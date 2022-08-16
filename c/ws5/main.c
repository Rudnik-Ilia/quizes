/**********************
* Title : Worksheet 5 
* Author: Ilia Rudnik
* Reviewer: 
* Date : 16/08/2022
***********************/


#include<stdio.h> /* printf*/
#include<stdlib.h> /* Malloc */
#include<assert.h> /* Assert */
#include<string.h>

#include"ws5.h"


typedef void (*p_func)(int);

typedef int (*p_tostrcmp)(const char*,const char*);

/*simple struct*/
typedef struct
{
    int number;
    p_func PrintMe;
    
} myStruct;

/* big another struct*/
typedef struct
{
    char *command;
    p_tostrcmp Checking;
    p_tostrcmp Action;
    
} mySuperStruct;


void Print(int number)
{
	printf("%d\n", number);
}

int Print_2(const char* x,const char* y)
{
	(void)x;
	(void)y;
	printf("YES\n");
	return 0;
}

int Exit(const char* x,const char* y)
{
	(void)x;
	(void)y;
	
	exit(0);
	return 0;
}

int Remove(const char *file,const char *str)
{	
	(void) *str;
	assert(NULL != str);
	assert(NULL != file);	
	
	if(0 != remove(file))
	{
		perror("Can't remove file");
		return (-1);
	}
	puts("File removed");
	return 0;
}

int Count(const char *file, const char *str)
{
	FILE* f;
	char c;
	int counter = 0;
	
	assert(NULL != str);
	assert(NULL != file);
	
	
	f = fopen(file, "r");
	
	if(NULL == f)
	{
	perror("Can't open file");
	return (-1);
	}
	
	for(c = getc(f); c != EOF; c = getc(f))
	{
		if('\n' == c)
		{
		++counter;
		}
	}
	printf("Number of lines: %d\n", counter);
	return 0;
}

int StrNcmp(const char *str1, const char *str2)
{	
	
	assert(NULL != str1);
	assert(NULL != str2);
	(void)str2;
	return strncmp(str1, str2, 1);
}

int Appender(const char *str1, const char *str2)
{	
	
	printf("%s\n", str2);
	return 0;
}







/* simple creater func for struct*/
myStruct* Creater(int a, p_func func)
{
    myStruct *print_me = (myStruct*)malloc(sizeof(myStruct));
    assert(print_me);
    print_me -> number = a;
    print_me -> PrintMe = func;
    return print_me;
}

/*super creater func for big struct*/
mySuperStruct* SuperCreater(char arr[], p_tostrcmp funcCheck, p_tostrcmp funcAct)
{
    mySuperStruct *bigStruct = (mySuperStruct*)malloc(sizeof(mySuperStruct));
    
    bigStruct -> command = arr;
    bigStruct -> Checking = funcCheck;
    bigStruct -> Action = funcAct;
    
    return bigStruct;
}








int main(int argc, char *argv[], char *env[])
{	
	/*
	int i;
	myStruct *arrayOFstruct[10];
	
	for(i = 0; i < 10; ++i)
	{
		arrayOFstruct[i] = Creater((i+1), Print);
	}
	
	for(i = 0; i < 10; ++i)
	{
		arrayOFstruct[i] -> PrintMe(i);
	}
	*/
	int i;
	int status;
	int count;
	char nameCommand[10];
	char nameFile_0[8] = "-remove";
	char nameFile_1[] = "-count";
	char nameFile_2[] = "-exit";
	char nameFile_3[] = "<";
	mySuperStruct* arrayOFsuper[4];
	
	assert(argv[1]);
	
	
	
	arrayOFsuper[0] = SuperCreater(nameFile_0, strcmp, Remove);
	arrayOFsuper[1] = SuperCreater(nameFile_1, strcmp, Count);
	arrayOFsuper[2] = SuperCreater(nameFile_2, strcmp, Exit);
	arrayOFsuper[3] = SuperCreater(nameFile_3, StrNcmp, Appender);
	
	while(1)
	{
		printf("Insert the command: \n");
		scanf("%s", &nameCommand);
		for(i = 0; i < 4; ++i)
		{
			if( !arrayOFsuper[i] -> Checking(arrayOFsuper[i] -> command, nameCommand) )
			{
				arrayOFsuper[i] -> Action(argv[1], nameCommand);
			}
			
		}	
	}
		
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	
	
	
	
	
	
	
















(void)argc;
(void)env;

return 0;
}

