#include <stdio.h>
#include <pthread.h>/*pthread*/
#include <unistd.h>
#include <stdlib.h>

#define NUMBEROFTHREADS (17)
#define NUMBER (1000000000)
#define RANGE NUMBER / NUMBEROFTHREADS

void *SumDivisors(void *idx)
{
    size_t i = *(size_t*)&idx;
    size_t sum = 0;
    size_t end = i + RANGE;
    /*
    size_t* ptr = malloc(sizeof(size_t));
    *ptr = sum;
    return (void *)ptr;
    */

    if (end > NUMBER)
    {
        end = NUMBER;
    }
    
    for( ; i <= end; ++i)
    {
        if(0 == NUMBER % i)
        {
            sum += i;
        } 
    }
    return *(void **)&sum;
}

int main()
{
    pthread_t arr_of_threads[NUMBEROFTHREADS] = {0};
    size_t i = 0;
    size_t sum = 0;
    /* size_t *data = NULL; */
    void *data = NULL;


    for (i = 0; i < NUMBEROFTHREADS; ++i)
    {
        pthread_create(arr_of_threads + i, NULL, SumDivisors, (void *)((i * RANGE) + 1));
    }

    for (i = 0; i < NUMBEROFTHREADS; ++i)
    {
        pthread_join(arr_of_threads[i], &data);
        sum += (size_t)data;
    } 

    printf("SUMM: %ld\n", sum);
    
    return 0;
}