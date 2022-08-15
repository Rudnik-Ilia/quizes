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
	
	char nameFile[50];
	
	p_tostrcmp* StrCmp;
	mySuperStruct* SS;
	
	
	(void)argc;
	(void)env;
	
	printf("Insert the command: \n");
	scanf("%s", &nameFile);
	
	
	
	SS = SuperCreater(nameFile, strcmp, Print);
	
	printf("%d",SS -> Checking(SS -> command, argv[1]));
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	
	
	
	
	
	
	


















return 0;
}

