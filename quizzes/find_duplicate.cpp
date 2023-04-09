#include <iostream>
#include <set>




int main()
{
    int arr[] = {1,1,2,3,4,5,6,6,-6,7,7,8,8,8,9,120,120};
    int size = 17;

    // std::set<int> m_set;

    // for(int i = 0; i < 14; ++i)
    // {
    //     m_set.insert(arr[i]);
    // }
    // std::cout << m_set.size() << std::endl;

    // for(auto iter : m_set)
    // {
    //     std::cout << iter << std::endl;
    // }

    int count = 0;

    for(int i = 0; i < size-1; ++i)
    {
        if(arr[i] == arr[i+1])
        {
            *(char*)&arr[i+1] = 'x';
            ++count;
        }
    }

    std::cout << "COUNT: "<< count << std::endl;

    int new_arr[size - count] = {0};

    int j = 0;
    
    for(int i = 0; i < size;)
    {
        if(*(char*)&arr[i] == 'x')
        {
            ++i;
            continue;
        }
        else
        {
            new_arr[j++] = arr[i++];
        }
    }

    for(int i = 0; i < size - count; ++i)
    {
       std::cout << new_arr[i] << std::endl;
    }








    return 0;
}