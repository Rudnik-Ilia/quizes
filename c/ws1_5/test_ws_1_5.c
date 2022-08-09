#include<stdio.h>
#include<assert.h>
#include<string.h>
#include"ws1_5.h"

int main()
{
	char word_1[] = "ilia";
	char word_2[] = "eeeeeeeeeeeeeeeeeeeeeeeee";
	printf("%ld - %ld\n", StrLen(word_1), strlen(word_1));
	printf("%ld - %ld\n", StrLen(word_2), strlen(word_2));
	
	if(StrLen(word_1) == strlen(word_1))
	{
		printf("%s\n", "Passed");
	}
	else
	{
		printf("%s\n", "fail");
	}
	
	
	
	return 0;

}
