
#include"ws3.h"


void Test_SummArray()
{
	int arr[2][3] = {{1,2,3},{4,5,6}};
	printf("Test_SummArray");
	if(SummArray(arr, 2, 3)[0] == 6 && SummArray(arr, 2, 3)[1] == 15) printf("PASS");
	else printf("FAIL!");
}





