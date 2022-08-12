
#include"ws3.h"


void Test_SummArray()
{
	int arr[2][3] = {{1,2,3},{4,5,6}};
	printf("Test_SummArray");
	if(SummArray(arr, 2, 3)[0] == 6 && SummArray(arr, 2, 3)[1] == 15) printf("PASS\n");
	else printf("FAIL!");
}

void Test_Joses()
{
	int solgers[] = {1,2,3,4,5,6,7,8,9,10,11,12};
	int solgers_2[] = {1,2,3,4,5,6,7};
	
	if (JosesProblem(solgers, 12) == 9 &&  JosesProblem(solgers_2, 7) == 7) printf("PASS\n");
	else printf("FAIL!");
}





