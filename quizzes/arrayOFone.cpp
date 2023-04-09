#include <iostream>

using namespace std;

int FindSum(int *arr, int start, int flip, int size)
{
    int summ = 0;
    int max = 0;
    int change = flip;

    for(int i = start; i < size; ++i)
    {
        cout <<  i << ' ';
        if(arr[i])
        {
            summ += 1;
        }
        else
        {
            if(--change >= 0)
            {
                summ += 1;
            }
            else
            {
                if(summ > max)
                {
                    max = summ;
                }
                i -= summ;
                summ = 0;
                change = flip;
            } 
        }
        if(summ > max)
        {
            max = summ;
        }

    }
    return max;

}


int main()
{
    int arr[] = {0,0,1,1,1,1,1,0,1,0,1,1,1,0,0,1,1,1,1,0,0,0,1,0,1,1,1,1,1};
    int arr1[] = {0, 1, 1, 1, 0, 0, 1, 0, 1, 1};

    // FindSum(arr, 0, 1, 17); 
    cout << FindSum(arr1, 0, 2, 10) << endl;



    return 0;
}