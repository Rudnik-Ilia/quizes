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

int OriginalStrCmp (const char *p1, const char *p2)
{
	const unsigned char *s1 = (const unsigned char *) p1;
  	const unsigned char *s2 = (const unsigned char *) p2;
	unsigned char c1, c2;
  	do
    	{
      		c1 = (unsigned char) *s1++;
      		c2 = (unsigned char) *s2++;
      		printf("%c",c1);
      	if (c1 == '\0')
        	return c1 - c2;
    	}
  	while (c1 == c2);
  	return c1 - c2;
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

int main()
{
	char a = 'a';
	char* p_a;
	p_a = a;
	del a;
	
	//printf("%d",StrCmp(NULL,"Infiniqqq"));
	printf("%d",StrLen(&p_a));

	

}

