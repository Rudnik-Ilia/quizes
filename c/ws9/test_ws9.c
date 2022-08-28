
#include <stdio.h>
#include <stdlib.h>

#include"ws9.h"

#define SIZE_ARRAY 12
#define SIZE_W 8

void MMemSet(char *source, int c, size_t n) 
{
	size_t i;
    size_t word; 
    size_t loop; 
    size_t tail;
    size_t start;                  
    unsigned char ch = (unsigned char)c; 
    start = (size_t)source % SIZE_W; 
    
    for (i = 0, word = 0; i < SIZE_W  ; ++i) 
    {
        word = word | ((size_t)ch << i * SIZE_W );
    }
    
    if(start != 0)
    {
    	for (i = 0; i < start; ++i)
    	{
        *source++ = ch;
        --n;
        }
    }

	loop = n / SIZE_W;
	tail = n % SIZE_W;
	
    for (i = 0; i < loop ; ++i, source += SIZE_W ) {
        *(size_t*)source = word;   
    }
    for (i = 0; i < tail; ++i, ++source) {
        *source = ch;
    }
}

void *MemCpy(void *dest, const void *src, size_t n)
{
	size_t i;
	void* p;
	char* ptr1 = dest;
	const char* ptr2 = src; 
	
	for(i = 0; i < n; ++i)
	{
		*ptr1++ = *ptr2++;
	}
	return p;
}



int main()
{
	
	
	char *c;
	int i;
	char a[SIZE_ARRAY] = "i am ilia s";

    c = (char *) malloc(SIZE_ARRAY);
	
    /*
    Wordmemset(c+1, 's', SIZE_ARRAY);
	*/
	
	MemCpy(c, a, SIZE_ARRAY);
	
    for (i = 0; i < SIZE_ARRAY ; ++i)
    {
        printf("%c", c[i]);
    }   
	






return 0;
}
