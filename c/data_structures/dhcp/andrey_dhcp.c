#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc(), free() */
#include <inttypes.h> /* uint_fast32_t */
#include <string.h> /* memcpy() */
#include <assert.h>

#include "dhcp.h"

#define NUM_OF_CHILDREN 2
#define BYTE_SIZE 8

typedef struct node_ip ip_ty;

struct dhcp
{
    ip_ty *root;
    unsigned int mask;
    address_ty subnet_id; 
};

struct node_ip
{
    int is_full_flag;
    ip_ty *children[NUM_OF_CHILDREN];
};

/* help functions declaration */
static void DHCPFillIPEnd(address_ty ip, const unsigned int mask, const unsigned int value);
static request_status_ty DHCPAllocateIPImp(size_t hight, ip_ty *current_node, uint_least32_t requested_ip, uint_least32_t *granted_ip);
static void DHCPFillNewNode(ip_ty *node);
static void DHCPDestroyImp(ip_ty *current_node);
static size_t DHCPRootHight(const dhcp_ty *this);
static size_t DHCPCountFreeImp(size_t hight, ip_ty *current_node);
static uint_least32_t DHCPIPtoInt(const address_ty ip);
static int DHCPCheckFull(const ip_ty *current_node);
static request_status_ty DHCPCheckSubnet(const dhcp_ty *this, const address_ty ip);


/* Implementation */
dhcp_ty *DHCPCreateDhcp(const address_ty subnet_id , unsigned int mask_bits)
{
    dhcp_ty *new_dhcp = NULL;
    size_t i = 0;

    do
    {
        address_ty temp_ip;

        /* alloc main struct */
        new_dhcp = malloc(sizeof(dhcp_ty));
        if(NULL == new_dhcp)
        {
            return NULL;
        }

        new_dhcp->root = malloc(sizeof(ip_ty));
        if(NULL == new_dhcp->root)
        {
            free(new_dhcp);
            return NULL;
        }

        DHCPFillNewNode(new_dhcp->root);

        new_dhcp->mask = mask_bits;

        /* initial fill of main struct */
        for (i = 0 ; i < SIZE_OF_ADDRESS ; ++i)
        {
            temp_ip[i] = subnet_id[i];
        }
        
        DHCPFillIPEnd(temp_ip, new_dhcp->mask, 0);
        for (i = 0; i < SIZE_OF_ADDRESS ; ++i)
        {
            new_dhcp->subnet_id[i] = temp_ip[i];
        }


        /* initial alloc 3 addresses */
        /* zeros */

        if(!(SUCCESS == DHCPAllocateIP(new_dhcp, subnet_id, temp_ip)))
        {
            break;
        }

        /* broadcast */
        DHCPFillIPEnd(temp_ip, new_dhcp->mask, 1);
        if(!(SUCCESS == DHCPAllocateIP(new_dhcp, temp_ip, temp_ip)))
        {
            break;
        }

        /* server, one before end */
        temp_ip[SIZE_OF_ADDRESS - 1] &= ~1;
        if(!(SUCCESS == DHCPAllocateIP(new_dhcp, temp_ip, temp_ip)))
        {
            break;
        }
        
        return new_dhcp;
    } while (0);
    
    /* destroy on fail */
    DHCPDestroy(new_dhcp);
    return NULL;
}

void DHCPDestroy(dhcp_ty *this)
{
    /* assert this */
    assert(NULL != this);
    /* recursive go to NULL and free */
    DHCPDestroyImp(this->root);
    free(this);
}


request_status_ty DHCPAllocateIP(dhcp_ty *this, const address_ty requested_ip, address_ty granted_ip)
{
    uint_least32_t temp_requested_ip = 0;
    uint_least32_t temp_granted_ip = 0;
    uint_least32_t last_ip = 0;

    request_status_ty res = FAIL;
    size_t i = 0;

    /* assert this */
    assert(NULL != this);

    if (FAIL == DHCPCheckSubnet(this, requested_ip))
    {
        return FAIL;
    }
    /* check path to requested ip */
    /* if path or ip not exists - create */
    /* if exists check if free */
    /* if not free look for next free */

    temp_requested_ip = DHCPIPtoInt(requested_ip);

    last_ip = temp_requested_ip;
    for ( i = 0 ; i < DHCPRootHight(this) ; ++i)
    {
        last_ip |= 1 << i;
    }

    for (res = FAIL ; (FAIL == res) && (temp_requested_ip <= last_ip) ; ++temp_requested_ip)
    {
        temp_granted_ip = 0;
        res = DHCPAllocateIPImp(DHCPRootHight(this), this->root, temp_requested_ip, &temp_granted_ip);
    }


    for ( i = 0 ; i < SIZE_OF_ADDRESS ; ++i)
    {
        granted_ip[3 - i] = temp_granted_ip >> (BYTE_SIZE * i);
    }

    return res;
}

static void DHCPFreeIPImp(size_t hight, ip_ty *current_node, uint_least32_t requested_ip)
{
    int next_child = NUM_OF_CHILDREN;

    if (NULL == current_node)
    {
        return;
    }

    /* check if node is a leaf */
    if (0 == hight)
    {
        /* mark as free */
        current_node->is_full_flag = 0;
        return;
    }

    /* go down */
    /* choose a child */
    next_child = (requested_ip >> (hight - 1)) & 1;
    if (NULL == current_node->children[next_child])
    {
        return;
    }

    DHCPFreeIPImp(hight - 1, current_node->children[next_child], requested_ip);

    current_node->is_full_flag = DHCPCheckFull(current_node);

}

