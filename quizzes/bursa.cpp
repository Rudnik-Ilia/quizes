#include <iostream>

using namespace std;



int Bursa(int *arr, int size, int *b, int *s)
{
    int diff = 0;
    int max = 0;
    int i = size - 2;
    int j = size - 1;

    for(; i >= 0; )
    {
        max = 0;
        
        max = arr[j] - arr[i];

        if(max < 0)
        {
            j = i;
            --i;
        }
        else
        {
            if(max > diff)
            {
                diff = max;
                *b = i;
                *s = j;
                --i;
            }
            else
            {
                --i;
            }
        }
    }
    return diff;
}



int main()
{
    int buy = 9999;
    int sell = 99999;
    int arr[] = {6,2,3,9,5,1,4,9,2};

    cout << Bursa(arr, 9, &buy, &sell) << endl;
    cout << buy << ' ' << sell << endl;


    return 0;
}