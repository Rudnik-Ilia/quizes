// #include <iostream>
// #include <vector>

// using namespace std;

// int findSmallestMissingInteger(vector<int>& arr) {
//     int n = arr.size();
//     vector<bool> present(n, false);
//     // mark present elements in the boolean array
//     for (int i = 0; i < n; i++) {
//         if (0 < arr[i] && arr[i] <= n) {
//             present[arr[i] - 1] = true;
//         }
//     }
//     // return the first index with false value
//     for (int i = 0; i < n; i++) {
//         if (!present[i]) {
//             return i + 1;
//         }
//     }
//     // if all elements are present, return the next integer
//     return n + 1;
// }

// int main() {
//     vector<int> arr = {100, 2, -1, 1};
//     cout << findSmallestMissingInteger(arr) << endl; // output: 2
//     return 0;
// }

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int findSmallestMissingInteger(vector<int>& arr) 
{
    int n = arr.size();

    int j = 0;

    for (int i = 0; i < n; i++) 
    {
        if (arr[i] > 0) 
        {
            swap(arr[i], arr[j]);
            j++;
        }
    }

    for (int i = 0; i < j; i++)
    {
        if (arr[i] <= j && arr[arr[i] - 1] > 0) 
        {
            arr[arr[i] - 1] *= -1 ;
        }
    }

    for (int i = 0; i < j; i++) 
    {
        if (arr[i] > 0)
        {
            return i + 1;
        }
    }

    return j + 1;
}

int main() {
    vector<int> arr = {3, 4, -1, 1};
    cout << findSmallestMissingInteger(arr) << endl; // output: 2
    return 0;
}