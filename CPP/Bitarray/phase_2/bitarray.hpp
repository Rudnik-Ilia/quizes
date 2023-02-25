#pragma once

#include <iostream>
using std::cout;
using std::endl;

#include <cstddef> // for size_t
#include <algorithm> // for stl algorithms
#include <bitset> 
#include <string.h>

#define BYTE (8)
#define WORD (64)

#define ALIGNED_SIZE(Size) ((Size / WORD)) + ((Size % WORD) ? 1 : 0)

#define POSTOINDEX(pos) (pos / 64)


namespace ilrd
{
    template <std::size_t Size>
    class BitArray
    {
        class BitProxy;

    public:
        inline explicit BitArray();

        inline BitProxy operator[](std::size_t index_);
        inline bool operator[](std::size_t index_) const;

        inline bool operator==(const BitArray& other_) const;
        inline bool operator!=(const BitArray& other_) const;

        inline BitArray& operator&=(const BitArray& other_);
        inline BitArray& operator^=(const BitArray& other_);
        inline BitArray& operator|=(const BitArray& other_);


        inline void set(bool value_); // setAll 
        inline void set(std::size_t index_, bool value_) throw(std::out_of_range);
        inline void flip(); // flipAll
        inline void flip(std::size_t index_) throw(std::out_of_range);

        inline bool get(std::size_t index_) const; 

        inline std::size_t count() const;

        inline std::string to_string() const; 

 
    private:
        static const size_t s_kNumWords = ALIGNED_SIZE(Size);
        std::size_t m_array[s_kNumWords];

    }; 

    /********************************************************************************************/
    template <std::size_t Size>
    class BitArray<Size>::BitProxy
    {
    public:
        inline BitProxy(BitArray& owner_, std::size_t index_);
        inline BitProxy& operator=(bool value_);
        inline BitProxy& operator=(const BitProxy& other_);
        inline operator bool() const;
        inline bool operator!() const;

    private:
        BitArray& m_owner;
        std::size_t m_index;
    };

    /*******************************************************************************************/

    template <size_t Size>
    BitArray<Size>::BitArray(): m_array()
    {
        cout << "Bitarray Ctor" << endl;
    }

    template <size_t Size>
    bool BitArray<Size>::operator[](size_t index_) const
    {
        return get(index_);
    } 
    template <size_t size>
    typename BitArray<size>::BitProxy BitArray<size>::operator[](size_t index_)
    {
        return BitProxy(*this, index_);
    }

    template <size_t Size>
    bool BitArray<Size>::get(std::size_t index_) const
    { 
        return (m_array[index_/WORD] & 1UL << (index_ % WORD));
    }

    template <size_t Size> 
    void BitArray<Size>::set(std::size_t index_, bool value_) throw(std::out_of_range)
    {
        int arr_index = POSTOINDEX(index_);

        if(value_ == true)
        {
            m_array[arr_index] |= 1UL << (index_ % WORD);
        }
        else
        {
            m_array[arr_index] &= ~(1UL << (index_ % WORD));
        }

    }

    template <size_t Size> 
    void BitArray<Size>::set(bool value_)
    {
        memset((void*)m_array, (value_ ? 0xff : 0x00), sizeof(m_array)); 
    }

    template <size_t Size> 
    void BitArray<Size>::flip()
    {
        // std::transform(m_array, m_array + sizeof(m_array), m_array, std::bit_not());
    }

    template <size_t Size> 
    void BitArray<Size>::flip(size_t index_) throw(std::out_of_range)
    {
        set(!(get(index_)), index_);
    }

    template <size_t size>
    std::string BitArray<size>::to_string() const
    {
        std::string temp;
        for(size_t i = 0; i < size; ++i)
        {
            temp += get(i) + '0';
        }
        return temp;
    }


    






} 
