#include <iostream>

using namespace std;
  
int SubArray(int arr[], int size)
{
    int max = 0;
    int tmp = 0;

    int start = 0;
    int s = 0;
    int end = 0;
  
    for (int i = 0; i < size; i++) 
    {
        tmp += arr[i];

        if (tmp > max)
        {
            max = tmp;
            start = s;
            end = i;
        }
  
        if (tmp <= 0)
        {
            tmp = 0;
            s = i + 1;
        }
    }

    cout << "start: " << start << "end: " << end << endl;
    return max;;
}


int main()
{
    int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3, -8, 3, 5, -1};

    cout << SubArray(arr, 12) << endl;
    return 0;
}