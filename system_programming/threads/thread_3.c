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
    int res = 0;
    int arr_2[NUMBEROFTHREADS] = {0};
    pthread_t arr_of_threads[NUMBEROFTHREADS];
    pthread_attr_t deatach;
    pthread_attr_init(&deatach);
    pthread_attr_setdetachstate(&deatach, PTHREAD_CREATE_DETACHED);


    time(&start);
    
    for(; i < NUMBEROFTHREADS; ++i)
    {
        arr_2[i] = i;
        res = pthread_create(arr_of_threads + i, &deatach, Stub, (void*)&arr_2[i]);
        if(0 != res)
        {
            while(0 != res)
            {
                res = pthread_create(arr_of_threads + i, NULL, Stub, (void*)&arr_2[i]);
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

    pthread_attr_destroy(&deatach);

    return 0;
}