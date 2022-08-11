#include<stdio.h>
#include<stdlib.h> /* Malloc */
#include<assert.h> /* Assert */
#include<string.h>
#include"func.c"
#include"ws3.h"


void Test_SummArray();
void PrintVar();
/*

void Josephus_circle(int arr[], int len)
{
	int tmp_first;
	int i;
	int n = 1;
	tmp_first = 0;
	
	
	while(n--)
	{
		tmp_first = arr[0];
		
		for(i = 0; i < len ; ++i)
		{
			arr[i] = arr[i+1];
		}
		arr[len-1] = tmp_first;
			
	}			
	
}


void Killer(int arr[], int len)
{
	int *p = arr;
	
	
	while(1)
	{
		if(0 == *p % 2)
		{
			*p = 0;
		}
		
		Josephus_circle(arr,len);
	}	
	
}
*/

int main(int argc, char *argv[], char *env[])
{


	 /*
	 
	 PrintArray(arr, 2, 3);
	 
	 
	 PrintArray_2((int*)arr, 2, 3);
	 
	 
	 PrintArray_3(p_arr, 2, 3);
	 for(i = 0; i < 17 ; ++i) printf("%d\n", solgers[i]);
	*/
	
	 int i;
	 int *p_i;
	 int solgers[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
	 
	 
	 for(i = 0; i < 17; ++i)
	 {
		 if(p_i[i]%2 == 0)
		 {
		  	p_i[i] = 0; 
		 }
	 }
	 
	 
	 for(i = 0; i < 17 ; ++i) printf("%d\n", solgers[i]);
	 
	 
	

	
	
	
	
	
	
	
	 
	
 


	return 0;
}








