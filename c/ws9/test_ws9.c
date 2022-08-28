
#include <stdio.h>
#include <stdlib.h>

#include"ws9.h"

#define SIZE_ARRAY 80
#define SIZE_W 8

void Wordmemset(char *dest, int ch, size_t len) 
{
	size_t i;
    size_t word; 
    size_t loop; 
    size_t tail;
    size_t start;                  
    unsigned char c = (unsigned char)ch; 
    start = (size_t)dest % SIZE_W; 
    
    for (i = 0, word = 0; i < SIZE_W  ; ++i) 
    {
        word = word | ((size_t)c << i * SIZE_W );
    }
    
    if(start != 0)
    {
    	for (i = 0; i < start; ++i)
    	{
        *dest++ = c;
        --len;
        }
    }

	loop = len / SIZE_W;
	tail = len % SIZE_W;
	
    for (i = 0; i < loop ; ++i, dest += SIZE_W ) {
        *(size_t*)dest = word;   
    }
    for (i = 0; i < tail; ++i, ++dest) {
        *dest = c;
    }
}


int main()
{
	
	
	char *c;
	int i;

    c = (char *) malloc(SIZE_ARRAY);
	
    
    Wordmemset(c+1, 's', SIZE_ARRAY);

    for (i = 0; i < SIZE_ARRAY ; ++i)
    {
        printf("%c", c[i]);
    }   
	






return 0;
}
