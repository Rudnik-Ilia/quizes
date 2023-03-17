#ifndef __ILRD_RD132_HANDLETON_HPP__
#define __ILRD_RD132_HANDLETON_HPP__

#include <atomic>
#include <functional>
#include <mutex>

namespace ilrd
{

    template<class T>
    class Handleton
    {
    public:
        Handleton() = delete;
        Handleton(const Handleton &) = delete;
        Handleton(Handleton &&) = delete;
        Handleton &operator=(const Handleton &) = delete;
        Handleton &operator=(Handleton &&) = delete;
        
        ~Handleton() = delete;

        static T *GetInstance();
        
    private:
        static std::atomic<T*> s_ptr;
        static void CleanUp();
    };

    #ifdef CREATOR

    template<class T>
    std::atomic<T*> Handleton<T>::s_ptr;

    template<class T>
    T* Handleton<T>::GetInstance()
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
    void Handleton<T>::CleanUp()
    {
        delete s_ptr;
    };
 
    #endif
}

#endif //__ILRD_RD132_HANDLETON_HPP__
