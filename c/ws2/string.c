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
	
	
	for (;*first_word == *second_word && count < num; first_word++, second_word++) {
		count++;
		if( count == num)
		{
		 	return(*first_word - *second_word);
		}
    		
  	} 
  	//printf("%d - %d\n", *first_word, *second_word);
  	return(*first_word - *second_word);
}




