#include <stddef.h>    /* size_t */
#include <stdio.h>     /* itoa   */
#include <stdlib.h>    /* itoa   */
#include <string.h>    /* itoa   */
#include <time.h>      /* time   */

#include "dhcp.h"
#include "tests.h"

/******************************* STRUCTS/CONSTS *********************************/
#define BITS_IN_BYTE 8
#define MASK_MAX 32
#define MAX_NUMBER 255

typedef enum boolean_ty {TRUE, FALSE} boolean_ty;
typedef struct ip ip_ty;

struct ip
{
    int is_full;
    ip_ty *nodes[2];
};

struct dhcp
{
    ip_ty *root;
    unsigned int mask;
    address_ty subnet_id;     
};

/******************************* SIGNATURES *********************************/
void CreateDestroyTest();
void AllocFreeCountTest();

/*void ConvertToAddress(unsigned int random[], address_ty new);*/

/******************************* MAIN *********************************/
int main()
{
    CreateDestroyTest();
    AllocFreeCountTest();
   
    PASS;
    return (0);
}

/******************************* TESTS *********************************/

/*********************** CREATE/DESTROY ******************/
void CreateDestroyTest()
{
    
    /*unsigned int random[SIZE_OF_ADDRESS], mask;*/
    

    /*srand((unsigned) time(NULL));

    mask = rand() % 7;
    ++mask;
    
    for(i = 0; i < SIZE_OF_ADDRESS; ++i)
    {
        random[i] = rand() % MAX_NUMBER;
    }

    ConvertToAddress(random,new);

    random[SIZE_OF_ADDRESS - 1] = (random[SIZE_OF_ADDRESS - 1] >> mask) << mask ;

    dhcp = DHCPCreateDhcp(new, MASK_MAX - mask);*/

    /*unsigned int mask;
    address_ty address;

    dhcp_ty *dhcp = NULL;

    address[0] = 192;
    address[1] = 168;
    address[2] = 17;
    address[3] = 0;
    mask = 8;

    dhcp = DHCPCreateDhcp(address, MASK_MAX - mask);

    TEST_NOT_EQUAL("Create()", dhcp,NULL);

    DHCPDestroy(dhcp);*/
}

/************************* ALLOC/FREE ********************/
void AllocFreeCountTest()
{
    dhcp_ty *dhcp = NULL;
    unsigned int mask;
    address_ty address, ip1, ip2, requsted_ip;
    size_t free_ips = 256;
    size_t count = 0;

    address[0] = 192;
    address[1] = 168;
    address[2] = 17;
    address[3] = 0;
    mask = 8;

    dhcp = DHCPCreateDhcp(address, MASK_MAX - mask);

    requsted_ip[0] = 192;
    requsted_ip[1] = 168;
    requsted_ip[2] = 17;
    requsted_ip[3] = 10;

    count = DHCPCountFree(dhcp);
    TEST_EQUAL ("DHCPCountFree", count,free_ips);

    DHCPAllocateIP(dhcp, requsted_ip, ip1);

    count = DHCPCountFree(dhcp);
    TEST_EQUAL ("DHCPCountFree", count,free_ips - 1);

    DHCPAllocateIP(dhcp, requsted_ip, ip2);

    count = DHCPCountFree(dhcp);
    TEST_EQUAL ("DHCPCountFree", count,free_ips - 2);

    TEST_NOT_EQUAL("DHCPAllocateIP", ip1, ip2);    

    TEST_EQUAL("DHCPFreeIP", DHCPFreeIP(dhcp, ip2), SUCCESS);

    count = DHCPCountFree(dhcp);
    TEST_EQUAL ("DHCPCountFree", count,free_ips - 1);

    count = DHCPCountFree(dhcp);
    TEST_EQUAL("DHCPFreeIP", DHCPFreeIP(dhcp, ip1), SUCCESS);

    count = DHCPCountFree(dhcp);
    TEST_EQUAL ("DHCPCountFree", count,free_ips);

    DHCPDestroy(dhcp);
}

/***************** CONVERT TO ADDRESS ********************/
/*void ConvertToAddress(unsigned int random[], address_ty new)
{
    size_t i;

    for (i = 0; i < SIZE_OF_ADDRESS; ++i)
    {
        new[i] = random[i];
    }
}*/