#ifndef __ILRD_RD132_SCOPE_LOCK_H__
#define __ILRD_RD132_SCOPE_LOCK_H__
#include <iostream>
#include <boost/thread/mutex.hpp>
#include <boost/core/noncopyable.hpp>
#include <pthread.h>

namespace ilrd
{
    template <typename Lockable>
    class ScopeLock : private boost::noncopyable
    {
        public:
            explicit ScopeLock(Lockable* lock): m_lockable(lock){};
            ~ScopeLock()
            {
                pthread_mutex_unlock(m_lockable);
                std::cout << "Dtor" << std::endl;

            };

        private:
            Lockable* m_lockable;
       
    };

}

#endif