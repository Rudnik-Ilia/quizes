#ifndef __ILRD_RD132_SCHEDULER_HPP__
#define __ILRD_RD132_SCHEDULER_HPP__

#include <chrono> // milliseconds
#include <memory> // shared_ptr
#include <time.h> // timer_t

#include "Handleton.hpp"
#include "Singleton.hpp"
#include "WaitableQueue.hpp"
#include "PriorityQueue.hpp"
#include "ITask.hpp"

namespace ilrd
{
    class Scheduler
    {
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
            WaitableQueue<std::shared_ptr<ITask>, PriorityQueue<std::shared_ptr<ITask>>> m_tasks;

            static void AlarmHandler(int signo_);   
    };

} // namespace ilrd
    
#endif // __ILRD_RD132_SCHEDULER_HPP__