request_status_ty DHCPFreeIP(dhcp_ty *this, const address_ty requested_ip)
{
    /* assert this */
    assert(NULL != this);

    /* check if ip in same subnet */
    if (FAIL == DHCPCheckSubnet(this, requested_ip))
    {
        return FAIL;
    }

    /* recursive check if exits */
    /* if exist - change flag to free */
    DHCPFreeIPImp(DHCPRootHight(this), this->root, DHCPIPtoInt(requested_ip));
    return SUCCESS;
}


size_t DHCPCountFree(const dhcp_ty *this)
{
    /* assert this */
    assert(NULL != this);
    /* recursive check if exits and flag free */
    /* count free leafs */
    return DHCPCountFreeImp(DHCPRootHight(this), this->root);
}

static void DHCPFillIPEnd(address_ty ip, const unsigned int mask, const unsigned int value)
{
    uint_least32_t temp_ip_int = 0;
    size_t i = 0;

    /* init copy array to int */
    temp_ip_int = DHCPIPtoInt(ip);

    /* fill int*/
    if (value)
    {
        for ( i = 0 ; i < (BYTE_SIZE * SIZE_OF_ADDRESS) - mask ; ++i)
        {
            temp_ip_int |= 1 << i;
        }
    }
    else
    {
        for ( i = 0 ; i < ((BYTE_SIZE * SIZE_OF_ADDRESS) - mask) ; ++i)
        {
            temp_ip_int &= ~(1 << i);
        }
    }
    /* return int to arr */
    for ( i = 0 ; i < SIZE_OF_ADDRESS ; ++i)
    {
        ip[SIZE_OF_ADDRESS - 1 - i] = temp_ip_int >> (BYTE_SIZE * i);
    }
}

static request_status_ty DHCPAllocateIPImp(size_t hight, ip_ty *current_node, uint_least32_t requested_ip, uint_least32_t *granted_ip)
{
    int next_child = NUM_OF_CHILDREN;
    request_status_ty res = FAIL;

    if (current_node->is_full_flag)
    {
        return FAIL;
    }

    /* check if node is a leaf */
    if (0 == hight)
    {
        /* mark as not free */
        current_node->is_full_flag = 1;
        *granted_ip = requested_ip;

        return SUCCESS;
    }

    /* go down */
    /* choose a child */
    next_child = (requested_ip >> (hight - 1)) & 1;
    /* if have not a right child */
    if (NULL == current_node->children[next_child])
    {
        /* create new */
        ip_ty *new_node = NULL;
        new_node = malloc(sizeof(ip_ty));
        if (NULL == new_node)
        {
            return FAIL;
        }

        /* fill new node */
        DHCPFillNewNode(new_node);

        current_node->children[next_child] = new_node;

    }

    /* try next free */
    /*if ((FAIL == res) && (0 == next_child))
    {
        res = DHCPAllocateIPImp(hight - 1, current_node->children[1], requested_ip, granted_ip);
    }*/
    res = DHCPAllocateIPImp(hight - 1, current_node->children[next_child], requested_ip, granted_ip);

    current_node->is_full_flag = DHCPCheckFull(current_node);
    
    return res; 
}

static void DHCPFillNewNode(ip_ty *node)
{
    assert(NULL != node);

    node->children[0] = NULL;
    node->children[1] = NULL;
    node->is_full_flag = 0;
}

static void DHCPDestroyImp(ip_ty *current_node)
{
    if (NULL == current_node)
    {
        return;
    }

    DHCPDestroyImp(current_node->children[0]);
    DHCPDestroyImp(current_node->children[1]);

    free(current_node);
}

static size_t DHCPRootHight(const dhcp_ty *this)
{
    return (BYTE_SIZE * SIZE_OF_ADDRESS) - this->mask;
}

static size_t DHCPCountFreeImp(size_t hight, ip_ty *current_node)
{
    if ((NULL == current_node))
    {
        return 1 << hight;
    }

    if (current_node->is_full_flag)
    {
        return 0;
    }

    if (0 == hight)
    {
        return 1;
    }

    return (DHCPCountFreeImp(hight - 1, current_node->children[0]) + DHCPCountFreeImp(hight - 1, current_node->children[1]));
}

static uint_least32_t DHCPIPtoInt(const address_ty ip)
{
    uint_least32_t temp_ip_int = 0;
    size_t i = 0;

    /* init copy array to int */
    for (i = 0 ; i < SIZE_OF_ADDRESS ; ++i)
    {
        temp_ip_int = (temp_ip_int << BYTE_SIZE) + ip[i];
    }

    return temp_ip_int;
}

static int DHCPCheckFull(const ip_ty *current_node)
{
    int child_full[NUM_OF_CHILDREN] = {0};
    size_t i = 0;

    assert(NULL != current_node);
    
    for (i = 0 ; i < NUM_OF_CHILDREN ; ++i)
    {
        child_full[i] = (NULL != current_node->children[i]) && current_node->children[i]->is_full_flag;
    }
    return child_full[0] && child_full[1];
}

static request_status_ty DHCPCheckSubnet(const dhcp_ty *this, const address_ty ip)
{
    address_ty temp_ip;
    size_t i = 0;

    /* assert this */
    assert(NULL != this);

    /* check if ip in same subnet */
    for (i = 0; i < SIZE_OF_ADDRESS ; ++i)
    {
        temp_ip[i] = ip[i];
    }

    DHCPFillIPEnd(temp_ip, this->mask, 0);

    for (i = 0; i < SIZE_OF_ADDRESS ; ++i)
    {
        if (temp_ip[i] != this->subnet_id[i])
        {
            return FAIL;
        }
    }

    return SUCCESS;
}