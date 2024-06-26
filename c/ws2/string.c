#include<stddef.h>
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


int BoomHelper(int);
char *strdup(const char *x);

int StrLen( char *str)
{
	assert(NULL != str)
	const char *p = str;
	while ( *p != '\0' ) ++p
		;
	return p - str;
}

int StrCmp(char* str_1, char* str_2)
{	
	
	while (*str_1++ == *str_2+ && '\0' != *str_1)
	{
		/*
			empty body
		*/		
			
	}
	return str_1 - str_2;
}




char *StrCpy(char *dest,  char *src) 
{
	char *start = dest;
	assert(NULL != dest && "First");
	assert(NULL != src && "second");
	
	
	assert(NULL != start && "Third");
    
    	while (*src)
    	{
    		*start++ = *src++;
    	}
        		
    	return dest;
}



char *StrCpyNum(char *dest,  char *src, int num) 
{
	int count;
	assert(NULL != dest && "First");
	assert(NULL != src && "second");
	

               for (count = 0; count < num && src[count] != '\0'; count++)
                   dest[count] = src[count];
               for ( ; count < num; count++)
                   dest[count] = 0;

               return dest;
}

int StrCmpNum(const char *first_word, const char *second_word, size_t num )
{ 
	size_t count = 0;
	assert(NULL != first_word);
	assert(NULL != second_word);
	
	
	
	
	for (;*first_word == *second_word && count < num; first_word++, second_word++) 
	{
		count++;
		if( count == num-1)
		{
		 	return(*first_word - *second_word);
		}
    		
  	} 
  	
  	return(*first_word - *second_word);
}

int StrCaseCmp(char *first_word,  char *second_word)
{

	char *p_f = first_word;
	char *p_s = second_word;
	
	
	assert(NULL != first_word);
	assert(NULL != second_word);
	
	
	
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
	char *p_word = word;
	assert(NULL != word);
	
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

char *StrDup(char *string)
{
	char *p_res = NULL;
	const char *p_str;
	size_t len_of_str = strlen(string);
	
	assert(NULL != string);
	
	p_res = (char *)malloc(len_of_str+1);
	
	strcpy(p_res, string);
	return p_res;
}

char *StrCat(char *str_dest, char *str_src)
{
	char *temp = str_dest+strlen(str_dest);
	assert(NULL != str_dest);
	assert(NULL != str_src);
	
	
	
	while(*str_src++ != '\0')
	{
	*temp++ = *str_src;	
	}	
	return str_dest;
}

char *StrCat_2(char *str_dest, char *str_src)
{
	assert(NULL != str_dest);
	assert(NULL != str_src);
	
	StrCpy(str_dest + strlen(str_dest), str_src);
	
	return str_dest;
}

char *StrCatNum(char *str_dest, char *str_src, int num)
{
	int size = 0;
	int i = 0;

	assert(NULL != str_src);
	assert(NULL != str_dest);

	size = strlen(str_dest);

	while(*str_src != '\0' && i < num)
	{
		*(str_dest + (size + i++)) = *str_src++;
	}

	
	return str_dest;
}


char *StrStr(char *where_find, char *what_find)
{
	size_t i, j;
	size_t n = strlen(what_find);
	
	for (i = 0, j = 0; where_find[i]; i++, j++)
		{       
			
			if (where_find[i] != what_find[j])
			{
			 	j = -1;
			}
        		if (j == n-1)
        		{
        			return (char *)where_find + i - n+1;

        		}
    		}   
    		return NULL; 

}

size_t StrSpn(const char *str, const char *chars) 
{
	size_t i = 0;
    
	while (str[i] && strchr(chars, str[i]))
	{
		i++;
	}	
	return (size_t)i;
}



int Palindrome(char word[])
{
    	int len;
    	int i;
    	len = strlen(word);
    	for (i =0; i < len/2 ;i++)
    	{	
       	if (word[i] != word[len-1-i])
            	return(0);
    	}
    	return(1);

}

void Boom(int first, int second)
{
	
	
	assert(second - first > 0 && "TROBLE!");
	
	while(first++ != second)
	{
		if(BoomHelper(first) && 0 == first % 7)
		{
			printf("%d", first);
			printf("BOOM!\n");
			
		}
		else if(BoomHelper(first))
		{
			printf("%d", first);
			printf("BOOM!\n");
			
			
		}
		else if(0 == first % 7)
		{
			printf("%d", first);
			printf("BOOM!\n");
			
		}
		else
		{
			
			
			printf("%d\n",first);
		}
				
	}
}




int BoomHelper(int x)
{
	while(x)
	{
		if(x%10 == 7)
		{
	 	return 1;
		}
		x/=10;
	}
	return 0;
}



































