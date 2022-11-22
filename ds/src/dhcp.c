#include <stdio.h> /*debug*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /* */
#include <string.h> /* memcpy */

#include "dhcp.h"
#include "utils.h" /*LOGERROR*/

#define FULL_MASK (0xFFFFFFFF)
#define BYTE (8)
#define MAX_CELL (255)
#define IP_SIZE (4)

typedef struct dhcp_node
{
	struct dhcp_node *children[2];
	int is_full;
}dhcp_node_t;

struct dhcp
{
	ip_t subnet_ip;
	dhcp_node_t *trie;
	size_t free_bits;
};

static ip_t network_add = {0, 0, 0, 0};
static ip_t server_add = {0, 0, 0, 254};
static ip_t broadcast_add = {0, 0, 0, 255};

/**********************************************************************************************AUX*/

static dhcp_node_t* CreateNode(void);
static size_t IpToSizeT(const ip_t address);
status_t _allocate(dhcp_node_t *node, size_t addr, size_t bits);
static void _destroy(dhcp_node_t *node);
static void Print2D(dhcp_node_t *root, int space);

static void IncrementAddr(ip_t suggested_ip, int index);
status_t IsFreeAddr(dhcp_node_t *node, size_t address, size_t shift);

static int _freeIp(dhcp_node_t **node, size_t addr, size_t bits);
static size_t _countFree(dhcp_node_t *node, size_t bits);
/**********************************************************************************************API*/

dhcp_t *CreateDHCP(const ip_t subnet_ip, size_t free_bits)
{	
	dhcp_t *dhcp = NULL;
	
	dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
	if(NULL == dhcp)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}
	memcpy(dhcp->subnet_ip, subnet_ip, IP_SIZE);
	
	dhcp->free_bits = free_bits;
	dhcp->trie = CreateNode();
	
	if(NULL == dhcp->trie)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		free(dhcp);
		return NULL;
	}
	if(FAILED_ALLOCATION == _allocate(dhcp->trie, IpToSizeT(network_add), dhcp->free_bits))
	{ 
		LOGERROR("SORRY, NO NETWORK ADDR");
	}
	if(FAILED_ALLOCATION == _allocate(dhcp->trie, IpToSizeT(server_add), dhcp->free_bits))
	{
		LOGERROR("SORRY, NO SERVER ADDR");
	}
	if(FAILED_ALLOCATION == _allocate(dhcp->trie, IpToSizeT(broadcast_add), dhcp->free_bits))
	{
		LOGERROR("SORRY, NO BROADCAST ADDR");
	}		
	return dhcp; 
}

status_t AllocateIP(dhcp_t *dhcp, const ip_t suggested_ip, ip_t allocated_ip)
{
	status_t status = FAILED_ALLOCATION;
	status_t status_1 = 0;
	
	assert(NULL != dhcp);
	
	if (dhcp->trie->is_full)
	{
		return  FAILED_ALLOCATION;
	}
	if(0 == IpToSizeT(suggested_ip))
	{		
		memcpy(allocated_ip, dhcp->subnet_ip, IP_SIZE);
		allocated_ip[IP_SIZE-1]++;
		status_1 = ANOTHER_IP_ALLOCATED;
	}
	else
	{	
		memcpy(allocated_ip, suggested_ip, IP_SIZE);
	}
	while(SUGGESTED_IP_ALLOCATED != (status = IsFreeAddr(dhcp->trie, IpToSizeT(allocated_ip), dhcp->free_bits)))
	{	
		IncrementAddr(allocated_ip, IP_SIZE - 1);
		status_1 = ANOTHER_IP_ALLOCATED;
	}
	status = _allocate(dhcp->trie, IpToSizeT(allocated_ip), dhcp->free_bits);
	
	return status_1;
}

status_t IsFreeAddr(dhcp_node_t *node, size_t address, size_t shift)
{
	size_t child = 0;
	
	assert(NULL != node);
	
	child = ((address << 1) >> shift) & 1;

	if (node->is_full)
	{
		return 1;
	}
	if(NULL == node->children[child])
	{
		return 0;
	}
	return IsFreeAddr(node->children[child], address, shift - 1);

	return 0;	
}

