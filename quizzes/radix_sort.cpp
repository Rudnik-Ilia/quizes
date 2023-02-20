
#include <iostream>

using namespace std;

void RadixSort(int array[], int len){
	int i;
	int max = 0;

	for(i = 0; i < len; i++){
		if(array[i] > max){
			max = array[i];
		}
	}
	int exp = 1;
	while(exp <= max){

		int bucket[10] = {0};

		int tmp[len] = {0};

		for(i = 0; i < len; i++)
        {
			bucket[array[i] / exp % 10]++;
        }

		for(i = 1; i < 10; i++)
        {
			bucket[i] += bucket[i-1];
        }

		for(i = len - 1; i >= 0; i--)
        {
			tmp[--bucket[array[i]/exp%10]] = array[i];
        }

		for(i = 0; i < len; i++)
        {
			array[i] = tmp[i];
		}

		exp *= 10;
	}
}



int main()
{
    int arr[] = {33,667,88,999,234,56,123,456,789,876,5443,111};

    RadixSort(arr, 12);

    for(int i = 0; i < 12; ++i)
    {
        cout << arr[i] << ' ';
    }



    return 0;
}