#include<stddef.h>
#include<assert.h>
#include"ws1_5.h"

int StrCmp(const char *first_word, const char *second_word)
{ 
	assert(NULL != first_word);
	assert(NULL != second_word);
	for (;*first_word == *second_word; first_word++, second_word++) {
		
    		if (*first_word == '\0')
    		{
    	 		return (*first_word - *second_word);
    		}
  	} 
  	
  	return(*first_word - *second_word);
}

size_t StrLen(const char *word)
{
	size_t count = 0;
	
	assert(NULL != word);
	
	while(*word++ != '\0')
	{
		count++;
	}	
	return count;
}
