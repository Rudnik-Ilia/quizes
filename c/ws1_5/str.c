#include <stdio.h>
#include<assert.h>







int StrCmp(char *first_word, char *second_word)
{ 
	assert((NULL != first_word && NULL != second_word) && "SOMETHING WRONG!CHECK PARAM!");
	for (;*first_word == *second_word; first_word++, second_word++) {
		
    		if (*first_word == '\0')
    		{
    	 		return (*first_word - *second_word);
    		}
  	} 
  	
  	return(*first_word - *second_word);
}

int StrLen(char *word)
{
	int count = 0;
	
	assert(NULL != word && "SOMETHING WRONG!CHECK PARAM!");
	
	while(*word++ != '\0')
	{
		count++;
	}	
	return count;
}
