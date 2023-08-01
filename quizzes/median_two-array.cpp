#include <iostream>
#include <limits>

const int  MAX = (int)1e10;
const int  MIN = (int)-1e10;


double Median(int *arr1, int *arr2, int len1, int len2)
{
    if(len1 > len2)
    {
        return Median(arr2, arr1, len2, len1);
    }
    int total_len = len1 + len2;
    int small_part = 0; 
    int big_part = 0; 

    int left = 0;
    int right = len1;

    while(left <= right)
    {
        small_part = (left + right) / 2;
        big_part = (total_len + 1) / 2 - small_part;

        int min_small = (small_part == 0) ? MIN : arr1[small_part - 1];
        int max_small = (small_part == len1) ? MAX : arr1[small_part];

        int min_big = (big_part == 0) ? MIN : arr2[big_part - 1];
        int max_big = (big_part == len2) ? MAX : arr2[big_part];

        if(min_small > max_big)
        {
            --left;
        }

        if(max_small < min_big)
        {
            ++left;
        }

        if(min_small <= max_big && max_small >= min_big)
        {
            if(!(total_len & 1))
            {
                return (double)(std::max(min_small, min_big) + std::min(max_small, max_big)) / 2;
            }
            else
            {
                return (double)(std::max(min_small, min_big));
            }
        }
    }
}

int main()
{
    int arr1[] = {3};
    int arr2[] = {1};

    int size1 =sizeof(arr1)/sizeof(int);
    int size2 =sizeof(arr2)/sizeof(int);
    
    // Median(arr2, arr1, size2, size1);

    std::cout << Median(arr1, arr2, size1, size2) << std::endl;

    return 0;
}