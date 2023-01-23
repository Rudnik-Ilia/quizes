#ifndef __ILRD_RD132_RCSTRING_HPP__
#define __ILRD_RD132_RCSTRING_HPP__
#include <iostream>
#include <ostream> // ostream
#include <cstddef> // size_t
#include <cstring> // strlen

namespace ilrd
{

class RCString
{
private:
    class CharProxy;
public:
    inline RCString(const char *s_);
    inline RCString(const RCString &other_ = s_empty_string);
    inline RCString &operator=(const RCString &other_);
    inline ~RCString();


    inline CharProxy &operator[](std::size_t index_);
    inline char operator[](std::size_t index_) const;

    inline bool operator==(const RCString &rhs_);
    inline bool operator!=(const RCString &rhs_);
    inline bool operator>(const RCString &rhs_);
    inline bool operator<(const RCString &rhs_);
    friend std::ostream &operator<<(std::ostream &os_, const RCString &rhs_);

private:
    // char *m_buff;
    struct RCS
    {
        int m_count;
        char m_str[1];
    }; 

    RCS * m_struct;
    static RCString s_empty_string;

    static RCS *Init(const char *str_);

    static void Show(RCS *ptr)
    {
        std::cout << ptr->m_count << ' ' << ptr->m_str << std::endl;
    }
}; 

class CharProxy
{
    public:
        inline CharProxy(RCString &str, std::size_t pos);
        inline CharProxy(const CharProxy &other_);
        inline char &operator=(const CharProxy &rhs);
        inline char &operator=(char c);
        inline char *operator&(char c);
        inline operator char() const;

    private:
    RCString& str;

    std::size_t pos;
};

inline RCString::RCString(const char *s_): m_struct(Init(s_))
{ 
    Show(m_struct);
}

inline RCString::RCString(const RCString &other_): m_struct(other_.m_struct)
{
    ++(m_struct->m_count);
    Show(m_struct);
}

inline RCString& RCString::operator=(const RCString &other_)
{
    if(m_struct == other_.m_struct)
    {
        return *this;
    }
    m_struct = other_.m_struct;
    ++m_struct->m_count;

    



    return *this;
}

inline RCString::~RCString()
{
    
}








} 

#endif // __ILRD_RD132_RCSTRING_HPP__
