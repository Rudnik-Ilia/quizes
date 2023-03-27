#ifndef __ILRD_RD132_SCHEDULER_HPP__
#define __ILRD_RD132_SCHEDULER_HPP__

#include <chrono> // milliseconds
#include <memory> // shared_ptr
#include <time.h> // timer_t
#include <signal.h>
#include <assert.h>
#include <iostream>

#include "Handleton.hpp"
#include "Singleton.hpp"
#include "WaitableQueue.hpp"
#include "PriorityQueue.hpp"
#include "ITask.hpp"

typedef void(*foo)(union sigval);

namespace ilrd
{
    class Scheduler
    {
        using QPair = std::pair<std::shared_ptr<ITask>, std::chrono::milliseconds>;

        public:
            void AddTask(std::shared_ptr<ITask> task_, std::chrono::milliseconds interval_);

        private:
            Scheduler();

            Scheduler(Scheduler &&) = delete;
            Scheduler(const Scheduler &) = delete;
            Scheduler &operator=(Scheduler &&) = delete;
            Scheduler &operator=(const Scheduler &) = delete;

            ~Scheduler();

            friend Handleton<Scheduler>;
            friend Singleton<Scheduler>;    

            timer_t m_timer;       

            static void AlarmHandler(union sigval sig);
            void Handler();

            WaitableQueue<QPair, PriorityQueue<QPair>> m_tasks;

            std::shared_ptr<ITask> m_curr_task; 

            std::function<void(union sigval)> call_back;


    };

    Scheduler::Scheduler(): m_curr_task(nullptr)
    {
        // , call_back(std::bind(&Scheduler::AlarmHandler, this, std::placeholders::_1))
        // (foo*)(&Scheduler::AlarmHandler);
        //  *call_back.target<void(*)(union sigval)>();
        struct sigevent sev = {0};
        sev.sigev_notify = SIGEV_THREAD;
        sev.sigev_notify_function = &AlarmHandler;
        sev.sigev_notify_attributes = NULL;
        sev.sigev_value.sival_ptr = (void*)this;

        assert(timer_create(CLOCK_MONOTONIC, &sev, &m_timer) == 0);

        struct itimerspec its = {0};

        its.it_interval.tv_sec = 4;
        its.it_interval.tv_nsec = 0;
        its.it_value.tv_sec = 1;
        its.it_value.tv_nsec = 0;
        timer_settime(m_timer, 0, &its, NULL);
    }

    Scheduler::~Scheduler()
    {
        timer_delete(m_timer);
    }

    void Scheduler::AddTask(std::shared_ptr<ITask> task_, std::chrono::milliseconds interval_)
    { 
        // if(!m_curr_task)
        // {
        //     m_curr_task = task_;
        // }
        // else
        // {
        //     QPair m_pair(task_, interval_);
        //     m_tasks.Push(m_pair);
        // }
            QPair m_pair(task_, interval_);
            m_tasks.Push(m_pair);
    }

    void Scheduler::AlarmHandler(union sigval sig)
    {
        Scheduler *obj= (Scheduler *)sig.sival_ptr;
        obj->Handler();
    }

    void Scheduler::Handler()
    {
        std::cout << "Handler" << std::endl;

        while (!m_tasks.isEmpty())
        {
            QPair m_pair;
            m_tasks.Pop(m_pair);
            std::cout << m_pair.second.max << std::endl;
            m_pair.first.get()->Execute();  
        }  
    }


} // namespace ilrd
    
#endif // __ILRD_RD132_SCHEDULER_HPP__
