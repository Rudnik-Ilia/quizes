#include <iostream>
#include <map>
#include <cstring>
#include <set>
#include <vector>
// #include "histo.hpp"

using namespace std;


int main()
{
    string str;
    map <string, int> data;
    vector<string> arr; 
    
    while(getline(cin, str) && str != ".")
    {
        if (data[str] == 0)
        {
            arr.push_back(str);
        }
        ++data[str];
    }

    for(std::size_t k = 0; k < arr.size(); ++k)
    {
        int x = data[arr[k]];
        if(x == 1)
        {
            cout << ((x == 1)? " " : " x " ) << arr[k] << endl;
        }
        else
        {
            cout << x << ((x == 1)? " " : " x " ) << arr[k] << endl;
        }

    }

    return 0;
}