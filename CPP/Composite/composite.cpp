#include <iostream>
#include "composite.hpp"

/*******************************************************************/
std::string File::GetName() 
{
    return m_name; 
}
std::size_t File::GetSize() 
{
    return m_size; 
}

void File::Print() 
{
    std::cout << GetName() << ' ' << GetSize() << std::endl;
}

/*******************************************************************/

std::string Folder::GetName() 
{
    return m_name; 
}

std::size_t Folder::GetSize() 
{
    return m_size; 
}

void Folder::Print() 
{
    std::cout << GetName() << ' ' << GetSize() << std::endl;
    for (std::list<Abstract *>::iterator it = list_of_files.begin(); it != list_of_files.end(); it++) 
    {
        std::cout << ((*it)->GetName()) << std::endl;
    }
}
/*******************************************************************/

void Folder::Add(Abstract* obj)
{   
    if(this == obj)
    {
        return;
    }
    list_of_files.push_back(obj);
}