#ifndef __ILRD_RD132_THREADPOOL_HPP__
#define __ILRD_RD132_THREADPOOL_HPP__

#include <thread> // thread
#include <atomic>
#include <condition_variable>
#include <mutex>

#include "WaitableQueue.hpp"
#include "PriorityQueue.hpp"
#include "ITask.hpp"
#include "ThreadMap.hpp"

namespace ilrd
{   

    class ThreadPool
    {
        public:
            enum TaskPriority {PRIORITY_LOW = 0, PRIORITY_NORMAL = 1, PRIORITY_HIGH = 2};

            typedef std::pair<std::shared_ptr<ITask>, TaskPriority> TaskPair;
            typedef PriorityQueue<TaskPair, std::vector<TaskPair>, std::less<TaskPair> > TaskPQ;

            explicit ThreadPool(std::size_t numOfThreads = std::thread::hardware_concurrency()); 
            
            ThreadPool(ThreadPool &&) = delete;
            ThreadPool(const ThreadPool &) = delete;
            ThreadPool &operator=(ThreadPool &&) = delete;
            ThreadPool &operator=(const ThreadPool &) = delete;
 
            ~ThreadPool();

            void AddTask(std::shared_ptr<ITask> task, TaskPriority taskPriority_ = PRIORITY_NORMAL);
            void Pause(void);
            void Resume(void);
            void SetThreadNum(std::size_t n_);

        private:

            void MyJoin();
            void Stop(size_t times);
            void CreateAndPushThread(size_t times);

            std::size_t m_numOfThreads;

            std::mutex m_mutex;
            std::condition_variable m_conditon_var;

            ThreadMap m_workingThreads;
            WaitableQueue<TaskPair, TaskPQ> m_Tasks;
            WaitableQueue<std::shared_ptr<WorkerThread> > m_availableThreads;

            std::atomic<bool> m_paused;
            std::shared_ptr<ITask> GetTask();

            std::function<std::shared_ptr<ITask>()>  wrap_for_func;

            TaskPriority ILIA = static_cast<TaskPriority>(3);
    };

}

#endif // __ILRD_RD132_THREADPOOL_HPP__
