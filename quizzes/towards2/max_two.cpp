#include <iostream>

void FindTwoNum(int *arr, int len)
{
    int first = arr[0];
    int second = arr[1];

    for (size_t i = 2; i < len; ++i)
    {
        if(arr[i] > first)
        {
            second = first;
            first = arr[i];
        }
        else if(arr[i] > second)
        {
            second = arr[i];
        }
    }
    
    std::cout << first << ' ' << second << std::endl;

}

int main()
{
    int arr[] = {1,2,5,-7,9,1,0};

    FindTwoNum(arr, 7);
    return 0;
}