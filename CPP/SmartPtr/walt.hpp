/*****************************************************************************
 * @namespace  ILRD_RD132
 * @file       shared_pointers.hpp
 * @author     Walter Caspari
 * @remarks    Ilia
 * @version    Pending Review
 * @brief      Shared Pointers
 *****************************************************************************/



#ifndef __ILRD_RD132_SHARED_POINTER_HPP__
#define __ILRD_RD132_SHARED_POINTER_HPP__

#include <cstddef> // size_t
#include <iostream>

namespace ilrd
{

    template <class T>
    class SharedPointer
    {
    public:
        inline explicit SharedPointer(T *ptr_ = NULL);
        inline explicit SharedPointer(const SharedPointer &other_);

       /*  template <typename U>
        inline explicit SharedPointer(const SharedPointer<U> &other_); */
        
        inline SharedPointer &operator=(const SharedPointer &other_);
        
        template <typename U>
        inline SharedPointer &operator=(const SharedPointer<U> &other_);
        
        inline ~SharedPointer();

        inline T &operator*() const;
        inline T *operator->() const;

        inline std::size_t UseCount() const;
        inline const T *GetPtr() const;


    private:
        T *m_rawPtr;
        std::size_t *m_counter;
        
        template <typename U>
        friend class SharedPointer;
    };

    template <class T>
    SharedPointer<T>::SharedPointer(T *ptr_) : m_rawPtr(ptr_), m_counter(new size_t (1))
    {
        // m_rawPtr = new T;
        // m_rawPtr = ptr_;
        // m_counter = new size_t;
        // *m_counter = 1;
    }

    template <class T>
    SharedPointer<T>::SharedPointer(const SharedPointer &other_) : m_rawPtr(other_.m_rawPtr)
    {
        m_rawPtr = new T;
        m_rawPtr = other_.m_rawPtr;
        m_counter = new size_t;
        m_counter = other_.m_counter;
        ++*m_counter;
    }

    /* template <class T>
    template <class U>
    SharedPointer<T>::SharedPointer(const SharedPointer<U> &other_) : m_rawPtr(other_.m_rawPtr)
    {
        m_rawPtr = new T;
        m_rawPtr = other_.m_rawPtr;
        m_counter = new size_t;
        m_counter = other_.m_counter;
        ++*m_counter;
    } */

    template <class T>
    SharedPointer<T> &SharedPointer<T>::operator=(const SharedPointer &other_)
    {
        --*m_counter;
        if(*m_counter == 0)
        {
            delete m_rawPtr;
        }
        m_rawPtr = other_.m_rawPtr;
        m_counter = other_.m_counter;
        ++(*m_counter);
        return *this;
    }

    template <class T>
    template <class U>
    SharedPointer<T> &SharedPointer<T>::operator=(const SharedPointer<U> &other_)
    {
        --*m_counter;
        if(*m_counter == 0)
        {
            delete m_rawPtr;
        }
        m_rawPtr = other_.m_rawPtr;
        m_counter = other_.m_counter;
        ++(*m_counter);
        return *this;
    }

    template <class T>
    SharedPointer<T>::~SharedPointer()
    {
        if(--*m_counter == 0)
        {
            delete m_rawPtr;
            delete m_counter;
            std::cout << "destructor!!" << std::endl;
        }
    }

    template <class T>
    T &SharedPointer<T>::operator*() const
    {
        return *m_rawPtr;
    }

    template <class T>
    T *SharedPointer<T>::operator->() const
    {
        return m_rawPtr;
    }

    template <class T>
    std::size_t SharedPointer<T>::UseCount() const
    {
        return *m_counter;
    }

    template <class T>
    const T *SharedPointer<T>::GetPtr() const
    {
        return m_rawPtr;
    }

    template <class T>
    bool operator==(const SharedPointer<T> &lhs_, const SharedPointer<T> &rhs_)
    {
        return (lhs_.GetPtr() == rhs_.GetPtr() && lhs_.UseCount() == rhs_.UseCount());
    }

    template <class T>
    bool operator!=(const SharedPointer<T> &lhs_, const SharedPointer<T> &rhs_)
    {
        return !(lhs_ == rhs_);
    }

    template <class T>
    bool operator>(const SharedPointer<T> &lhs_, const SharedPointer<T> &rhs_)
    {
        return lhs_.GetPtr() > rhs_.GetPtr();
    }

    template <class T>
    inline bool operator<(const SharedPointer<T> &lhs_, const SharedPointer<T> &rhs_)
    {
        return lhs_.GetPtr() < rhs_.GetPtr();
    }

    template <class T>
    inline bool operator>=(const SharedPointer<T> &lhs_, const SharedPointer<T> &rhs_)
    {
        return lhs_.GetPtr() >= rhs_.GetPtr();
    }

    template <class T>
    inline bool operator<=(const SharedPointer<T> &lhs_, const SharedPointer<T> &rhs_)
    {
        return lhs_.GetPtr() <= rhs_.GetPtr();
    }

} // namespace ilrd

#endif // __ILRD_RD132_SHARED_POINTER_HPP__