static void IncrementAddr(ip_t suggested_ip, int index)
{
	if (0 > index)
	{
		return;
	}
	if (MAX_CELL == suggested_ip[index])
	{
		IncrementAddr(suggested_ip, index - 1);
		suggested_ip[index] = 0;
	}
	else 
	{	
		++suggested_ip[index];
	}
}
	
status_t _allocate(dhcp_node_t *node, size_t addr, size_t bits)
{
	size_t child = 0;
	status_t status = 0;
	
	assert(NULL != node);
	
	child = ((addr << 1) >> bits) & 1;

	if(NULL == node->children[child])
	{                                   
		if(0 == bits)
		{	
			node->is_full = 1;
			return 0;
		}
		node->children[child] = CreateNode();
		if(NULL == node->children[child])
		{	
			LOGERROR("SORRY, NO MEMORY FOR YOU");
			return FAILED_ALLOCATION;
		}
			
	}
	status = _allocate(node->children[child], addr, bits - 1);
	
	if ((0 == status) && (NULL != node->children[!child]) && node->children[0]->is_full && node->children[1]->is_full)
	{
			node->is_full = 1;
	}
		
	return status;
}

void DestroyDHCP(dhcp_t *dhcp)
{
	assert(NULL != dhcp);	
	
	if(NULL != dhcp->trie)
	{
		_destroy(dhcp->trie);
	}
	free(dhcp);
}

size_t CountFree(dhcp_t *dhcp)
{
	assert(NULL != dhcp);

	return _countFree(dhcp->trie, dhcp->free_bits);
}

void FreeIp(dhcp_t *dhcp, const ip_t ip_to_free)
{
	assert(NULL != dhcp);
	
	_freeIp(&dhcp->trie, IpToSizeT(ip_to_free), dhcp->free_bits);
}
/*********************************************************************************************AUX**/

static dhcp_node_t* CreateNode(void)
{	
	dhcp_node_t *node = NULL;
	
	node = (dhcp_node_t *)calloc(1, sizeof(dhcp_node_t));
	if(NULL == node)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}
	
	return node;
}

static size_t IpToSizeT(const ip_t address)
{
	size_t output = 0;
	size_t i = 0;
	for (i= 0; i < IP_SIZE; ++i)
	{
		output <<= BYTE;
		output |= address[i];
	}
	return output;
}

static void _destroy(dhcp_node_t *node)
{
	if(NULL == node)
	{
		return;
	}
	_destroy(node->children[0]);
	_destroy(node->children[1]);
	free(node);
}

static size_t _countFree(dhcp_node_t *node, size_t bits)
{
	if (NULL == node)
	{
		return 1 << bits;
	}
	if (node->is_full)
	{
		return 0;
	}
	return _countFree(node->children[0], bits - 1) + _countFree(node->children[1], bits - 1);
}



static int _freeIp(dhcp_node_t **node, size_t addr, size_t bits)
{
	int child = ((addr << 1) >> bits) & 1;

	if (0 == bits)								
	{
		(*node)->is_full = 0;
		free(*node);
		*node = NULL;
		node = NULL;
		return 0;
	}
	if (NULL == (*node)->children[child] || 0 != _freeIp(&(*node)->children[child], addr, bits - 1))
	{
		return 1;
	}

	if (NULL == (*node)->children[child] && NULL == (*node)->children[!child])
	{
		free(*node); 
		*node = NULL;
		node = NULL; 
	}
	else						
	{
		(*node)->is_full = 0;
	}
	return 0;
}

void PrintTrie(dhcp_t *dhcp)
{
	Print2D(dhcp->trie, 0);
	printf("-------------------------------------------------------------------------\n");
}

static void Print2D(dhcp_node_t *root, int space)
{
	int i = 0;
	if (root == NULL)
	{
		return;
	}
	space += 15;
	Print2D(root->children[1], space);
	
	for(i = 15; i < space; ++i)
	{
		printf(" ");
	}
	printf("%d \n", (root->is_full));
	printf("\n");
	Print2D(root->children[0], space);
}












