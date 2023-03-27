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

            static void AlarmHandler(union sigval sigval_);

            WaitableQueue<QPair, PriorityQueue<QPair>> m_tasks;

            std::shared_ptr<ITask> m_curr_task; 


    };

    Scheduler::Scheduler(): m_curr_task(nullptr)
    {
        struct sigevent sev;
        sev.sigev_notify = SIGEV_THREAD;
        sev.sigev_notify_function = &AlarmHandler;
        sev.sigev_notify_attributes = NULL;
        sev.sigev_value.sival_ptr = &m_timer;

        assert(timer_create(CLOCK_MONOTONIC, &sev, &m_timer) == 0);

        struct itimerspec its;

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
        if(!m_curr_task)
        {
            m_curr_task = task_;
        }
        else
        {
            QPair m_pair(task_, interval_);
            m_tasks.Push(m_pair);
        }
    }

    void Scheduler::AlarmHandler(union sigval sigval_)
    {
        std::cout << "AlarmHandler" << std::endl;

    }



} // namespace ilrd
    
#endif // __ILRD_RD132_SCHEDULER_HPP__
