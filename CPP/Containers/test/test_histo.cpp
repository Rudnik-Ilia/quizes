#include <iostream>
#include <map>
#include <cstring>
#include <set>
#include <vector>
// #include "histo.hpp"

using namespace std;


int main()
{
    int i = 0;
    int count = 1;
    map <string, int> data;
    vector<string> arr; 
    
    while(i < 6)
    {
        string str;
        cout << "Insert string: ";
        cin >> str;

        if (data.find(str) == data.end())
        {
            data.insert(pair<string, int>(str, count));
            arr.push_back(str);
        }
        else
        {
           ++data[str];
        }

        ++i;
    }
   
    map<string, int>:: iterator iter = data.begin();
    for(std::size_t k = 0; k < data.size(); ++k)
    {
        cout << iter->first << ' ' << iter->second << endl;
        ++iter;
    }
    cout << "------------------" << endl;

     for(std::size_t k = 0; k < arr.size(); ++k)
    {
        cout << arr[k] << endl;
    }


    

   
    return 0;
}