#ifndef __ILRD_RD132_SHARED_POINTER_HPP__    
#define __ILRD_RD132_SHARED_POINTER_HPP__    

#include <iostream>
using std::cout;
using std::endl;
#include <cstddef> // size_t    

namespace ilrd
{

    template <typename T>
    class SharedPointer
    {
    public:
        inline explicit SharedPointer(T* ptr_ = NULL);
        inline explicit SharedPointer(const SharedPointer<T>& other_);

        inline SharedPointer<T>& operator=(const SharedPointer<T>& other_);

        template <typename U>
        inline explicit SharedPointer(const SharedPointer<U>& other_);

        template <typename U>
        inline SharedPointer<T>& operator=(const SharedPointer<U>& other_);

        inline ~SharedPointer();

        inline T& operator*() const;
        inline T* operator->() const;

        inline std::size_t UseCount() const;
        inline const T* GetPtr() const;

    private:
        template <class U> friend class SharedPointer;
        T* m_rawPtr;
        std::size_t* m_counter;
    };

    template <typename T>
    inline bool operator!=(const SharedPointer<T>& lhs_, const SharedPointer<T>& rhs_);

    template <typename T>
    inline bool operator==(const SharedPointer<T>& lhs_, const SharedPointer<T>& rhs_);
    
    template <typename T>
    SharedPointer<T>::SharedPointer(T *ptr_) : m_rawPtr(ptr_) , m_counter(new size_t(1)){}

    template <typename T>
    SharedPointer<T>::SharedPointer(const SharedPointer<T>& other_): m_rawPtr(other_.m_rawPtr) , m_counter(other_.m_counter)
    {
        ++(*m_counter);
    }

    template <typename T>
    template <typename U>
    SharedPointer<T>::SharedPointer(const SharedPointer<U>& other_): m_rawPtr(other_.m_rawPtr) , m_counter(other_.m_counter)
    {
        ++(*m_counter);
    }

    template <typename T>
    template <typename U>
    SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<U>& other_)
    {
        SharedPointer <T> tmp(*this);
        --(*m_counter);

        m_counter = other_.m_counter;
        m_rawPtr = other_.m_rawPtr;

        ++(*m_counter);

        return *this;

    }
    template <typename T>
    SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<T>& other_)
    {
        SharedPointer <T> tmp(*this);
        --(*m_counter);

        m_counter = other_.m_counter;
        m_rawPtr = other_.m_rawPtr;

        ++(*m_counter);

        return *this;

    }

    template <typename T>
    SharedPointer<T>::~SharedPointer()
    {	
        if((--(*m_counter)) == 0)
        {
            delete m_counter;
            delete m_rawPtr;
        }
        cout << "Dtor PTR" << endl;
    }

    template <typename T>
    const T *SharedPointer<T>::GetPtr() const
    {
        return m_rawPtr;
    }

    template <typename T>
    size_t SharedPointer<T>::UseCount() const
    {
        return *m_counter;
    }

    template <typename T>
    T* SharedPointer<T>::operator->() const
    {
        return m_rawPtr;
    }

    template <typename T>
    T& SharedPointer<T>::operator*() const
    {
        return *m_rawPtr;
    }

    template <typename T>
    bool operator==(const SharedPointer<T>& lhs_, const SharedPointer<T>& rhs_)
    {
        return (lhs_.GetPtr() == rhs_.GetPtr());
    }

    template <typename T>
    bool operator!=(const SharedPointer<T>& lhs_, const SharedPointer<T>& rhs_)
    {
        return !(lhs_ == rhs_);
    }



} // namespace ilrd


#endif // __ILRD_RD132_SHARED_POINTER_HPP__