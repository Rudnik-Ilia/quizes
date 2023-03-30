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
                    AsyncTask(const std::function<bool()> &action_, AsyncInjection* injector_): m_action(action_), my_injector(injector_){}

                    void Execute()
                    {
                        if(m_action())
                        {
                            std::cout << "TRUE" << std::endl;
                            my_injector->m_sched->AddTask(my_injector->m_shared_task, my_injector->m_interval);
                        }
                        else
                        {
                            std::cout << "FALSE" << std::endl;
                        }
                    }

                private:
                    std::function<bool()> m_action;
                    AsyncInjection* my_injector;
            };

            std::shared_ptr<AsyncTask> m_shared_task;

            friend Singleton<Scheduler>; 
            ~AsyncInjection() = delete;

            static Scheduler *m_sched;
            AsyncTask* m_task;
            Ms m_interval;
            
    };

    Scheduler* AsyncInjection::m_sched = Singleton<Scheduler>::GetInstance();

    AsyncInjection::AsyncInjection(const std::function<bool()> &action_, std::chrono::milliseconds timeout_): m_shared_task(std::shared_ptr<AsyncTask>(new AsyncTask(action_, this))), m_interval(timeout_)
    {
        m_sched->AddTask(std::shared_ptr<AsyncTask>(m_shared_task), m_interval);
    }
    
} // namespace ilrd

#endif // __ILRD_RD132_ASYNC_INJECTION_HPP__
