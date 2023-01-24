#ifndef __ILRD_RD132_RCSTRING_HPP__
#define __ILRD_RD132_RCSTRING_HPP__
#include <iostream>
#include <ostream> // ostream
#include <cstddef> // size_t
#include <cstring> // strlen
#include <exception> // throw
#include <cstdlib>

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


        inline CharProxy operator[](std::size_t index_);

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
            size_t m_count;
            char m_str[1];
        }; 
        RCS * m_struct;
        static RCString s_empty_string;
        static RCS *Init(const char *str_);
        static void Remove(RCS *staff);
    }; 
    
    RCString RCString::s_empty_string(" ");

    class RCString::CharProxy
    {
        public:
            inline CharProxy(RCString &str, std::size_t pos);
            inline CharProxy(const CharProxy &other_);
            inline RCString::CharProxy &operator=(const CharProxy &rhs);
            inline RCString::CharProxy &operator=(char c);
            inline char *operator&();
            inline operator char() const;

        private:
            RCString& m_prox_str;
            std::size_t m_pos;
    };


inline RCString::RCString(const char *s_): m_struct(Init(s_))
{  
}

inline RCString::RCString(const RCString &other_): m_struct(other_.m_struct)
{
    ++(m_struct->m_count);
}

inline RCString& RCString::operator=(const RCString &other_)
{
   
    m_struct = other_.m_struct;
    ++m_struct->m_count;

    if (m_struct->m_count)
    {
        --(m_struct->m_count);
    }
    else
    {
        delete(m_struct);
        m_struct = NULL;
    } 
    return *this;
}

inline RCString::~RCString()
{
     Remove(m_struct);
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
        throw std::logic_error("CHECK THE SIZE!");
    }
    return *((m_struct->m_str)+ index_);
}

inline std::ostream& operator<<(std::ostream& os, const RCString& str)
{
    return (os << str.m_struct->m_str);
}

inline RCString::CharProxy RCString::operator[](std::size_t index_)
{
    return RCString::CharProxy(*this, index_);
}
/*****************************************************************************************/
inline RCString::CharProxy::CharProxy(RCString &str, std::size_t pos): m_prox_str(str), m_pos(pos)
{ 
}

inline RCString::CharProxy::CharProxy(const CharProxy &other_): m_prox_str(other_.m_prox_str)
{  
}

inline RCString::CharProxy::operator char() const
{
    return m_prox_str.m_struct->m_str[m_pos];
}

inline char *RCString::CharProxy::operator&()
{
    return &(m_prox_str.m_struct->m_str[m_pos]);
}

inline RCString::CharProxy &RCString::CharProxy::operator=(const CharProxy &rhs)
{
    return *this = char(rhs);
}
inline RCString::CharProxy &RCString::CharProxy::operator=(char c)
{

    m_prox_str.m_struct->m_str[m_pos] = c;
    return *this;
}

/*****************************************************************************************/
inline RCString::RCS* RCString::Init(const char *str_)
{
    size_t size = std::strlen(str_) + 1;
    RCS *ptr = static_cast<RCS *>(operator new(offsetof(RCS, m_str) + size));
    ptr->m_count = 1;
    memcpy(ptr->m_str, str_, size);
    
    return ptr;
}
inline void RCString::Remove(RCS *staff)
{
    if(--staff->m_count == 0)
    {
       delete(staff);
    }
}

} 

#endif // __ILRD_RD132_RCSTRING_HPP__
