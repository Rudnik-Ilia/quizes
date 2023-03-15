#ifndef __ILRD_RD132_SINGLETON_HPP__
#define __ILRD_RD132_SINGLETON_HPP__

#include <atomic>
#include <functional>
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
        static std::atomic<T*> s_ptr;
        static void CleanUp();
    };
    
    #ifdef CREATOR

    template<class T>
    std::atomic<T*> Singleton<T>::s_ptr;

    template<class T>
    T* Singleton<T>::GetInstance()
    {
        static std::mutex s_mutex;

        T *tmp = s_ptr;

        __sync_synchronize();

        if(0 == tmp)
        {
            std::lock_guard<std::mutex> lock(s_mutex);
            tmp = s_ptr;

            if(0 == tmp)
            {
                tmp = new T;

                __sync_synchronize();

                s_ptr = tmp;
                
                atexit(CleanUp);
            }
        }
        return tmp;
    }

    template<class T>
    void Singleton<T>::CleanUp()
    {
        delete s_ptr;
    }
    #endif

}
#endif //__ILRD_RD132_SINGLETON_HPP__