#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h> /* for size_t */

#define SIZE_OF_ADDRESS 4

/********* VERSION 1.4 *********/

typedef struct dhcp dhcp_ty;
typedef unsigned char address_ty[SIZE_OF_ADDRESS];

typedef enum request_status {SUCCESS, FAIL} request_status_ty;

dhcp_ty *DHCPCreateDhcp(const address_ty subnet_id , unsigned int mask_bits);

void DHCPDestroy(dhcp_ty *this);

/* generates smallest available IP, bigger or equal to requested and stores it to granted_ip */
request_status_ty DHCPAllocateIP(dhcp_ty *this, const address_ty requested_ip, address_ty granted_ip); 

request_status_ty DHCPFreeIP(dhcp_ty *this, const address_ty requested_ip);

size_t DHCPCountFree(const dhcp_ty *this);

#endif
