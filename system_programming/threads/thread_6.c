#include <stdio.h>
#include <pthread.h>/*pthread_create*/
#include <unistd.h>
#include <omp.h> /*OpenMp*/

#define NUMBER 1000000000

void *Sum_Of_Divisors(void *idx)
{
    size_t num = *(size_t*)&idx;
    size_t sum = 0;
    size_t i = 1;

    #pragma omp parallel for
    for(i = 1 ; i <= num; ++i)
    {
        if(0 == num % i)
        {
            sum += i;
        } 
    }
    return (*(void **)&sum);
}

int main()
{
    printf("SUMM: %lu\n", (size_t)(Sum_Of_Divisors((void *)NUMBER)));
    return 0;
}