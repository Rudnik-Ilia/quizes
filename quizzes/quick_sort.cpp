#include <iostream>
using namespace std;

void Swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int Part(int *arr, int left, int right)
{
    int wall = left;
    int pivot = arr[right];

    for(int i = left; i < right; ++i)
    {
        if(arr[i] <= pivot)
        {
            Swap(&arr[i], &arr[wall]);
            ++wall;
        }
    }

    Swap(&arr[right], &arr[wall]);

    return wall;
}

void Quick(int *arr, int left, int right)
{
    if(left >= right)
    {
        return;
    }

    int pivot = Part(arr, left, right);
    Quick(arr, left, pivot - 1);
    Quick(arr, pivot + 1, right);
}






int main()
{
    int array[] = {3,7,1,9,4,7,1,2,6};
    int arr[] = {33,667,88,999,234,56,123,456,789,876,5443,111};

    int size = sizeof(array)/sizeof(int);

    Quick(arr, 0, 11);
   

    for(int i = 0; i < 11; ++i)
    {
        cout << arr[i] << ' ';
    }
    cout << '\n' ;
    
    return 0;
}


// int Part(int *arr, int left, int right)
// {
//     int wall = left;
//     int pivot = arr[right];

//     for(int i = left; i < right; ++i)
//     {
//         if(arr[i] < pivot)
//         {
//             Swap(&arr[wall], &arr[i]);
//             ++wall;
//         }
//     }
//     Swap(&arr[wall], &arr[right]);

//     return wall;

// }



// void Quick(int *arr, int left, int right)
// {
//     if(left >= right)
//     {
//         return;
//     }

//     int pivot = Part(arr, left, right);
//     Quick(arr, left, pivot - 1);
//     Quick(arr, pivot + 1, right);
// }