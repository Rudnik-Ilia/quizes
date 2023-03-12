#ifndef __ILRD_RD132_SINGLETON_HPP__
#define __ILRD_RD132_SINGLETON_HPP__

#include <atomic>
#include <mutex>

namespace ilrd
{
    template<class T>
    class Singleton
    {
    public:
        Singleton() = delete;
        Singleton(const Singleton &) = delete;
        Singleton(Singleton &&) = delete;
        Singleton &operator=(const Singleton &) = delete;
        Singleton &operator=(Singleton &&) = delete;
        
        ~Singleton() = delete;

        static T *GetInstance();
        
    private:
        static T *s_ptr = NULL;
        static std::mutex s_mutex;
        static void CleanUp();
    };

    template<class T>
    T* Singleton<T>::GetInstance()
    {
        static Singleton<T> singleton_p; 

        T *tmp = singleton_p.s_ptr;
        __sync_synchronize();

        if(0 == tmp)
        {
            std::lock_guard<std::mutex> lock(s_mutex);
            tmp = singleton_p.m_instance;

            if(0 == tmp)
            {
                tmp = new T();
                __sync_synchronize();
                singleton_p.m_instance = tmp;
            }
        }
        return *tmp;
    }

    template<class T>
    void Singleton<T>::CleanUp()
    {
        delete s_ptr;
    }


}
#endif //__ILRD_RD132_SINGLETON_HPP__