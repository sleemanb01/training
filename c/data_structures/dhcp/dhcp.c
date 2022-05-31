/************************************************************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : DHCP
* REVIEWER NAME : ROTEM
************************************************************************************************/

#include <stddef.h>	         /* size_t */ 
#include <stdlib.h>          /* malloc */
#include <assert.h>          /* assert */
#include <string.h>          /* memcpy */
#include <math.h>            /* pow    */
#include <stdio.h>

#include "dhcp.h"

/***********************************************************************************************
*                                      STRCUCTS/CONSTS                                          *
************************************************************************************************/

#define BITS_IN_BYTE 8
#define MASK_MAX 32
#define CHAR_BIT_SIZE 8

#define ZERO 0

typedef enum boolean_ty {FALSE, TRUE} boolean_ty;                     /*   TO INCREASE READABILITY */
typedef enum alocate_status_ty {DONE, ERR, SEARCH} alocate_status_ty; /*             ^^^           */

typedef struct ip ip_ty;

struct ip
{
    int is_full_flag;
    ip_ty *children[2];         /* left/right macro */
};

struct dhcp
{
    ip_ty *root;
    unsigned int mask;          /* how many bits for host address */
    address_ty subnet_id;       /* EX. 192.168.17.0 */ 
};

/***********************************************************************************************
*                                            EXTRA FUNCS                                       *
************************************************************************************************/

static ip_ty *DHCPInsert();

static ip_ty* Find(ip_ty *root, size_t ip_bits, unsigned int subnet_size);

static void DestroyIMP(ip_ty *node);
static void ConverBitsToAddress(size_t ip_bits, address_ty target);

static size_t CountFullIMP(ip_ty *node);
static size_t ConvertAddress(const address_ty address);
static size_t SetBits(size_t ip_bits, size_t size, size_t number);
static size_t SetBitOn(size_t bit_array, size_t index);
static size_t SetBitOff(size_t bit_array, size_t index);
static size_t SetBit(size_t bit_array, size_t index, unsigned int value);

static boolean_ty IsLeaf(ip_ty *node);
static boolean_ty SearchNextAvailable(size_t *ip_bits, unsigned int ip_size);

static alocate_status_ty AllocateIMP(ip_ty *node, size_t ip_bits, unsigned int subnet_size);

/************************************************************************************************
*  Name:            DHCPCreateCountFreeIMP
*  Description:     Create an empty dhcp
*  Parameters:      address type, mask bits
*  Return    :      Pointer to newly created DHCP structure
*  Complexity:      O(1)
************************************************************************************************/

dhcp_ty *DHCPCreateDhcp(const address_ty subnet_id , unsigned int mask_bits)
{
    dhcp_ty *new = NULL;
    ip_ty *root_ip = NULL;
    address_ty granted, requested;
    size_t ip_bits;

    do
    {
        /* CREATE A NEW DHCP WITH ALLOCATED ROOT */
        new = (dhcp_ty*)malloc(sizeof(struct dhcp));
        if(NULL == new)
        {
            break;
        }

        root_ip = DHCPInsert();

        if(NULL == root_ip)
        {
            break;
        }

        new->root = root_ip;
        new->mask = mask_bits;
        memcpy(new->subnet_id, subnet_id, SIZE_OF_ADDRESS);

        /* address to bits >>>> change according to mask >>>>> bit to address */

         memcpy(requested, subnet_id, SIZE_OF_ADDRESS);

        ip_bits = ConvertAddress(requested);
        
        /* SUBNET MASK 000 ... 000 */

        ip_bits = SetBits(ip_bits, (MASK_MAX - mask_bits), ZERO);
        ConverBitsToAddress(ip_bits, requested);

        if(FAIL == DHCPAllocateIP(new, requested, granted))
        {
            break;
        }

        /* SUBNET MASK 111 ... 111 */
        ip_bits = SetBits(ip_bits, (MASK_MAX - mask_bits), pow(2,(MASK_MAX - mask_bits)) - 1);
        ConverBitsToAddress(ip_bits, requested);

        if(FAIL == DHCPAllocateIP(new, requested, granted))
        {
            break;
        }


        /* SUBNET MASK 111 ... 110 */
        ip_bits = SetBits(ip_bits, (MASK_MAX - mask_bits), pow(2,(MASK_MAX - mask_bits)) - 2);
        ConverBitsToAddress(ip_bits, requested);

        if(FAIL == DHCPAllocateIP(new, requested, granted))
        {
            break;
        }

        return new;

    } while (0);

    DHCPDestroy(new);

    return NULL;
}

