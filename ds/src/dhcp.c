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
void _destroy(dhcp_node_t *node);
static void Print2D(dhcp_node_t *root, int space);


static void IncrementAddr(ip_t suggested_ip, int index);
status_t IsFreeAddr(dhcp_node_t *node, size_t address, size_t shift);
/**********************************************************************************************API*/

dhcp_t *CreateDHCP(const ip_t subnet_ip, size_t free_bits)
{	
	size_t submask = 0;
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
	if(NULL == dhcp)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		free(dhcp);
		return NULL;
	}
	
	submask = FULL_MASK & ~(IpToSizeT(subnet_ip));
	
	if(FAILED_ALLOCATION == _allocate(dhcp->trie, IpToSizeT(network_add) , dhcp->free_bits))
	{ 
		puts("ERROR");
	}
	
	if(FAILED_ALLOCATION == _allocate(dhcp->trie, IpToSizeT(server_add) , dhcp->free_bits))
	{
		puts("ERROR");
	}
	if(FAILED_ALLOCATION == _allocate(dhcp->trie, IpToSizeT(broadcast_add) , dhcp->free_bits))
	{
		puts("ERROR");
	}	
	printf("RRR: %ld\n", submask);	
	Print2D(dhcp->trie, 0);
	return dhcp; 
}

status_t AllocateIP(dhcp_t *dhcp, ip_t suggested_ip, ip_t allocated_ip)
{

	status_t status = FAILED_ALLOCATION;
	/*
	printf("IS FREE: %d\n", IsFreeAddr(dhcp->trie, IpToSizeT(suggested_ip), dhcp->free_bits - 1));
	size_t submask = FULL_MASK;
	submask >>= ~(IpToSizeT(dhcp->subnet_ip));
	submask ^= FULL_MASK;
	printf("IS FREE_1: %ld\n", submask);
	*/
	
	if (dhcp->trie->is_full)
	{
		printf("ALL BUSY\n");
		return  FAILED_ALLOCATION;
	}
	/*
	if(0 == IpToSizeT(suggested_ip))
	{		
		printf("ZERO\n");
		
		memcpy(allocated_ip, network_add, IP_SIZE);
		allocated_ip[IP_SIZE-1]++;
	}
	*/
	else
	{	
		printf("Record\n");
		memcpy(allocated_ip, suggested_ip, IP_SIZE);
	}
	
	while(!(status = IsFreeAddr(dhcp->trie, IpToSizeT(allocated_ip), dhcp->free_bits)))
	
	{
		printf("!!!\n");
		IncrementAddr(allocated_ip, IP_SIZE - 1);
	}
	
	status = _allocate(dhcp->trie, IpToSizeT(suggested_ip), dhcp->free_bits);
	
	Print2D(dhcp->trie, 0);
	return status;
}

status_t IsFreeAddr(dhcp_node_t *node, size_t address, size_t shift)
{
	size_t child = ((address << 1) >> shift) & 1;

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
		printf("!!!\n");
		++suggested_ip[index];
	}
}
	
status_t _allocate(dhcp_node_t *node, size_t addr, size_t bits)
{
	size_t child = 0;
	status_t status = 0;
	
	assert(NULL != node);
	
	child = ((addr << 1) >> bits) & 1;
	printf("BIT:  %ld\n", child);

	if(NULL == node->children[child])                                     /*TODO -1 or 1*/
	{	
		if(0 == bits)
		{	
			printf("!!!\n");
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
	if(NULL != dhcp->trie)
	{
		_destroy(dhcp->trie);
	}
	free(dhcp);
}

/*********************************************************************************************AUX**/
static dhcp_node_t* CreateNode(void)
{	
	dhcp_node_t *node = NULL;
	printf("CREATE\n");
	
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

void _destroy(dhcp_node_t *node)
{
	if(NULL == node)
	{
		return;
	}
	_destroy(node->children[0]);
	_destroy(node->children[1]);
	free(node);
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

size_t CountFree(dhcp_t *dhcp)
{
	assert(NULL != dhcp);

	return _countFree(dhcp->trie, dhcp->free_bits);
}


/*

static void UpdateIsAllocd(dhcp_node_t *node, int child)
{
	
	if ((NULL != node->children[!child]) && node->children[child]->is_full && node->children[!child]->is_full)
	{
		node->is_full = 1;
	}
}

static void UpdateIP(size_t addr, size_t index)
{
	addr = addr ^ (1 << index);
}

*/












