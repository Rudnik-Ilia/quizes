#include <iostream>

int * Majority(int *arr, size_t len)
{
    int stand = 0;
    int * last = NULL;

    for (size_t i = 0; i < len; ++i)
    {
        if(stand == 0)
        {
            last = &arr[i];
            stand++;
        } 
        else if(*last == arr[i])
        {
            stand++;
        }
        else
        {
            stand--;
        }
    }
    std::cout << "Stand: " << stand << std::endl;
    return stand > 0 ? last : NULL;
}

int main()
{
    int arr[] = {1,2,3,1,4,5,1,1, 6};
    size_t size = sizeof(arr)/sizeof(int);

    int * res = Majority(arr, size);

    if(res == NULL)
    {
        std::cout << "NONE" << std::endl;
    }
    else
    {
        std::cout << *res << std::endl;
    }


    return 0;
}