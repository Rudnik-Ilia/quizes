#include <iostream>
#include <cstdlib>

using namespace std;
void Helper(int *array, int *left, int *right, int len1, int len2);

void Merge(int *array, int lenght)
{
    if(lenght < 2)
    {
        return;
    }

    int len_1 = lenght/2;
    int len_2 = lenght - len_1;

    int left[len_1] = {0};
    int right[len_2] = {0};

    for(int i = 0; i < len_1; ++i)
    {
        left[i] = array[i];
    }
    for(int i = len_1; i < lenght; ++i)
    {
        right[i - len_1] = array[i];
    }
    Merge(left, len_1);
    Merge(right, len_2);
    Helper(array, left, right, len_1, len_2);

}

void Helper(int *array, int *left, int *right, int len1, int len2)
{
    int target = 0;
    int arr1 = 0;
    int arr2 = 0;

    while(arr1 < len1 && arr2 < len2)
    {
        if(left[arr1] <= right[arr2])
        {
            array[target] = left[arr1++];
        }
        else
        {
            array[target] = right[arr2++];
        }
        ++target;
    }

    while(arr1 < len1)
    {
        array[target++] = left[arr1++];
    }
    while(arr2 < len2)
    {
        array[target++] = right[arr2++];
    }
}

void Swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
};


void BitSort(int *array, int len)
{
    for(int i = 0, j = len - 1; i < j;)
    {
        if(array[i] == 1 && array[j] == 0)
        {
            Swap(&array[i], &array[j]);
        }
        if(array[i] == 0)
        {
            ++i;
        }
        if(array[j] == 1)
        {
            --j;
        }
    }
}


int main()
{

    int arr[] = {5,8,1,9,4,7,2,8,1,0,2,5,8,88,8};
    int bit[] = {1,0,1,1,0,0,0,1,0,0,1,1,1,0,1};

    int size = sizeof(bit)/sizeof(int);
    int buff[size] = {};

    Merge(arr, size);
    // Selection(arr, size);
    // Bubble(arr, size);
    // Insertion(arr, size);
    BitSort(bit, 15);

   

    for(int i = 0; i < size; i++)
    {
        cout << bit[i] << " ";
    }

    return 0;
}
// void Merge(int *arr, int lenght)
// {
//     if(lenght < 2)
//     {
//         return;
//     }

//     int len1 = lenght/2;
//     int len2 = lenght - len1;

//     int arr_1[len1] = {0};
//     int arr_2[len2] = {0};

//     for(int i = 0; i < len1; ++i)
//     {
//         arr_1[i] = arr[i];
//     }
//     for(int i = len1; i < lenght ; ++i)
//     {
//         arr_2[i - len1] = arr[i];
//     }
//     Merge(arr_1, len1);
//     Merge(arr_2, len2);

//     Helper(arr, arr_1, arr_2, len1, len2);
 
// }

// void Helper(int *arr_res, int *arr_1, int *arr_2, int len1, int len2)
// {
//     int idx_1_min = 0;
//     int idx_2_min = 0;
//     int idx_res = 0;

//     while(idx_1_min < len1 && idx_2_min < len2)
//     {
//         if(arr_1[idx_1_min] <= arr_2[idx_2_min])
//         {
//             arr_res[idx_res] = arr_1[idx_1_min];
//             idx_1_min++;
//         }
//         else
//         {
//             arr_res[idx_res] = arr_2[idx_2_min];
//             idx_2_min++;
//         }
//         idx_res++;
//     }
   
//     while (idx_1_min < len1)
//     {
//         arr_res[idx_res++] = arr_1[idx_1_min++];
//     }
        
//     while (idx_2_min < len2)
//     {
//         arr_res[idx_res++] = arr_2[idx_2_min++];
//     }

// }