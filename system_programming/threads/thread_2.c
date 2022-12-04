#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


#define NUMBEROFTHREADS (100000)

int ARRAY[NUMBEROFTHREADS] = {0};

void* Stub(void *idx)
{
    int num = *(int*)idx;
    ARRAY[num] = num;

    return NULL;
}

int main()
{
    time_t start = 0;  
    time_t final = 0;
    size_t i = 0;
    int arr_2[NUMBEROFTHREADS] = {0};
    pthread_t arr_of_threads[NUMBEROFTHREADS];

    time(&start);
    
    for(; i < NUMBEROFTHREADS; ++i)
    {
        arr_2[i] = i;
        if(0 != pthread_create(arr_of_threads + i, NULL, Stub, (void*)&arr_2[i]))
        {
            while(!pthread_create(arr_of_threads + i, NULL, Stub, (void*)&arr_2[i]))
            {
                
            }
        }
    }

    
    time(&final);
    
    sleep(10);
    
    for(i = 0; i < NUMBEROFTHREADS; ++i)
    {
        if((int)i != ARRAY[i])
        {
            break;
        }
        printf("%d\n", ARRAY[i]);
          
      
    }

    printf("Time of execution: %ld\n", final - start);


    return 0;
}