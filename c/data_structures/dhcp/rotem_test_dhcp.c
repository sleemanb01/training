
#include <limits.h> /* CHAR_BIT */
#include <math.h>   /* pow */

#include "dhcp.h"
#include "tests.h"
#define BITS_IN_ADDRESS SIZE_OF_ADDRESS * CHAR_BIT

static address_ty test_address1;
static address_ty test_address2;
static address_ty test_address3;
static int mask1;
static int mask2;
static int mask3;

static void InitAddresses();
static void SetBits(address_ty address, const size_t from, const size_t to , const int value);
static int GetBit(const address_ty address, const size_t bit);
static void CopySubnet(const address_ty subnet, address_ty dest, const size_t mask);
static void GetNetwork(address_ty subnet, address_ty return_add, int mask);
static void GetServer(address_ty subnet, address_ty return_add, int mask);
static void GetBrodcast(address_ty subnet, address_ty return_add, int mask);

void TestDHCPCreateDhcpDestroy();

void TestDHCPAllocateIP(); 

void TestDHCPFreeIPCountFree();

int main()
{
    InitAddresses();
    TestDHCPCreateDhcpDestroy();
    TestDHCPAllocateIP();
    TestDHCPFreeIPCountFree();

    PASS;
    return 0;
}

void TestDHCPCreateDhcpDestroy()
{
    dhcp_ty *dhcp1 = NULL;
    dhcp_ty *dhcp2 = NULL;
    dhcp_ty *dhcp3 = NULL;

    address_ty add_to_allo;
    address_ty allocated;
    request_status_ty status = 0;

    dhcp1 = DHCPCreateDhcp(test_address1, mask1);
    dhcp2 = DHCPCreateDhcp(test_address2, mask2);
    dhcp3 = DHCPCreateDhcp(test_address3, mask3);
    
    TEST_NOT_EQUAL("TestDHCPCreateDhcpDestroy", dhcp1, NULL);
    TEST_EQUAL("TestDHCPCreateDhcpDestroy", DHCPCountFree(dhcp1), pow(2, BITS_IN_ADDRESS - mask1) -3);

    TEST_NOT_EQUAL("TestDHCPCreateDhcpDestroy", dhcp2, NULL);
    TEST_EQUAL("TestDHCPCreateDhcpDestroy", DHCPCountFree(dhcp2), pow(2, BITS_IN_ADDRESS - mask2) -3);

    TEST_NOT_EQUAL("TestDHCPCreateDhcpDestroy", dhcp3, NULL);
    TEST_EQUAL("TestDHCPCreateDhcpDestroy", DHCPCountFree(dhcp3), pow(2, BITS_IN_ADDRESS - mask3) -3);

    GetNetwork( test_address1, add_to_allo, mask1);
    status = DHCPAllocateIP(dhcp1, add_to_allo, allocated);
    TEST_EQUAL("TestDHCPCreateDhcpDestroy", status, SUCCESS);
    TEST_EQUAL("TestDHCPCreateDhcpDestroy", allocated[3], add_to_allo[3]+1);
    
    GetNetwork( test_address2, add_to_allo, mask2);
    status = DHCPAllocateIP(dhcp2, add_to_allo, allocated);
    TEST_EQUAL("TestDHCPCreateDhcpDestroy", status, SUCCESS);
    TEST_EQUAL("TestDHCPCreateDhcpDestroy", allocated[3], add_to_allo[3]+1);

    GetNetwork( test_address3, add_to_allo, mask3);
    status = DHCPAllocateIP(dhcp3, add_to_allo, allocated);
    TEST_EQUAL("TestDHCPCreateDhcpDestroy", status, SUCCESS);
    TEST_EQUAL("TestDHCPCreateDhcpDestroy", allocated[3], add_to_allo[3]+1);

    GetServer( test_address1, add_to_allo, mask1);
    status = DHCPAllocateIP(dhcp1, add_to_allo, allocated);
    TEST_EQUAL("TestDHCPCreateDhcpDestroy", status, FAIL);

    GetServer( test_address2, add_to_allo, mask2);
    status = DHCPAllocateIP(dhcp2, add_to_allo, allocated);
    TEST_EQUAL("TestDHCPCreateDhcpDestroy", status, FAIL);

    GetServer( test_address3, add_to_allo, mask3);
    status = DHCPAllocateIP(dhcp3, add_to_allo, allocated);
    TEST_EQUAL("TestDHCPCreateDhcpDestroy", status, FAIL);

    GetBrodcast( test_address1, add_to_allo, mask1);
    status = DHCPAllocateIP(dhcp1, add_to_allo, allocated);
    TEST_EQUAL("TestDHCPCreateDhcpDestroy", status, FAIL);

    GetBrodcast( test_address2, add_to_allo, mask2);
    status = DHCPAllocateIP(dhcp2, add_to_allo, allocated);
    TEST_EQUAL("TestDHCPCreateDhcpDestroy", status, FAIL);

    GetBrodcast( test_address3, add_to_allo, mask3);
    status = DHCPAllocateIP(dhcp3, add_to_allo, allocated);
    TEST_EQUAL("TestDHCPCreateDhcpDestroy", status, FAIL);

    DHCPDestroy(dhcp1);
    DHCPDestroy(dhcp2);
    DHCPDestroy(dhcp3);
}

