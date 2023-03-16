#ifndef __ILRD_RD132_WORKERTHREAD_HPP__
#define __ILRD_RD132_WORKERTHREAD_HPP__

#include <thread>
#include <functional>
#include <iostream>

#include "ITask.hpp"

namespace ilrd
{
    class WorkerThread
    {
        public:
            enum State {RUNNING, STOPPED};

            explicit WorkerThread(std::function<std::shared_ptr<ITask>()> fGetTask_);
            
            explicit WorkerThread(WorkerThread &&) = default;
            WorkerThread(const WorkerThread &) = delete;
            WorkerThread &operator=(WorkerThread &&) = default;
            WorkerThread &operator=(const WorkerThread &) = delete;
            ~WorkerThread() = default;

            void Stop();
            State GetState() const;
            std::thread::id GetTID() const;

            void SwitchState();
            void JoinThread();

        private:
            State m_state;
            std::function<std::shared_ptr<ITask>()> m_taskGetter;
            std::thread m_thread;
            void Run();
    };

    WorkerThread::WorkerThread(std::function<std::shared_ptr<ITask>()> fGetTask_): m_state(RUNNING), m_taskGetter(fGetTask_), m_thread(std::bind(&WorkerThread::Run, this)){}

    WorkerThread::State WorkerThread::GetState() const
    {
        return m_state;
    }

    std::thread::id WorkerThread::GetTID() const
    {
        return m_thread.get_id();
    }

    void WorkerThread::Stop()
    {
        m_state = STOPPED;
    }

    void WorkerThread::Run()
    {
        while (m_state == RUNNING)
        {
            #ifdef NDEBUG
            std::cout << "LOOP" << std::endl;
            #endif
            m_taskGetter().get()->Execute();
        } 
    }

    void WorkerThread::SwitchState()
    {
        m_state = STOPPED;
    }

    void WorkerThread::JoinThread()
    {
        m_thread.join();
    }
}

#endif // __ILRD_RD132_WORKERTHREAD_HPP__
