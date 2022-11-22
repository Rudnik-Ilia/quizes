/*********************************
* Author: Alena Khoroshilova     *
* Group: OL132                   *
* WS: DHCP                       *
* Reviewer: Ilia                 *
* Date : 21.11.2022              *
* Status: ________               *
*********************************/

#include <stdlib.h> /* malloc, free, size_t */
#include <assert.h> /* assert */
#include <string.h> /* strcmp */
#include <stdio.h> /* print for debug */

#include "dhcp.h"

#define IPv4_BYTES 4
#define DUMMY_DATA (void *)0xdeadbeef

#define MASK_0 (int) 0 		/* X X X 00000000 */
#define MASK_1 (int) 1 		/* X X X 00000001 */
#define MASK_F (int) 0xFFFFFFFF 	/* X X X 11111_111 */

#define BIT 1lu
#define NETWORK_ADDRESS (int) 0 		/* X X X 00000_000 */ /* X.X.X.24 */
#define SERVER_ADDRESS (int) 0xFFFFFFFE 	/* X X X 11111_110 */ /* X.X.X.30 */
#define BROADCAST_ADDRESS (int) 0xFFFFFFFF 	/* X X X 11111_111 */ /* X.X.X.31 */

#define TEST_ADDRESS_29 (int) 0xFFFFFFFD 	/* X X X 11111_001 */ /* X.X.X.29 */
#define TEST_ADDRESS_25 		 	/* X X X 11111_001 */ /* X.X.X.25 */
#define TEST_ADDRESS_26 		 	/* X X X 11111_010 */ /* X.X.X.26 */

/* 
typedef struct dhcp dhcp_t;
typedef unsigned char ip_t[IPv4_BYTES];
typedef enum status
{
    SUGGESTED_IP_ALLOCATED = 0,
    ANOTHER_IP_ALLOCATED = 1,
    FAILED_ALLOCATION = 2
} status_t;
*/

typedef enum flag
{
	EMPTY = 0,
	FULL = 1
} flag_t;

typedef struct trie trie_t;
typedef struct dhcp_node dhcp_node_t;


struct dhcp
{
	/* subnet_ip == subnet_mask*/
	ip_t subnet_ip;
	size_t free_bits;
	trie_t *trie;
};

struct trie 
{
	dhcp_node_t *root;
};

struct dhcp_node 
{
    struct dhcp_node *children[2];
    struct dhcp_node *parent;
    int is_full;
};

/*********************************************** Additional Functions **************************************************/
static trie_t *CreateTrie();
static dhcp_node_t *CreateNode();
static void ToMaskSubIp(dhcp_t *dhcp, const ip_t subnet_ip, ip_t submask_ip); /*here*/
static void RemovePostOrder(dhcp_node_t *root);
static void AllocateIPAux(dhcp_t *dhcp, dhcp_node_t *root, int IP);
static int IsAllocated(dhcp_t *dhcp, dhcp_node_t *root, int IP);
static int NotReachedTheEnd(dhcp_t *dhcp, int IP);
static void SetAllocatedIP(int IP, ip_t allocated_ip);
static int IpToInt(const ip_t ip);
static size_t CountFreeAux(dhcp_node_t *node, size_t bits);

/*debug IP print */
static void PrintIP(char *comment, ip_t IP);
static void PrintConstIP(char *comment, const ip_t IP);

