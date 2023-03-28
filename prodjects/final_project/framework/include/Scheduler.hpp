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
        using Ms = std::chrono::milliseconds;
        using TP = std::chrono::time_point<std::chrono::system_clock>;

        public:
            void AddTask(std::shared_ptr<ITask> task_, Ms interval_);

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
            void SetTimer(Ms interval_);

            WaitableQueue<QPair, PriorityQueue<QPair>> m_tasks;
            TP m_early_time;

    };

} // namespace ilrd
    
#endif // __ILRD_RD132_SCHEDULER_HPP__
