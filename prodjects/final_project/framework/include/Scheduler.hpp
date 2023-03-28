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
            friend bool operator<(const Scheduler::QPair &left, const Scheduler::QPair &right);

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
            std::chrono::time_point<std::chrono::system_clock> m_early_time;

    };

    Scheduler::Scheduler(): m_early_time(std::chrono::time_point<std::chrono::system_clock>::max())
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
        // timer_delete(m_timer);
    }

    void Scheduler::AddTask(std::shared_ptr<ITask> task_, std::chrono::milliseconds interval_)
    { 
        std::chrono::time_point<std::chrono::system_clock> time_to_execute = std::chrono::system_clock::now() + interval_;

        if(m_tasks.isEmpty() || time_to_execute < m_early_time)
        {
            std::cout << "Lesser" << std::endl;
            m_early_time = time_to_execute;
            SetTimer(interval_);
        }
        m_tasks.Push({task_, time_to_execute});
    }

    void Scheduler::AlarmHandler(union sigval sig)
    {
        Scheduler *obj= (Scheduler *)sig.sival_ptr;
        obj->Handler();
    }

    void Scheduler::Handler()
    {
        std::cout << "Handler" << std::endl;

        QPair m_pair;
        m_tasks.Pop(m_pair);
        m_pair.first->Execute();

        if(m_tasks.isEmpty())
        {
            std::cout << "Empty" << std::endl;
            timer_delete(m_timer);
            return;
        }

        m_tasks.Pop(m_pair);
        std::chrono::milliseconds new_interval = std::chrono::duration_cast<std::chrono::milliseconds>(m_pair.second - std::chrono::system_clock::now());
        SetTimer(new_interval);
        m_tasks.Push(m_pair);
    }

    void Scheduler::SetTimer(std::chrono::milliseconds interval_)
    {
        struct timespec curr;
        struct itimerspec new_value;

        memset(&curr, 0, sizeof(struct timespec));
        memset(&new_value, 0, sizeof(struct itimerspec));

        curr.tv_sec = interval_.count() / 1000;
        curr.tv_nsec = (interval_.count() % 1000) * 1000000;
        new_value.it_interval.tv_sec = 0;
        new_value.it_interval.tv_nsec = 0;
        new_value.it_value = curr;

        assert(0 == timer_settime(m_timer, 0, &new_value, NULL));
    }

    bool operator<(const Scheduler::QPair &left, const Scheduler::QPair &right)
    {
        return (left.second > right.second);
    }

} // namespace ilrd
    
#endif // __ILRD_RD132_SCHEDULER_HPP__
