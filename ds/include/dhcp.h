#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h> /*size_t*/

#define IPv4_BYTES 4

typedef struct dhcp dhcp_t;

typedef unsigned char ip_t[IPv4_BYTES];

typedef enum status
{
    SUGGESTED_IP_ALLOCATED = 0,
    ANOTHER_IP_ALLOCATED = 1,
    FAILED_ALLOCATION = 2
} status_t;

/*
typedef struct dhcp_node
{
    struct dhcp_node *children[2];
    struct dhcp_node *parent;
    int is_full;
} dhcp_node_t;

struct dhcp
{
    ip_t subnet_ip;
    trie_t *trie;
    size_t free_bits;
}
*/

/**
 * @brief:  Creates an instance of the DHCP module
 * @params: @subnet_ip - User's constant subnet address
 *          @free_bits - Number of modifiable bits
 * @return: Pointer to DHCP module
 * @complexity: O(log n)
 * @details: Network Address, Server Address, & Broadcast Address
 *           are allocated implicitly (where X is the subnet ID)
 *           X.000...000 (Network Address)
 *           X.111...110 (Server Address)
 *           X.111...111 (Broadcast Address)
 */
 dhcp_t *CreateDHCP(const ip_t subnet_ip, size_t free_bits);
 
 /**
  * @brief:  Destroys an instance of DHCP 
  * @params: Pointer to instance of DHCP
  * @return: void
  * @complexity: O(n)
  */
 void DestroyDHCP(dhcp_t *dhcp);
 
 /**
 * @brief: Assigns an IP address to a user.  If @suggested_ip is free, it will be assigned. 
 * Otherwise, another free IP address will be chosen (bigger than @suggested_ip).
 * @params: ip_suggested_ip is the IP address requested by user.  
 * @return: status_t enum descriptor
 * @complexity: O(log n)
 */
 status_t AllocateIP(dhcp_t *dhcp, const ip_t suggested_ip, ip_t allocated_ip);

 
 /**
  * @brief: Frees a reserved IP address for further allocation.
  * @params: An instance of dhcp, ip_to_free - the requested IP address to be freed.
  * @return: nothing
  * @complexity: O(log n)
  */
 void FreeIp(dhcp_t *dhcp, const ip_t ip_to_free);
 
 /**
  * @brief: Calculates the number of free IPs available for
  *         allocation
  * @params: Pointer to DHCP
  * @return: number of available ip addresses
  * @complexity: O(n)
  */
 size_t CountFree(dhcp_t *dhcp);
 
void PrintTrie(dhcp_t *dhcp);
#endif
