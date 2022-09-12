
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define TEST(a, b) ((a) != (b)) ? printf("TEST FAIL! ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__) : puts("PASS");


typedef struct node
{
	void *data;
	struct node *next;
}node_t;


node_t *BornNode(void *data, void *next)
{
	node_t *new_node = (node_t*)malloc(sizeof(node_t));
	assert(data);
	
	if(NULL == new_node)
	{
		return NULL;
	}
	new_node->data = data;
	new_node->next = next;
	return new_node;
}

	

node_t *Flip(node_t * head)
{
	node_t *curr = NULL;
	node_t *next = NULL;
	assert(head);
	while(NULL != head)
	{
		head->next = curr;
		next = head->next;
		curr = head;
		head = next;
	}

	return curr;	
}
 
int HasLoop(node_t * head)
{
	node_t *a = NULL;
	node_t *b = NULL;
	assert(head);
	a = head;
	b = head;
	
	while(a && b && b->next)
	{
		a = a->next;
		b = b->next->next;
		if(a == b)
		{
			return 1;
		}
	}
	return 0;
}





node_t *FindIntersection(node_t * first_head, node_t *second_head)
{
	node_t * ptr1 = first_head;
	node_t * ptr2 = second_head;
	assert(ptr1);
	assert(ptr2);
	
	while(ptr1)
	{
		if(ptr1 == ptr2)
		{
			return first_head;
		}
		while(ptr2)
		{	
			if(ptr1 == ptr2)
			{
				return first_head;
			}
			ptr2 = ptr2->next;
		}
	ptr1 = ptr1->next;
	ptr2 = second_head;
	}
	return NULL;
}

void Test_HasLoop();
void Test_Flip();
void Test_FindIntersec();	

int main()
{
	Test_Flip();
	Test_HasLoop();
	Test_FindIntersec();
	
return 0;
}

void Test_FindIntersec()
{
	char arr[] = {'a','b','c'};
	node_t * item1 = BornNode(&arr[2], NULL);
	node_t * item2 = BornNode(&arr[1], item1);
	node_t * item3 = BornNode(&arr[0], item2);
	
	
	char arr1[] = {'e','d','f','g','i'};
	node_t * item_1 = BornNode(&arr[4], NULL);
	node_t * item_2 = BornNode(&arr[3], item_1);
	node_t * item_3 = BornNode(&arr[2], item_2);
	node_t * item_4 = BornNode(&arr[1], item_3);
	node_t * item_5 = BornNode(&arr[0], item_4);
	
	if(FindIntersection(item3, item_5) == NULL)
	{
		puts("PASS");
	}
	else
	{
		puts("FAIL");
	}
	
	
	item1->next = item_2;
	
	if(FindIntersection(item3, item_5) != NULL)
	{
		puts("PASS");
	}
	else
	{
		puts("FAIL");
	}
	
	free(item_5);
	free(item_4);
	free(item_3);
	free(item_2);
	free(item_1);
	
	free(item3);
	free(item2);
	free(item1);
}
	



void Test_HasLoop()
{
	char arr[] = {'a','b','c','d','e'};
	node_t * item1 = BornNode(&arr[4], NULL);
	node_t * item2 = BornNode(&arr[3], item1);
	node_t * item3 = BornNode(&arr[2], item2);
	node_t * item4 = BornNode(&arr[1], item3);
	node_t * item5 = BornNode(&arr[0], item4);
	
	TEST(HasLoop(item5), 0);
	item1->next = item4;
	TEST(HasLoop(item5), 1);
	item1->next = item5;
	TEST(HasLoop(item5), 1);
	
	free(item5);
	free(item4);
	free(item3);
	free(item2);
	free(item1);
}

void Test_Flip()
{	
	char arr[] = {'a','b','c'};
	node_t * item1 = BornNode(&arr[2], NULL);
	node_t * item2 = BornNode(&arr[1], item1);
	node_t * item3 = BornNode(&arr[0], item2);
	Flip(item3);
	TEST(item3->next, 0);
	TEST(*(char*)item1->data, 'c');
	free(item3);
	free(item2);
	free(item1);
}

