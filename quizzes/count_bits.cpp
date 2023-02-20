#include <iostream>

using namespace std;


int Count(size_t x)
{
    int res = 0;

    while (x)
    {
        res += x&1;
        x>>=1;
    }
    return res;
}

int Count2(size_t x)
{
    int res = 0;

    while (x)
    {
        x &= x-1;
        res++;
        
    }
    return res;
}

int Count3(size_t x, int *arr)
{
    unsigned char* tmp = (unsigned char*)&x;
    int res = arr[*tmp] + arr[*(tmp+1)] + arr[*(tmp+2)] + arr[*(tmp+3)];
    return res;
}




int main()
{
    int *arr = new int[255];
    for (size_t i = 0; i < 255; i++)
    {
        arr[i] = Count2(i);
    }
    
    // cout << arr[234] << endl;
    cout << Count2(769124) << endl;
    cout << Count3(769124, arr) << endl;



    return 0;

}