/************************************************************************************************
*  Name:            DHCPDestroy
*  Description:     destroy a DHCP
*  Parameters:      DHCP type
*  Return    :      
*  Complexity:      O(n)
************************************************************************************************/

void DHCPDestroy(dhcp_ty *this)
{
    assert(NULL != this);

    /* RECURSIVLEY DELETE ALL NODES */
    DestroyIMP(this->root);
    free(this);
}

/************************************************************************************************
*  Name:            DHCPAllocateIP
*  Description:     Create an empty heap
*  Parameters:      dhcp, requested address, granted address
*  Return    :      smallest available IP, bigger or equal to requested IP
*  Complexity:      O(1)
************************************************************************************************/
request_status_ty DHCPAllocateIP(dhcp_ty *this, const address_ty requested_ip, address_ty granted_ip)
{
    size_t ip_bits, ip_host_bits, subnet_bits;
    unsigned int mask;
    alocate_status_ty status = SEARCH;
    
    assert(NULL != this);

    mask = MASK_MAX - this->mask;

    /* CONVERT THE ADDRESSES INTO BITS */
    subnet_bits = ConvertAddress(this->subnet_id);

    /* IF REQUESTED ADDRESS IS NULL */
    if(NULL == requested_ip)
    {
        requested_ip = this->subnet_id;
    }

    ip_host_bits = ip_bits = ConvertAddress(requested_ip);

    /* CALCULATE AVAILABLE BITS AVAILABLE FOR HOST NETWORK */
    /* VALIDATE NETWORK IS SAME */
    if((ip_bits >> mask) != (subnet_bits >> mask))
    {
        return FAIL;
    }
    
    /* GET THE HOST PART */
    ip_host_bits &= (~subnet_bits);

    /* ALLOCATE, IF ADDRESS NOT AVAILABLE SEARCH FOR NEXT */
    do
    {
        status = AllocateIMP(this->root, ip_host_bits, mask);

        if(ERR == status)
        {
            return FAIL;
        }

        if(SEARCH == status && (pow(2,mask) - 1) == ip_host_bits)
        {
            return FAIL;
        }

    }while((status == SEARCH) && (SearchNextAvailable(&ip_host_bits, mask)));

    ip_bits >>= (MASK_MAX - this->mask);
    ip_bits <<= (MASK_MAX - this->mask);

    ip_bits |= ip_host_bits;

    ConverBitsToAddress(ip_bits, granted_ip);

    return SUCCESS;
}

/************************************************************************************************
*  Name:            DHCPFreeIP
*  Description:     free address
*  Parameters:      dhcp, requested address
*  Return    :      smallest available IP, bigger or equal to requested IP
*  Complexity:      O(1)
************************************************************************************************/

request_status_ty DHCPFreeIP(dhcp_ty *this, const address_ty requested_ip)
{
    ip_ty *target = NULL;
    size_t target_bits, ip_size, subnet_bits;

    assert(NULL != this);
    assert(NULL != requested_ip);

    ip_size = MASK_MAX - this->mask;

    subnet_bits = ConvertAddress(this->subnet_id);
    target_bits = ConvertAddress(requested_ip);

    if((target_bits >> ip_size) != (subnet_bits >> ip_size))
    {
        return FAIL;
    }

    target = Find(this->root, target_bits, ip_size);
    if(NULL != target)
    {
        /* FOR SAVING FUTURE ALLOCATION ONLY FLAG IS CHANGED */ 
        target->is_full_flag = 0;
        return SUCCESS;
    }

    return FAIL;
}

/************************************************************************************************
*  Name:            DHCPCountFree
*  Description:     count free ip's left
*  Parameters:      dhcp
*  Return    :      number of free ip's
*  Complexity:      O(1)
************************************************************************************************/

size_t DHCPCountFree(const dhcp_ty *this)
{
    /* CALCULATE AVAILABLE IP'S MINUS ALREADY FULL */ 
    return ((pow(2,(MASK_MAX - this->mask))) - (CountFullIMP(this->root)));
}


/***********************************************************************************************
*                                            EXTRA FUNCS                                       *
************************************************************************************************/

/*********************************** IS LEAF ************************************/
static boolean_ty IsLeaf(ip_ty *node)
{
    if((NULL == node->children[0]) && (NULL == node->children[1]))
    {
        return TRUE;
    }

    return FALSE;
}

/*********************************** RECURSIVE DESTROY ************************************/
static void DestroyIMP(ip_ty *node)
{
    if(NULL == node)
    {
        return;
    }

    DestroyIMP(node->children[0]);
    DestroyIMP(node->children[1]);
    free(node);
}

