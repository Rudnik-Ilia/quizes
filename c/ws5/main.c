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

typedef int (*p_tostrcmp)(const char*, const char*);


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
    p_func Action;
    
} mySuperStruct;


void Print(int number)
{
	printf("%d\n", number);
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
mySuperStruct* SuperCreater(char arr[], p_tostrcmp funcCheck, p_func funcAct)
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
	int count;
	char nameCommand[10];
	char nameFile_0[8] = "-remove";
	char nameFile_1[] = "-count";
	char nameFile_2[] = "-exit";
	
	p_tostrcmp* StrCmp;
	mySuperStruct* SS_0;
	mySuperStruct* SS_1;
	mySuperStruct* SS_2;
	mySuperStruct* arrayOFsuper[3];
	
	
	(void)argc;
	(void)env;
	


	
	arrayOFsuper[0] = SuperCreater(nameFile_0, strcmp, Print);
	arrayOFsuper[1] = SuperCreater(nameFile_1, strcmp, Print);
	arrayOFsuper[2] = SuperCreater(nameFile_2, strcmp, Print);
	
	
	/*
	printf("%s",arrayOFsuper[0] -> command);
	printf("%s",nameCommand);
	printf("%d",strcmp(arrayOFsuper[0] -> command, nameCommand));
	count = 0;
	printf("%d", arrayOFsuper[0] -> Checking(arrayOFsuper[0] -> command, nameFile_0));
	*/
	while(count != 3)
	{
		printf("Insert the command: \n");
		scanf("%s", &nameCommand);
		for(i = 0; i < 3; ++i)
		{
			if( arrayOFsuper[i] -> Checking(arrayOFsuper[i] -> command, nameCommand) )
			{
				printf("PASS\n");
			}
			else
			{
				printf("FAIL\n");
			}
			++count;
		}
		
			
	}
		
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	
	
	
	
	
	
	


















return 0;
}

