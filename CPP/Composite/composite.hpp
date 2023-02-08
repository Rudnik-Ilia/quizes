#pragma once

#include <cstddef> 
#include <iostream>
#include <list>



class Abstract
{
public:

    virtual ~Abstract(){};

    virtual void Add( Abstract* obj){};
    // virtual void Remove( Abstract* obj){};           
    virtual void Print(){};

    virtual std::string GetName() = 0;
    virtual std::size_t GetSize() = 0;
  
};

class File: public Abstract
{
public:
    explicit File(std::string name, std::size_t size): m_name(name) , m_size(size){};
    ~File(){};

    void Print();

    std::string GetName();
    std::size_t GetSize();

private:
    std::string m_name;
    std::size_t m_size;
};

class Folder: public Abstract
{
public:
    explicit Folder(std::string name, std::size_t size): m_name(name), m_size(size){};

    ~Folder(){};

    void Add(Abstract* obj);
    // void Remove(Abstract* obj); 
    void Print();

    std::string GetName();
    std::size_t GetSize();

private:
    std::string m_name;
    std::size_t m_size;
    std::list<Abstract *> list_of_files;
};




