#include <iostream>

int Gap(int gap)
{
    return gap <= 1 ? 0 : (gap/2) + (gap%2);
}

void Swap(int * x, int * y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void Merge(int *arr1, int *arr2, int len1, int len2)
{
    int gap = len1 + len2;
    int i = 0;
    int j = 0;

    for(gap = Gap(gap); gap > 0; gap = Gap(gap))
    {
        for(i = 0; (i + gap) < len1; ++i)
        {
            if(arr1[i] > arr1[i + gap])
            {
                Swap(&arr1[i], &arr1[i + gap]);
            }
        }

        for(j = gap > len1 ? gap - len1: 0; i < len1 && j < len2; ++i, ++j)
        {
            if(arr1[i] > arr2[j])
            {
                Swap(&arr1[i], &arr2[j]);
            }
        }

        if(j > len2)
        {
            for(j = 0; (j + gap) < len2; ++j)
            {
                if(arr2[j] > arr2[j + gap])
                {
                    Swap(&arr2[j], &arr2[j + gap]);
                }
            }
        }
    }
}

void PrintArr(int *arr, int size)
{
    for(int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}

int main()
{
    int arr1[] = {1,5,7,9,11};
    
    int arr2[] = {4,8,10};

    Merge(arr1, arr2, 5, 3);

    PrintArr(arr1, 5);
    PrintArr(arr2, 3);
    
    return 0;
}