void TestDHCPAllocateIP()
{
    dhcp_ty *dhcp1 = NULL;
    dhcp_ty *dhcp2 = NULL;
    dhcp_ty *dhcp3 = NULL;
    dhcp_ty *dhcp4 = NULL;

    address_ty add_to_allo;
    address_ty allocated;
    request_status_ty status = 0;

    size_t runner = 0;

    dhcp1 = DHCPCreateDhcp(test_address1, mask1);
    dhcp2 = DHCPCreateDhcp(test_address2, mask2);
    dhcp3 = DHCPCreateDhcp(test_address3, mask3);
    dhcp4 = DHCPCreateDhcp(test_address1, mask1);

    SetBits(add_to_allo, 0, BITS_IN_ADDRESS, 0);
    CopySubnet( test_address1, add_to_allo,  mask1);
    add_to_allo[3] += 25;
    status = DHCPAllocateIP(dhcp1, add_to_allo, allocated);
    TEST_EQUAL("TestDHCPAllocateIP", status, SUCCESS);
    TEST_EQUAL("TestDHCPAllocateIP", allocated[3], add_to_allo[3]);

    status = DHCPAllocateIP(dhcp1, add_to_allo, allocated);
    TEST_EQUAL("TestDHCPAllocateIP", status, SUCCESS);
    TEST_EQUAL("TestDHCPAllocateIP", allocated[3], add_to_allo[3] + 1);

    SetBits(add_to_allo, 0, BITS_IN_ADDRESS, 0);
    CopySubnet( test_address2, add_to_allo,  mask2);
    add_to_allo[3] += 25;
    status = DHCPAllocateIP(dhcp2, add_to_allo, allocated);
    TEST_EQUAL("TestDHCPAllocateIP", status, SUCCESS);
    TEST_EQUAL("TestDHCPAllocateIP", allocated[3], add_to_allo[3]);

    status = DHCPAllocateIP(dhcp2, add_to_allo, allocated);
    TEST_EQUAL("TestDHCPAllocateIP", status, SUCCESS);
    TEST_EQUAL("TestDHCPAllocateIP", allocated[3], add_to_allo[3] + 1);

    SetBits(add_to_allo, 0, BITS_IN_ADDRESS, 0);
    CopySubnet( test_address3, add_to_allo,  mask3);
    add_to_allo[3] += 25;
    status = DHCPAllocateIP(dhcp3, add_to_allo, allocated);
    TEST_EQUAL("TestDHCPAllocateIP", status, SUCCESS);
    TEST_EQUAL("TestDHCPAllocateIP", allocated[3], add_to_allo[3]);

    status = DHCPAllocateIP(dhcp3, add_to_allo, allocated);
    TEST_EQUAL("TestDHCPAllocateIP", status, SUCCESS);
    TEST_EQUAL("TestDHCPAllocateIP", allocated[3], add_to_allo[3] + 1);

    SetBits(add_to_allo, 0, BITS_IN_ADDRESS, 0);
    CopySubnet( test_address1, add_to_allo,  mask1);

    for(runner = 1; runner < 254 ; ++runner)
    {
        ++add_to_allo[3];
        status = DHCPAllocateIP(dhcp4, add_to_allo, allocated);
        TEST_EQUAL("TestDHCPAllocateIP", status, SUCCESS);
        TEST_EQUAL("TestDHCPAllocateIP", allocated[3], add_to_allo[3]);
    }

    DHCPDestroy(dhcp1);
    DHCPDestroy(dhcp2);
    DHCPDestroy(dhcp3);
    DHCPDestroy(dhcp4);

}

