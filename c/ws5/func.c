


#include<stdio.h> /* printf*/
#include<stdlib.h> /* Malloc */
#include<assert.h> /* Assert */
#include<string.h> /* strlen */

#include"ws5.h"


typedef int (*p_tostrcmp)(const char*,const char*);
typedef status_t (*p_status_t)(const char *, const char *);


typedef struct
{
    char *command;
    p_tostrcmp Checking;
    p_status_t Action;
    
} mySuperStruct;


status_t Exit(const char* x,const char* y)
{
	(void)x;
	(void)y;
	
	exit(0);
	return SUCCESS;
}

status_t Remove(const char *file,const char *str)
{	
	(void) *str;
	assert(NULL != str);
	assert(NULL != file);	
	
	if(0 != remove(file))
	{
		perror("Can't remove file");
		return EXIT;
	}
	puts("File removed");
	return SUCCESS;
}

status_t Count(const char *file, const char *str)
{
	FILE* f;
	char c;
	int counter = 1;
	assert(NULL != str);
	assert(NULL != file);
	f = fopen(file, "r");
	
	if(NULL == f)
	{
		perror("Can't open file");
		return EXIT;
	}
	
	for(c = getc(f); c != EOF; c = getc(f))
	{
		if('\n' == c)
		{
			++counter;
		}
	}
	printf("Number of lines: %d\n", counter);
	fclose(f);
	return SUCCESS;
}

int StrNcmp(const char *str1, const char *str2)
{	
	assert(NULL != str1);
	assert(NULL != str2);
	(void)str2;
	return strncmp(str1, str2, 1);
}

status_t PreAppender(const char *str1, const char *str2)
{	
	FILE* f;
	FILE* new_f;
	
	char temp_str[100];
	assert(NULL != str1);
	assert(NULL != str2);
	

	new_f = fopen("new.txt", "w+");
	f = fopen(str1, "r");
	
	if(NULL == new_f || NULL == f)
	{
		perror("Can't open file");
		return EXIT;
	}
	fprintf(new_f,"%s", str2+1);
	while(fgets(temp_str, sizeof(temp_str), f) != 0)
	{	
		fputs(temp_str, new_f);		
	}
	
	remove(str1);
	rename("new.txt", "txt.txt");
	
	fclose(new_f);
	fclose(f);
	
	return SUCCESS;
}

status_t Appender(const char *str1, const char *str2)
{
	FILE* f;
	assert(NULL != str1);
	assert(NULL != str2);
	f = fopen(str1, "a");
	
	if( NULL == f)
	{
		perror("Can't open file");
		return (-1);
	}
	fprintf(f,"%s", str2);
	fclose(f);
	return SUCCESS;
}

int StubFunc(const char *str1, const char *str2)
{
	(void)str1;
	(void)str2;
	
	return 0;
}


mySuperStruct* SuperCreater(char arr[], p_tostrcmp funcCheck, p_status_t funcAct)
{
    mySuperStruct *bigStruct = (mySuperStruct*)malloc(sizeof(mySuperStruct));
    bigStruct -> command = arr;
    bigStruct -> Checking = funcCheck;
    bigStruct -> Action = funcAct;
    return bigStruct;
}



int logger(char *argv[]){

	int i;
	char nameCommand[50];
	char nameFile_0[8] = "-remove";
	char nameFile_1[] = "-count";
	char nameFile_2[] = "-exit";
	char nameFile_3[] = "<";
	char nameFile_4[] = " ";
	status_t SPECIAL;
	mySuperStruct* arrayOFsuper[5];
	SPECIAL = SUCCESS;
	
	if(!argv[1])
	{
		puts("You must add the FILE!Try again!");
		return -1;
	}
	
	arrayOFsuper[0] = SuperCreater(nameFile_0, strcmp, Remove);
	arrayOFsuper[1] = SuperCreater(nameFile_1, strcmp, Count);
	arrayOFsuper[2] = SuperCreater(nameFile_2, strcmp, Exit);
	arrayOFsuper[3] = SuperCreater(nameFile_3, StrNcmp, PreAppender);
	arrayOFsuper[4] = SuperCreater(nameFile_4, StubFunc, Appender);
	
	
	while(SPECIAL!=EXIT)
	{
		printf("Insert the command: \n");
		scanf("%[^\n]%*c", nameCommand); /* this staff for feading with spaces*/
		for(i = 0; i < 5; ++i)
		{
			if( !arrayOFsuper[i] -> Checking(arrayOFsuper[i] -> command, nameCommand) )
			{
				SPECIAL = arrayOFsuper[i] -> Action(argv[1], nameCommand);
				break;
			}
		}	
	}
	return 0;
}



