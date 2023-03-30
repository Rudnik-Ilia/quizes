#ifndef __ILRD_RD132_ASYNC_INJECTION_HPP__
#define __ILRD_RD132_ASYNC_INJECTION_HPP__

#include <iostream>
#include <functional> // std::function
#include <chrono> //std::chrono::milliseconds

#include "Singleton.hpp"
#include "Scheduler.hpp"
#include "ITask.hpp"

namespace ilrd
{
    class AsyncInjection
    {
        using Ms = std::chrono::milliseconds;

        public:
            explicit AsyncInjection(const std::function<bool()>& action_, std::chrono::milliseconds timeout_);
            
            AsyncInjection(const AsyncInjection&) = delete;
            AsyncInjection& operator=(const AsyncInjection&) = delete;
            AsyncInjection(AsyncInjection&&) = delete;
            AsyncInjection& operator=(AsyncInjection&&) = delete;

        private:
            class AsyncTask;

            class AsyncTask : public ITask
            {
                public:
                    AsyncTask(const std::function<bool()> &action_, AsyncInjection* injector_);
                    void Execute();

                private:
                    std::function<bool()> m_action;
                    AsyncInjection* my_injector;
            };

            std::shared_ptr<AsyncTask> m_shared_task;

            friend Singleton<Scheduler>; 
            ~AsyncInjection();

            static Scheduler *m_sched;
            AsyncTask* m_task;
            Ms m_interval;   
    };
    
} // namespace ilrd

#endif // __ILRD_RD132_ASYNC_INJECTION_HPP__
