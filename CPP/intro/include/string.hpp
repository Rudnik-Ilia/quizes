#ifndef __ILRD_RD132_STRING_HPP__    
#define __ILRD_RD132_STRING_HPP__

#include <cstddef> // for size_t

namespace ilrd
{
    class String
    {
    public:
        explicit String(const char *str = "");        
        explicit String(const String &);        
        String &operator=(const String &);       
        
        ~String();                              
    
        std::size_t Length() const;             
        const char *Cstr() const;

    private:                        
        char *m_str;                             
    };
}    
#endif /* _ILRD_RD132_STRING_HPP_ */