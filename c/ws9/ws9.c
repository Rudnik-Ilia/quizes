

#include <stdlib.h> /* size_t*/
#include <assert.h> /*assert*/

#include "ws9.h"


void *MemSet(void *source, int c, size_t n)
{
	size_t i;
    size_t word; 
    size_t loop; 
    size_t tail;
    size_t start;                  
    unsigned char ch = (unsigned char)c; 
    char* sor = (char*)source; 
    
    assert(source);
    
    start = (size_t)source % SIZE_W;
    
    for (i = 0, word = 0; i < SIZE_W  ; ++i) 
    {
        word = word | ((size_t)ch << i * SIZE_W );
    }
    
    if(start != 0)
    {
    	for (i = 0; i < start; ++i)
    	{
        *sor++ = ch;
        --n;
        }
    }

	loop = n / SIZE_W;
	tail = n % SIZE_W;
	
    for (i = 0; i < loop ; ++i, sor += SIZE_W ) 
    {
        *(size_t*)source = word;   
    }
    for (i = 0; i < tail; ++i, ++sor) 
    {
        *sor = ch;
    }
    return source;
}

void *MemCpy(void *dest, const void *src, size_t n)
{
	
	char* ptr1 = (char*)dest;
	const char* ptr2 = (char*)src; 
	
	assert(dest);
	assert(src);
	
	while(n > 0)
	{
	
		if((size_t)ptr2 % SIZE_W == 0 && n > SIZE_W) 
			{
				*(size_t*)ptr1 = *(size_t*)ptr2;
				n = n - SIZE_W;
				ptr1 += SIZE_W;
				ptr2 += SIZE_W;
			}
		else
			{
				*ptr1++ = *ptr2++;
				--n;
			}
	}
	return dest;
}


void *MemMove(void *dest, const void *src, size_t n)
{
	char *p_d = (char*)dest;
	const char *p_s = (char*)src;
	
	
	assert(dest);
	assert(src);
	
	if(p_d == p_s)
	{
		return dest;
	}
	
	else if(p_d < p_s)
	{
		MemCpy(dest, src, n );
    } 	
  	else
    {	
    	
		p_s = p_s + (n-1);
       	p_d = p_d + (n-1);
       	
        while(n--)
        {
        	*p_d-- = *p_s--;
    	}
    }
  	return dest;
}


