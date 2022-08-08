#include<stddef.h>
#include<assert.h>
#include<stdio.h>
#include"string.h"





char *StrCpy(char *dest,  char *src) 
{
	assert(NULL != dest && "First");
	assert(NULL != src && "second");
	
	char *start = dest;
	assert(NULL != start && "Third");
    
    	while (*src)
    	{
    		*start++ = *src++;
    	}
        		
    	return dest;
}

char *StrCpyNum_2(char *dest,  char *src, int num) 
{
	assert(NULL != dest && "First");
	assert(NULL != src && "second");
	
	char *start = dest;
	int count = 0;
	assert(NULL != start && "Third");
    
    	while (count--)
    	{
    		*start++ = *src++;
    	}
        		
    	return dest;
}

char *StrCpyNum(char *dest,  char *src, int num) 
{
	assert(NULL != dest && "First");
	assert(NULL != src && "second");
	int count;

               for (count = 0; count < num && src[count] != '\0'; count++)
                   dest[count] = src[count];
               for ( ; count < num; count++)
                   dest[count] = 0;

               return dest;
}

int StrCmpNum(const char *first_word, const char *second_word, size_t num )
{ 
	assert(NULL != first_word);
	assert(NULL != second_word);
	
	size_t count = 0;
	
	
	for (;*first_word == *second_word && count < num; first_word++, second_word++) 
	{
		count++;
		if( count == num-1)
		{
		 	return(*first_word - *second_word);
		}
    		
  	} 
  	//printf("%d - %d\n", *first_word, *second_word);
  	return(*first_word - *second_word);
}

int StrCaseCmp( char *first_word,  char *second_word)
{
	assert(NULL != first_word);
	assert(NULL != second_word);
	
	char *p_f = first_word;
	char *p_s = second_word;
	int result = 0;
	
	
	for(; (tolower(*p_f) - tolower(*p_s)) == 0; *p_f++, *p_s++)
	{
		
		if(*p_f == '\0')
		{
			return tolower(*p_f) - tolower(*p_s);
		}
		 
	}
	return tolower(*p_f) - tolower(*p_s);
}

char *StrChar(char *word, char x)
{
	assert(NULL != word);
	char *p_word = word;
	while(*p_word++ != x)
	{
		if(*p_word == '\0')
		{
			return NULL;
		}
		if(*p_word == x)
		{
			return p_word;
		}
	}
	return p_word;
}

char *StrDup(const char *string)
{
	assert(NULL != string);
	
	const char * p_res;
	
	return p_res;
}






































