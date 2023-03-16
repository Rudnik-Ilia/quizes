#ifndef __ILRD_RD132_THREADPOOL_HPP__
#define __ILRD_RD132_THREADPOOL_HPP__

#include <thread> // thread
#include <atomic>
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <stdlib.h> /*abs*/

#include "WaitableQueue.hpp"
#include "PriorityQueue.hpp"
#include "ITask.hpp"
#include "ThreadMap.hpp"

namespace ilrd
{   
    // class StopTask: public ITask
    // {
    //     public:
    //         StopTask(ThreadMap &map_arg, WaitableQueue<std::shared_ptr<WorkerThread> > &wq_arg): m_workingThreads(map_arg), m_availableThreads(wq_arg){}
    //         void Execute()
    //         {
    //             ThreadMap::iterator iter;
    //             iter = m_workingThreads.Find(std::this_thread::get_id());
    //             iter->second->SwitchState();
    //             m_availableThreads.Push(iter->second);
    //             m_workingThreads.Remove(iter);
    //         }

    //     private:
    //         ThreadMap &m_workingThreads;
    //         WaitableQueue<std::shared_ptr<WorkerThread> > &m_availableThreads;
    // };

    // class PauseTask: public ITask
    // {
    //     public:
    //         PauseTask(std::mutex &mu, std::condition_variable &con, std::atomic<bool> &m_pau): mu_mutex(mu) , cond_var(con), m_paused(m_pau){};
    //         void Execute()
    //         {
    //             while(m_paused)
    //             {
    //                 std::unique_lock<std::mutex> lock(mu_mutex);
    //                 while(m_paused)
    //                 {
    //                     cond_var.wait(lock);
    //                 }
    //             }
    //         }

    //     private:
    //         std::mutex &mu_mutex;
    //         std::condition_variable &cond_var;
    //         std::atomic<bool> &m_paused;
    // };

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

    // ThreadPool::ThreadPool(std::size_t numOfThreads): m_numOfThreads(numOfThreads), m_paused(false), wrap_for_func(std::bind(&ThreadPool::GetTask, this))
    // {
    //     if(0 == numOfThreads)
    //     {
    //         m_numOfThreads = 5;
    //     }
    //     CreateAndPushThread(m_numOfThreads);
    // }

    // ThreadPool::~ThreadPool()
    // {
    //     Resume();
    //     #ifdef NDEBUG
    //     std::cout << "Dtor" << std::endl;
    //     #endif
    //     Stop(m_numOfThreads);
    // }

    // void ThreadPool::Stop(size_t times)
    // {
    //     for (size_t i = 0; i < times; ++i)
    //     {
    //         m_Tasks.Push(TaskPair(std::shared_ptr<StopTask>(new StopTask(m_workingThreads, m_availableThreads)), ThreadPool::ILIA));
    //     }

    //     for (size_t i = 0; i < times; ++i)
    //     {
    //        MyJoin();
    //     } 
    // }

    // void ThreadPool::MyJoin()
    // {
    //     std::shared_ptr<WorkerThread> work_thread;
    //     m_availableThreads.Pop(work_thread);
    //     work_thread->JoinThread();
    // }

    // void ThreadPool::AddTask(std::shared_ptr<ITask> task, TaskPriority taskPriority_)
    // {
    //     #ifdef NDEBUG
    //     std::cout << "PUSH"<< std::endl;
    //     #endif
    //     m_Tasks.Push(TaskPair(task, taskPriority_));
    // }

    // std::shared_ptr<ITask> ThreadPool::GetTask()
    // {
    //     TaskPair task_pair;
    //     m_Tasks.Pop(task_pair);
    //     return task_pair.first;
    // }

    // void ThreadPool::Pause()
    // {
    //     m_paused = true;  

    //     for (size_t i = 0; i < m_numOfThreads; ++i)
    //     {
    //         m_Tasks.Push(TaskPair(std::shared_ptr<PauseTask>(new PauseTask(m_mutex, m_conditon_var, m_paused)), ThreadPool::ILIA));
    //         #ifdef NDEBUG
    //         std::cout << "!!!" << std::endl;
    //         #endif
    //     }
    // }

    // void ThreadPool::Resume()
    // {   
    //     {
    //         std::unique_lock<std::mutex> lock(m_mutex);
    //         m_paused = false;
    //     }
    //     m_conditon_var.notify_all();
    // }

    // void ThreadPool::SetThreadNum(size_t n_)
    // {
    //     int check = n_ - m_numOfThreads;

    //     if(check < 0)
    //     {
    //         Stop(abs(check));
    //     }
    //     if(check > 0)
    //     {
    //         CreateAndPushThread(check);
    //     }
    //     this->m_numOfThreads = n_;
    // }

    // void ThreadPool::CreateAndPushThread(size_t times)
    // {
    //     for(size_t i = 0; i < times; ++i)
    //     {
    //         WorkerThread *work_thread = new WorkerThread(wrap_for_func);
    //         m_workingThreads.Insert({work_thread->GetTID(), std::shared_ptr<WorkerThread>(work_thread)});
    //     }
    // }

    // bool operator<(const ThreadPool::TaskPair &lhs, const ThreadPool::TaskPair &rhs)
    // {
    //     return lhs.second < rhs.second;
    // }

}

#endif // __ILRD_RD132_THREADPOOL_HPP__
