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


        // inline CharProxy& operator[](std::size_t index_);

        inline char operator[](std::size_t index_) const;

        inline bool operator==(const RCString &rhs_);
        inline bool operator!=(const RCString &rhs_);
        inline bool operator>(const RCString &rhs_);
        inline bool operator<(const RCString &rhs_);
        friend std::ostream &operator<<(std::ostream &os_, const RCString &rhs_);

        #ifndef NDEBUG
        void ShowAddr()
        {
             std::cout <<  &m_struct->m_str << std::endl;
        }

        void ShowCount()
        {
            std::cout << m_struct->m_count << ' ' << m_struct->m_str << std::endl;
        }
        #endif 

    private:
        struct RCS
        {
            int m_count;
            char m_str[1];
        }; 
        RCS * m_struct;
        static RCString s_empty_string;

        static RCS *Init(const char *str_);
    }; 
    
    RCString RCString::s_empty_string(" ");

    // class RCString::CharProxy
    // {
    //     public:
    //         inline CharProxy(RCString &str, std::size_t pos);
    //         inline CharProxy(const CharProxy &other_);
    //         inline char &operator=(const CharProxy &rhs);
    //         inline char &operator=(char c);
    //         inline char *operator&(char c);
    //         inline operator char() const;

    //     private:
    //         RCString& str;
    //         std::size_t pos;
    // };


inline RCString::RCString(const char *s_): m_struct(Init(s_))
{ 
   
}

inline RCString::RCString(const RCString &other_): m_struct(other_.m_struct)
{
    ++(m_struct->m_count);
    
}

inline RCString& RCString::operator=(const RCString &other_)
{
   
    if(m_struct == other_.m_struct)
    {
        return *this;
    }
    m_struct = other_.m_struct;
    ++m_struct->m_count;

    if (m_struct->m_count)
    {
        --(m_struct->m_count);
    }
    else
    {
        delete m_struct;
        m_struct = NULL;
    } 
    return *this;
}

inline RCString::~RCString()
{
    if(--m_struct == 0)
    {
        delete m_struct;
        m_struct = NULL;
    }
}

inline bool RCString::operator==(const RCString &rhs_)
{
    return strcmp(m_struct->m_str, rhs_.m_struct->m_str) == 0;
}

inline bool RCString::operator!=(const RCString &rhs_)
{
    return !(*this == rhs_);
}

inline bool RCString::operator>(const RCString &rhs_)
{
    return strcmp(m_struct->m_str, rhs_.m_struct->m_str) > 0;
}

inline bool RCString::operator<(const RCString &rhs_)
{
    return strcmp(m_struct->m_str, rhs_.m_struct->m_str) < 0;
}

inline char RCString::operator[](std::size_t index_) const
{
    if(index_ > strlen(m_struct->m_str))
    {
        throw 1;
    }
    return *((m_struct->m_str)+ index_);
}

inline std::ostream& operator<<(std::ostream& os, const RCString& str)
{
    return (os << str.m_struct->m_str);
}

/*****************************************************************************************/
inline RCString::RCS* RCString::Init(const char *str_)
{
    std::size_t size = std::strlen(str_) + 1;
    RCS *ptr = (RCS*)operator new(offsetof(RCS, m_str) + size);
    ptr->m_count = 1;
    memcpy(ptr->m_str, str_, size);
    
    return ptr;
}

} 

#endif // __ILRD_RD132_RCSTRING_HPP__
