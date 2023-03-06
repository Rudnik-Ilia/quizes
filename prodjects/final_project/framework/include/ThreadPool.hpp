#ifndef __ILRD_RD132_THREADPOOL_HPP__
#define __ILRD_RD132_THREADPOOL_HPP__

#include <thread> // thread
#include <atomic>

#include "WaitableQueue.hpp"
#include "PriorityQueue.hpp"
#include "ITask.hpp"
#include "ThreadMap.hpp"

namespace ilrd
{

    class ThreadPool
    {
        public:
            enum TaskPriority { PRIORITY_HIGH = 1, PRIORITY_NORMAL = 2, PRIORITY_LOW = 3 };

            typedef std::pair<std::shared_ptr<ITask>, TaskPriority> TaskPair;

            typedef PriorityQueue<TaskPair, std::vector<TaskPair>, std::less<TaskPair> > TaskPQ;

            explicit ThreadPool(std::size_t numOfThreads = std::thread::hardware_concurrency()); // check in ctor body 0 == numOfThreads
            
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

            void Stop();

            std::size_t m_numOfThreads;
            ThreadMap m_workingThreads;
            WaitableQueue<TaskPair, TaskPQ> m_Tasks;
            WaitableQueue<std::thread> m_availableThreads;

            std::atomic<bool> m_paused;
            std::shared_ptr<ITask> GetTask();

            class Compare
            {
                public:
                    bool operator() (TaskPair a, TaskPair b)
                    {
                        return (a.first > b.first);
                    }
            };

           
    };

    ThreadPool::ThreadPool(std::size_t numOfThreads): m_numOfThreads(numOfThreads), m_paused(false)
    {
        if(0 == numOfThreads)
        {
            m_numOfThreads = 10;
        }
        std::function<std::shared_ptr<ITask>()>  wrap_for_func = std::bind(&ThreadPool::GetTask, this);

        while(m_numOfThreads--)
        {
            WorkerThread * work_thread = new WorkerThread(wrap_for_func);
            m_workingThreads.Insert({work_thread->GetTID(), std::shared_ptr<WorkerThread>(work_thread)});
        }
    }

    ThreadPool::~ThreadPool()
    {
        Stop();
    }

    void ThreadPool::Stop()
    {
        for (size_t i = 0; i < m_numOfThreads; ++i)
        {
            
        }
        
    }

    void ThreadPool::AddTask(std::shared_ptr<ITask> task, TaskPriority taskPriority_)
    {
        TaskPair task_pair(task, taskPriority_);
        m_Tasks.Push(task_pair);
    }

    std::shared_ptr<ITask> ThreadPool::GetTask()
    {
        TaskPair task_pair;
        // m_Tasks.Pop();q
    }

}

#endif // __ILRD_RD132_THREADPOOL_HPP__
