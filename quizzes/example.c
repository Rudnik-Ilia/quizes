#include <stdio.h>

void Swap(int* x, int* y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}



void BS(int* arr, size_t len)
{
    size_t i = 0;
    size_t j = 0;

    while (i != len)
    {
        for(j = 0; j < len-1 - i; ++j)
        {
            if(arr[j] > arr[j+1])
            {
                Swap(&arr[j], &arr[j+1]);
            }
        }
        ++i;
    }   
}
void SS(int* arr, size_t len)
{
    size_t i = 0;
    size_t j = 0;
    size_t copy = 0;
    
    for(i = 0; i < len - 1; ++i)
    {
        copy = i;

        for (j = i+1; j < len; ++j)
        {
            if(arr[copy] > arr[j])
            {
                copy = j;
            }
            Swap(&arr[i], &arr[copy]);
        }
        
    }


}
void IS(int* arr, size_t len)
{
    size_t i = 0;
    size_t j = 0;
    
    for(i = 0; i < len; ++i)
    {
        for (j = i + 1; j > 0 && (arr[j] < arr[j-1]); --j)
        {
            Swap(&arr[j], &arr[j-1]);
        }
        
        
    }


}
int main()
{
    size_t i = 0;
    int arr[] = {10,9,8,7,6, -98, 777,5,4,3,2,1};
    size_t size = sizeof(arr)/sizeof(int);

    IS(arr, size);

    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    



return 0;
}