/******************************* ALLOCATE RECURSIVE *********************************/
static alocate_status_ty AllocateIMP(ip_ty *node, size_t ip_bits, unsigned int subnet_size)
{
    ip_ty *parent, *child;
    size_t msb, ip;
    int i;

    /* TRAVERSE TRIE FOR HOST_NETWORK SIZE (SUBNET) */
    for (
            ip = ip_bits, parent = node, i = subnet_size -1;
            (0 <= i); 
            ip &= ~(0x01 << i), parent = child, --i
        )
    {
        /* TRAVERSE THROUGH MOST SIGNIFICANT BIT */ 
        msb = (ip & (0x01 << i));
        msb >>= (i);

        child = parent->children[msb];

        /* IF NODE DON'T EXISTS CREATE ONE */ 
        if(NULL == child)
        {
            child = DHCPInsert();
        }
        
        /* IF NODE EXISTS AND NOT FULL */ 
        if(NULL != child && (0 == child->is_full_flag))
        {
            parent->children[msb] = child;
        }
        else
        {
            /* IF MALLOC FAILED */
            if(NULL == child)
            {
                return FAIL;
            }
            else
            {
                /* IP IS FULL SEARCH FOR ANOTHER (MOST SMALLER THAT IS BIGGER THAN CURRENT) */ 
                return SEARCH;
            }
        }
    }

    child->is_full_flag = 1;

    return SUCCESS;
}

/******************************* CONVERT CHAR[] TO BITS *********************************/
static size_t ConvertAddress(const address_ty address)
{
    size_t output = 0;
    int index = 0;
    for (index = 0; index < SIZE_OF_ADDRESS; ++index)
    {
        output <<= BITS_IN_BYTE;
        output |= address[index];
    }
    return output;
}

/******************************* INSERT *********************************/
static ip_ty* DHCPInsert()
{
    ip_ty *node = NULL;

    node = (ip_ty*)malloc(sizeof(struct ip));
    if(NULL == node)
    {
        return NULL;
    }

    node->is_full_flag = 0;
    node->children[0] = NULL;
    node->children[1] = NULL;

    return node;
}

/******************************* FIND *********************************/
static ip_ty* Find(ip_ty *root, size_t ip_bits, unsigned int subnet_size)
{
    ip_ty *target = root;
    size_t msb;
    int i;

    for 
        (
            i = subnet_size - 1;
            (0 <= i); 
            ip_bits &= ~(0x01 << i), --i
        )
    {
        /* TRAVERSE THROUGH MOST SIGNIFICANT BIT */ 
        msb = (ip_bits & (0x01 << i));
        msb >>= (i);

        target = target->children[msb];
        if(NULL == target)
        {
            return NULL;
        }
    }

    return target;
}

/******************************* COUNT FREE RECURSIVE *********************************/
static size_t CountFullIMP(ip_ty *node)
{
    if(NULL == node)
    {
        return 0;
    }
    if(IsLeaf(node) && (1 == (node->is_full_flag)))
    {
        return 1;
    }

    return CountFullIMP(node->children[0]) + CountFullIMP(node->children[1]);
}

/******************************* SEARCH FOR NEXT AVAILABLE *********************************/
static boolean_ty SearchNextAvailable(size_t *ip_bits, unsigned int ip_size)
{
    size_t i;

    for(i = 0; i < ip_size; ++i)
    {
        if(!(*ip_bits & (0x1 << i)))
        {
            ++*ip_bits;
            return TRUE;
        }
    }

    return FALSE;
}


/******************************* CONVERT BITS TO ADDRESS *********************************/
static void ConverBitsToAddress(size_t ip_bits, address_ty target)
{
    int i;

    for(i = SIZE_OF_ADDRESS - 1 ; i >= 0; --i)
    {
        target[i] = ip_bits & (255);
        ip_bits >>= CHAR_BIT_SIZE;
    }
}

/******************************* SET BITS *********************************/
static size_t SetBits(size_t ip_bits, size_t size, size_t number)
{
    size_t i;

    for(i = 0 ; i < size; ++i)
    {
        ip_bits = SetBit(ip_bits, i, ((number >> i) & 0x1));
    }

    return ip_bits;

}

/******************************* SET BIT ON S*********************************/
size_t SetBitOn(size_t bit_array, size_t index)
{
	return (bit_array | (0x1 << index));
}

/******************************* SET BIT OFF *********************************/
size_t SetBitOff(size_t bit_array, size_t index)
{
	return (bit_array & ~(0x1 << index));
}

/******************************* SET BIT *********************************/
size_t SetBit(size_t bit_array, size_t index, unsigned int value)
{
	if(value == 1)
	{
		bit_array = SetBitOn(bit_array, index);
	}
	else
	{
		bit_array = SetBitOff(bit_array, index);
	}
	return (bit_array);
}