#include <iostream>
#include "composite.hpp"
using namespace std;

int main()
{

    string names_for_file[3]= {"file", "fole", "fule"};
    string names_for_folders[3]= {"folder", "filder", "falder"};
    size_t size_for_file[3]= {100, 200, 300};

    File* files[3];
    Folder* folders[3];

    for(int i = 0; i < 3; ++i)
    {
        files[i] = new File(names_for_file[i], size_for_file[i]);
    }
    for(int i = 0; i < 3; ++i)
    {
        folders[i] = new Folder(names_for_folders[i], size_for_file[i]);
    }
    for(int i = 0; i < 3; ++i)
    {
        folders[0]->Add(files[i]);
    }
    for(int i = 0; i < 2; ++i)
    {
        folders[1]->Add(files[i]);
    }

    folders[0]->Print();
    folders[1]->Print();
    



    return 0;
}