/*********************************************** API Functions **************************************************/
dhcp_t *CreateDHCP(const ip_t subnet_ip, size_t free_bits)
{
	dhcp_t *dhcp = NULL;
	ip_t submask_ip = {0,0,0,0};
	
	assert(free_bits >= 3);
	
	dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
	if(NULL == dhcp)
	{
		return NULL;
	}

	dhcp->trie = CreateTrie();
	
	if(NULL == dhcp->trie)
	{
		free(dhcp);
		return NULL;
	}

	ToMaskSubIp(dhcp, subnet_ip, submask_ip);
	memcpy(dhcp->subnet_ip, submask_ip, 4); 
	dhcp->free_bits = free_bits;	
	
	/* Preallocate 3 IP */
	AllocateIPAux(dhcp, dhcp->trie->root, NETWORK_ADDRESS);
	AllocateIPAux(dhcp, dhcp->trie->root, SERVER_ADDRESS);
	AllocateIPAux(dhcp, dhcp->trie->root, BROADCAST_ADDRESS);
	
/*	PrintConstIP("subnet_ip", subnet_ip);
	PrintIP("submask_ip", submask_ip);*/

	return dhcp;
}

void DestroyDHCP(dhcp_t *dhcp)
{
	assert(NULL != dhcp);

	RemovePostOrder(dhcp->trie->root);
	free(dhcp->trie);	
	free(dhcp);
}

status_t AllocateIP(dhcp_t *dhcp, const ip_t suggested_ip, ip_t allocated_ip)
{
	int IP = IpToInt(suggested_ip);
		
	assert(dhcp);
	
	if(FULL == dhcp->trie->root->is_full)
	{
		return FAILED_ALLOCATION;
	}
	
	if(0 == IP)
	{
		IP = IpToInt(dhcp->subnet_ip);
	}

	if(!IsAllocated(dhcp, dhcp->trie->root, IP))
	{
		AllocateIPAux(dhcp, dhcp->trie->root, IP);
		SetAllocatedIP(IP, allocated_ip);
		
		return SUGGESTED_IP_ALLOCATED;
	}

	while(IsAllocated(dhcp, dhcp->trie->root, IP) && NotReachedTheEnd(dhcp, IP)) 
	{
		++IP;
	}
	
	if(NotReachedTheEnd(dhcp, IP)) 
	{
		AllocateIPAux(dhcp, dhcp->trie->root, IP);
		SetAllocatedIP(IP, allocated_ip);
		
		return ANOTHER_IP_ALLOCATED;
	}

	return FAILED_ALLOCATION;
}

void FreeIp(dhcp_t *dhcp, const ip_t ip_to_free)
{
	dhcp_node_t *parent = dhcp->trie->root;
	dhcp_node_t *node_to_free;
	unsigned int side;
	int i;
	int ip_int = IpToInt(ip_to_free);
		
	assert(NULL != dhcp);
	
	if(!IsAllocated(dhcp, dhcp->trie->root, ip_int))	
	{
		/*printf("FreeIp not_allocated_ip - EXIT\n");
		PrintConstIP("not allocated ip", ip_to_free);*/
		return ;
	}

	/* printf("FreeIP: IpToInt(ip_int) = %d\n", ip_int);*/
	for(i = dhcp->free_bits - 1; i > -1 ; --i)
	{
		side = ((ip_int & (1lu << i)) >> i);
		/* printf("side = %d\n", side); */
		node_to_free = parent->children[side];
		parent = node_to_free;
	}
	parent = node_to_free->parent;
	parent->children[side] = NULL;
	parent->is_full = EMPTY;
	free(node_to_free);
}

size_t CountFree(dhcp_t *dhcp)
{
	assert(NULL != dhcp);
	
	return CountFreeAux(dhcp->trie->root, dhcp->free_bits);
}

/*********************************************** Additional Functions **************************************************/
static trie_t *CreateTrie()
{
	trie_t *trie = (trie_t *)malloc(sizeof(trie_t));
	if(NULL == trie)
	{
		return NULL;
	}
	
	trie->root = CreateNode();
	if(NULL == trie->root)
	{
		free(trie);
		return NULL;
	}
	trie->root->parent = DUMMY_DATA;
	
	return trie;
}

static dhcp_node_t *CreateNode()
{	
	dhcp_node_t *node = (dhcp_node_t *)malloc(sizeof(dhcp_node_t));
	
	if(NULL == node)
	{
		return NULL;
	}
	
	node->parent = NULL;
	node->children[0] = NULL;
	node->children[1] = NULL;
	node->is_full = 0;

	return node;
}

