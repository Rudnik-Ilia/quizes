#include <assert.h>

#include"utils.h"
#include"queue.h"
#include "SLL.h"

int main()
{	
	size_t i;
	int arr[] = {10,20,30,40,50};
	int arr2[] = {60, 70, 80};
	
	queue_t *que= QueueCreate();
	queue_t *que2= QueueCreate();
	
	printf("Test is empty before adding: \n");
	TEST(QueueIsEmpty(que), 1);
	TEST(QueueIsEmpty(que2), 1);
	printf("-----------------------------------------\n");
	
	for(i = 0;i < 5; ++i)
	{
		QueueEnqueue(que, &arr[i]);
	}
	
	for(i = 0;i < 3; ++i)
	{
		QueueEnqueue(que2, &arr2[i]);
	}
	
	printf("Test after create: \n");
	TEST(QueueSize(que), 5);
	TEST(QueueSize(que2), 3);
	printf("-----------------------------------------\n");
	
	printf("Test delete: \n");
	QueueDequeue(que);
	QueueDequeue(que2);
	
	TEST(QueueSize(que), 4);
	TEST(QueueSize(que2), 2);
	printf("-----------------------------------------\n");
	
	printf("Test peek: \n");
	TEST(*(int*)QueuePeek(que), 20);
	TEST(*(int*)QueuePeek(que2), 70);
	printf("-----------------------------------------\n");
	
	printf("Test is empty: \n");
	TEST(QueueIsEmpty(que), 0);
	TEST(QueueIsEmpty(que2), 0);
	printf("-----------------------------------------\n");
	
	printf("Test for append: \n");
	QueueAppend(que, que2);
	TEST(QueueIsEmpty(que2), 1);
	TEST(QueueSize(que), 6);
	
	QueueDestroy(que2);
	QueueDestroy(que);

return 0;
}
