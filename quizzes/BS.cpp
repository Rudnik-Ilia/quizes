#include <iostream>

using namespace std;


int binSearchRecusive(int *arr, int l, int r, int num)
{
    if (l <= r)
    {
        int mid = l + (r - 1) / 2;

        if (arr[mid] == num)
        {
            return mid;
        }
        if( arr[mid] > num)
        {
            return binSearchRecusive(arr, l, mid - 1, num);

        }
        return binSearchRecusive(arr, mid + 1, r, num);

    }
    return -1;
}

int BS(int *arr, int size, int num)
{
    int l = 0;
    int r = size;

    while (l + 1 < r)
    {
        int mid = (l + r)/ 2;

        if(arr[mid] > num)
        {
            r = mid;
        }
        else
        {
            l = mid;
        }
    }
    return arr[l] == num ? l : -1;  
}

int SuperBS(int *arr, int size, int num)
{
    int left = 0;
    int right = size;

    while (left + 1 < right)
    {
        int mid = (left + right)/ 2;
        int ftrue = (arr[mid] > num);
        int ffalse = ftrue ^ 1;
        right = right * ffalse + mid * ftrue;
        left = mid * ffalse + left * ftrue;
    }
    return arr[left];  
}

int SSuperBS(int *arr, int size, int num)
{
    int left = 0;
    int right = size - 1;

    while (left < right)
    {
        int mid = (left + right)/ 2;
        int ftrue = (arr[mid] >= num);
        int ffalse = ftrue ^ 1;
        right = right * ffalse + mid * ftrue;
        left = (mid + 1)* ffalse + left * ftrue;
    }
    return arr[left];  
}

int main()
{
    int arr[] = {1,2,3, 3,4,5,6,7,8};

    // cout << binSearchRecusive(arr, 0, 8, 7) << endl;
    // cout << BS(arr, 9, 7) << endl;
    cout << SuperBS(arr, 9, 38888) << endl;

    return 0;
}