/* here */
static void ToMaskSubIp(dhcp_t *dhcp, const ip_t subnet_ip, ip_t submask_ip)
{
	int mask = MASK_F << dhcp->free_bits; /* 11111111111000 */	
	int subnet_ip_int = IpToInt(subnet_ip);

	subnet_ip_int = (mask & subnet_ip_int);
	SetAllocatedIP(subnet_ip_int, submask_ip);
}

static void RemovePostOrder(dhcp_node_t *root)
{
	if(NULL == root)
	{
		return ;
	}
	
	RemovePostOrder(root->children[0]);
	RemovePostOrder(root->children[1]);
	free(root);
}

static void AllocateIPAux(dhcp_t *dhcp, dhcp_node_t *root, int IP)
{
	dhcp_node_t *parent = root;
	dhcp_node_t *node;
	int i = 0;
	unsigned int side;

	assert(NULL != dhcp);	
	assert(NULL != root);
	
	for(i = dhcp->free_bits - 1; i > -1  ; --i)
	{
		side = ((IP & (1lu << i)) >> i);
		if(NULL == parent->children[side])
		{
			node = CreateNode();	
			parent->children[side] = node;
			node->parent = parent;
		}
		parent = parent->children[side];		
	}
	node = parent;
	
	if(NULL != node->parent->children[0] && NULL != node->parent->children[1])
	{
		node->parent->is_full = FULL;
	}
}

static int IsAllocated(dhcp_t *dhcp, dhcp_node_t *root, int IP)
{
	dhcp_node_t *parent = root;
	int i = 0;
	unsigned int side;

	assert(NULL != dhcp);	
	assert(NULL != root);
	
	for(i = dhcp->free_bits - 1; i > -1  ; --i)
	{
		if(FULL == parent->is_full)
		{
			return 1;
		}
		
		side = ((IP & (1lu << i)) >> i);
		if(NULL == parent->children[side])
		{
			return 0;
		}
		parent = parent->children[side];		
	}
		
	return 1;
}

static int NotReachedTheEnd(dhcp_t *dhcp, int IP)
{
	int mask = ~(MASK_F << dhcp->free_bits); 	

	if((mask & BROADCAST_ADDRESS) != (mask & IP))
	{	
		return 1;
	}

	return 0;
}

static void SetAllocatedIP(int IP, ip_t allocated_ip)
{	
	char *ptr = (char *) &IP;
	size_t i = 0;
	
	for(i = 0; i < sizeof(ip_t); ++i, ++ptr)
	{
		allocated_ip[sizeof(ip_t) - 1 - i] = *ptr;
	}
	
	/* PrintIP("SetAllocatedIP: allocated_ip", allocated_ip); */
}

static int IpToInt(const ip_t ip)
{
	int result = 0;
	size_t i = 0;
	for (i= 0; i < sizeof(ip_t); ++i)
	{
		result <<= 8;
		result |= ip[i];
	}
	return result;
}

static size_t CountFreeAux(dhcp_node_t *node, size_t bits)
{
	if (NULL == node)
	{
		return 1lu << bits;
	}
	
	if (node->is_full)
	{
		return 0;
	}
	
	return CountFreeAux(node->children[0], bits - 1) + CountFreeAux(node->children[1], bits - 1);
}

/**************************** Debug Functions to Print IPs **************************/
static void PrintIP(char *comment, ip_t IP)
{
 	size_t i = 0;

	printf("%s: ", comment);
	for(i = 0; i < sizeof(ip_t); ++i)
	{
		printf("%d ", IP[i]);
	}
	printf("\n");
}

static void PrintConstIP(char *comment, const ip_t IP)
{
 	size_t i = 0;

	printf("%s: ", comment);
	for(i = 0; i < sizeof(ip_t); ++i)
	{
		printf("%d ", IP[i]);
	}
	printf("\n");
}

