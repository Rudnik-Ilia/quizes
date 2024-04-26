#pragma once

#include <iostream>
#include  <limits.h>
#include <cstdio> 

namespace ilrd
{
    class BitArray
    {
    private:
        class BitProxy;

    public:
        inline BitArray();

        inline BitProxy operator[](size_t idx);
        inline bool operator[](size_t idx) const;

    private:
        size_t m_array;
    };

/*********************************************/
    class BitArray::BitProxy
    {
    public:
        inline BitProxy(BitArray &arr_, size_t pos_);
        inline BitProxy &operator=(const BitProxy &other_);
        inline BitProxy &operator=(bool b_);
        inline operator bool() const;

    private:
        BitArray& array;
        size_t m_pos;
    };
/*********************************************/

    BitArray::BitArray(): m_array(0LU){}
   
    bool BitArray::operator[](size_t idx) const
    {
        cout << "Bitarray operator[] return bool" << endl;
        return (m_array & (1UL << idx)) != 0;
    }

    BitArray::BitProxy BitArray::operator[](size_t idx)
    {
        cout << "Bitarray operator[] return Proxy" << endl;
        return BitProxy(*this, idx);
    }

/*********************************************/

    BitArray::BitProxy::BitProxy(BitArray &arr_, size_t pos_) : array(arr_), m_pos(pos_)
    {
        cout << "Bitproxy Ctor" << endl;
    }

    BitArray::BitProxy &BitArray::BitProxy::operator=(const BitProxy &other_)
    {
        cout << "Bitproxy operator=(const BitProxy &other_)" << endl;

        return *this = (bool)other_;
    }

    BitArray::BitProxy &BitArray::BitProxy::operator=(bool b_)
    {
        cout << "Bitproxy operator=(bool)" << endl;

        array.m_array &= ~(1UL << m_pos);
        array.m_array |= (size_t)(b_) << m_pos;

        return *this;
    }

    BitArray::BitProxy::operator bool() const
    {
        cout << "Bitproxy boo()" << endl;
        return (array.m_array & (1UL << m_pos));
    }

}





