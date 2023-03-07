#ifndef __ILRD_RD132_THREADPOOL_HPP__
#define __ILRD_RD132_THREADPOOL_HPP__

#include <thread> // thread
#include <atomic>
#include <iostream>
#include <condition_variable>
#include <mutex>

#include "WaitableQueue.hpp"
#include "PriorityQueue.hpp"
#include "ITask.hpp"
#include "ThreadMap.hpp"

namespace ilrd
{   
    class PauseTask: public ITask
    {
        public:
            PauseTask(std::mutex* mu, std::condition_variable *con, std::atomic<bool> *m_pau): mu_mutex(mu) , cond_var(con), m_paused(m_pau){};
            void Execute()
            {
                std::unique_lock<std::mutex> lock(*mu_mutex);

                while(m_paused)
                {
                    cond_var->wait(lock);
                }
            }

        private:
            std::mutex *mu_mutex;
            std::condition_variable *cond_var;
            std::atomic<bool> *m_paused;
    };

    class ThreadPool
    {
        public:
            enum TaskPriority { PRIORITY_LOW = 0, PRIORITY_NORMAL = 1, PRIORITY_HIGH = 2};

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

            std::mutex m_mutex;
            std::condition_variable m_conditon_var;

            ThreadMap m_workingThreads;
            WaitableQueue<TaskPair, TaskPQ> m_Tasks;
            WaitableQueue<std::shared_ptr<WorkerThread> > m_availableThreads;

            std::atomic<bool> m_paused;
            std::shared_ptr<ITask> GetTask();

            std::shared_ptr<ITask> pause_func;   
    };

    ThreadPool::ThreadPool(std::size_t numOfThreads): m_numOfThreads(numOfThreads), m_paused(false), pause_func()
    {
        if(0 == numOfThreads)
        {
            m_numOfThreads = 10;
        }
        size_t tmp = m_numOfThreads;
        std::function<std::shared_ptr<ITask>()>  wrap_for_func = std::bind(&ThreadPool::GetTask, this);
    
        while(tmp--)
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
        m_Tasks.Push(TaskPair(task, taskPriority_));
    }

    std::shared_ptr<ITask> ThreadPool::GetTask()
    {
        TaskPair task_pair;
        m_Tasks.Pop(task_pair);
        return task_pair.first;
    }

    void ThreadPool::Pause()
    {
        m_paused = true;  
        std::cout << "NUMOF:  " <<  m_numOfThreads << std::endl;


        for (size_t i = 0; i < m_numOfThreads; ++i)
        {
            m_Tasks.Push(TaskPair(std::shared_ptr<PauseTask>(new PauseTask(&m_mutex, &m_conditon_var, &m_paused)), ThreadPool::PRIORITY_HIGH));
            // std::cout << "!!!" << std::endl;
        }
    }

    void ThreadPool::Resume()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_paused = false;
        m_conditon_var.notify_all();
    }


    bool operator<(const ThreadPool::TaskPair &lhs, const ThreadPool::TaskPair &rhs)
    {
        return lhs.second < rhs.second;
    }




}

#endif // __ILRD_RD132_THREADPOOL_HPP__
