#ifndef __ILRD_RD132_SCHEDULER_HPP__
#define __ILRD_RD132_SCHEDULER_HPP__

#include <chrono> // milliseconds
#include <memory> // shared_ptr
#include <time.h> // timer_t
#include <signal.h>
#include <assert.h>
#include <iostream>
#include <cstring>

#include "Handleton.hpp"
#include "Singleton.hpp"
#include "WaitableQueue.hpp"
#include "PriorityQueue.hpp"
#include "ITask.hpp"

namespace ilrd
{
    class Scheduler
    {
        using QPair = std::pair<std::shared_ptr<ITask>, std::chrono::time_point<std::chrono::system_clock>>;

        public:
            void AddTask(std::shared_ptr<ITask> task_, std::chrono::milliseconds interval_);

        private:
            friend bool operator<(Scheduler::QPair &left, Scheduler::QPair &right);

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
            void SetTimer(std::chrono::milliseconds interval_);

            WaitableQueue<QPair, PriorityQueue<QPair>> m_tasks;

            QPair m_close_pair; 


    };

    Scheduler::Scheduler(): m_close_pair()
    {
        struct sigevent sev;
        memset(&sev, 0, sizeof(struct sigevent));
        sev.sigev_notify = SIGEV_THREAD;
        sev.sigev_notify_function = &AlarmHandler;
        sev.sigev_notify_attributes = NULL;
        sev.sigev_value.sival_ptr = (void*)this;

        assert(timer_create(CLOCK_MONOTONIC, &sev, &m_timer) == 0);

    }

    Scheduler::~Scheduler()
    {
        timer_delete(m_timer);
    }

    void Scheduler::AddTask(std::shared_ptr<ITask> task_, std::chrono::milliseconds interval_)
    { 
        std::chrono::time_point<std::chrono::system_clock> time_to_execute = std::chrono::system_clock::now() + interval_;

        QPair new_pair(task_, time_to_execute);

        if(m_tasks.isEmpty() || new_pair > m_close_pair)
        {
            std::cout << "Lesser" << std::endl;
            m_close_pair = new_pair;
            SetTimer(interval_);
        }
        m_tasks.Push(new_pair);
    }

    void Scheduler::AlarmHandler(union sigval sig)
    {
        Scheduler *obj= (Scheduler *)sig.sival_ptr;
        obj->Handler();
    }

    void Scheduler::Handler()
    {
        std::cout << "Handler" << std::endl;
        if(m_tasks.isEmpty())
        {
            std::cout << "Empty" << std::endl;
        }
      
        QPair m_pair;
        m_tasks.Pop(m_pair);
        m_pair.first.get()->Execute();
         
    }

    void Scheduler::SetTimer(std::chrono::milliseconds interval_)
    {
        struct timespec curr;
        struct itimerspec new_value;

        curr.tv_sec = interval_.count() / 1000;
        curr.tv_nsec = (interval_.count() % 1000) * 1000000;
        new_value.it_interval.tv_sec = 0;
        new_value.it_interval.tv_nsec = 0;
        new_value.it_value = curr;

        assert(0 == timer_settime(m_timer, 0, &new_value, NULL));
    }

    bool operator<(Scheduler::QPair &left, Scheduler::QPair &right)
    {
        return (left.second > right.second);
    }

} // namespace ilrd
    
#endif // __ILRD_RD132_SCHEDULER_HPP__