void TestDHCPFreeIPCountFree()
{
    dhcp_ty *dhcp1 = NULL;

    address_ty add_to_allo;
    address_ty allocated;
    request_status_ty status = 0;

    size_t runner = 0;
    size_t free_add = 0;

    dhcp1 = DHCPCreateDhcp(test_address3, mask3);

    SetBits(add_to_allo, 0, BITS_IN_ADDRESS, 0);
    CopySubnet( test_address3, add_to_allo,  mask3);

    free_add = pow(2, BITS_IN_ADDRESS - mask3) - 3;

    for(runner = 1; runner <= free_add ; ++runner)
    {
        if(add_to_allo[3] == 255)
        {
            add_to_allo[3] = 0;
            ++add_to_allo[2];
        }
        else
        {
            ++add_to_allo[3];
        }
        status = DHCPAllocateIP(dhcp1, add_to_allo, allocated);
        TEST_EQUAL("TestDHCPFreeIPCountFree", status, SUCCESS);
        TEST_EQUAL("TestDHCPFreeIPCountFree", allocated[3], add_to_allo[3]);
        TEST_EQUAL("TestDHCPFreeIPCountFree", DHCPCountFree(dhcp1), free_add - runner);
    }

    SetBits(add_to_allo, 0, BITS_IN_ADDRESS, 0);
    CopySubnet( test_address3, add_to_allo,  mask3);

    for(runner = 1; runner <= free_add ; ++runner)
    {
        if(add_to_allo[3] == 255)
        {
            add_to_allo[3] = 0;
            ++add_to_allo[2];
        }
        else
        {
            ++add_to_allo[3];
        }
        status = DHCPFreeIP(dhcp1, add_to_allo);

        TEST_EQUAL("TestDHCPFreeIPCountFree", status, SUCCESS);
        TEST_EQUAL("TestDHCPFreeIPCountFree", DHCPCountFree(dhcp1), runner);
    }

    DHCPDestroy(dhcp1);
}

static void InitAddresses()
{
    test_address1[0] = 254;
    test_address1[1] = 254;
    test_address1[2] = 128;
    test_address1[3] = 0;
    mask1 = 24;

    test_address2[0] = 254;
    test_address2[1] = 254;
    test_address2[2] = 128;
    test_address2[3] = 128;
    mask2 = 25;

    test_address3[0] = 254;
    test_address3[1] = 254;
    test_address3[2] = 128;
    test_address3[3] = 0;
    mask3 = 20;
}

static int GetBit(const address_ty address, const size_t bit)
{
    size_t bit_in_char = 0;
    bit_in_char = CHAR_BIT - bit % CHAR_BIT -1;
    return  ((address[bit/CHAR_BIT] >>  bit_in_char) & 1);
}

static void SetBits(address_ty address, const size_t from, const size_t to , const int value)
{
    size_t bit_in_char = 0;
    size_t bit = 0;

    bit = from;

    for(bit = from; bit < to; ++bit)
    {
        bit_in_char = CHAR_BIT - bit % CHAR_BIT -1;
        address[bit/CHAR_BIT] &= ~(1 << bit_in_char); 
        address[bit/CHAR_BIT] = address[bit/CHAR_BIT] | (value << bit_in_char);
    }

}

static void CopySubnet(const address_ty subnet, address_ty dest, const size_t mask)
{
    size_t runner = 0;

    for(runner = 0; runner < mask; ++runner)
    {
        SetBits(dest, runner, runner + 1, 0);
        SetBits(dest, runner, runner + 1, GetBit(subnet, runner));
    }
}

static void GetNetwork(address_ty subnet, address_ty return_add, int mask)
{
    CopySubnet(subnet, return_add ,mask);
    SetBits(return_add, mask, BITS_IN_ADDRESS , 0);
}

static void GetServer(address_ty subnet, address_ty return_add, int mask)
{
    CopySubnet(subnet, return_add ,mask);
    SetBits(return_add, mask, BITS_IN_ADDRESS , 1);
    SetBits(return_add, BITS_IN_ADDRESS -1, BITS_IN_ADDRESS , 0);
}

static void GetBrodcast(address_ty subnet, address_ty return_add, int mask)
{
    CopySubnet(subnet, return_add ,mask);
    SetBits(return_add, mask, BITS_IN_ADDRESS , 1);
}