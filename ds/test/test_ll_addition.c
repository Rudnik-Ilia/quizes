
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

size_t LenOf(node_t *head)
{
	size_t count = 0;
	assert(head);
	while(head)
	{
		head = head->next;
		++count;
	}
	return count;
}



node_t *FindIntersection(node_t * first_head, node_t *second_head)
{
	size_t len1 = LenOf(first_head);
	size_t len2 = LenOf(second_head);
	node_t *res = NULL;
	
	while(len1 > len2)
	{
		first_head = first_head->next;
		--len1;
	}
	while(len1 < len2)
	{
		second_head = second_head->next;
		--len2;
	}
	while((first_head != NULL || second_head != NULL) && first_head != second_head)
	{
		first_head = first_head->next;
		second_head = second_head->next;
		res = first_head;
	}
	return res;
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

