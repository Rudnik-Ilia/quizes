#include "Scheduler.hpp"

namespace ilrd
{
    Scheduler::Scheduler(): m_early_time(TP::max())
    {
        struct sigevent sev{};
        memset(&sev, 0, sizeof(struct sigevent));
        sev.sigev_notify = SIGEV_THREAD;
        sev.sigev_notify_function = &AlarmHandler;
        sev.sigev_notify_attributes = NULL;
        sev.sigev_value.sival_ptr = (void*)this;
        sev.sigev_signo = SIGALRM;

        if(timer_create(CLOCK_MONOTONIC, &sev, &m_timer) == -1)
        {
            throw std::runtime_error("Timer create error");
        }
    }

    Scheduler::~Scheduler()
    {
        timer_delete(m_timer);
    }

    void Scheduler::AddTask(std::shared_ptr<ITask> task_, Ms interval_)
    { 
        TP time_to_execute = std::chrono::system_clock::now() + interval_;

        if(m_tasks.isEmpty() || time_to_execute < m_early_time)
        {
            #ifdef NDEBUG
            std::cout << "Lesser" << std::endl;
            #endif
            
            m_early_time = time_to_execute;
            SetTimer(interval_);

        }
        m_tasks.Push({task_, time_to_execute});

        #ifdef NDEBUG
        std::cout << "Lesser bottom" << std::endl;
        #endif
    }

    void Scheduler::AlarmHandler(union sigval sig)
    {
        #ifdef NDEBUG
        std::cout << "Alarm Handler" << std::endl;
        #endif
        Scheduler *obj= reinterpret_cast<Scheduler *>(sig.sival_ptr);
        obj->Handler();
    }

    void Scheduler::Handler()
    {
        #ifdef NDEBUG
        std::cout << "Handler" << std::endl;
        #endif

        QPair m_pair;
        m_tasks.Pop(m_pair);
        m_pair.first->Execute();

        if(m_tasks.isEmpty())
        {
            #ifdef NDEBUG
            std::cout << "Empty" << std::endl;
            #endif
            return;
        }

        m_tasks.Pop(m_pair);
        Ms new_interval = std::chrono::duration_cast<Ms>(m_pair.second - std::chrono::system_clock::now());
        SetTimer(new_interval);
        m_tasks.Push(m_pair);
    }

    void Scheduler::SetTimer(Ms interval_)
    {
        #ifdef NDEBUG
        std::cout << "Set timer" << std::endl;
        #endif
        struct timespec curr;
        struct itimerspec new_value;

        memset(&curr, 0, sizeof(struct timespec));
        memset(&new_value, 0, sizeof(struct itimerspec));

        curr.tv_sec = interval_.count() / 1000;
        curr.tv_nsec = (interval_.count() % 1000) * 1000000;
        new_value.it_interval.tv_sec = 0;
        new_value.it_interval.tv_nsec = 0;
        new_value.it_value = curr;

        if(timer_settime(m_timer, 0, &new_value, NULL) == -1)
        {
            throw std::runtime_error("Set timer error!");
        }

    }

    bool operator<(const Scheduler::QPair &left, const Scheduler::QPair &right)
    {
        return (left.second > right.second);
    }
}