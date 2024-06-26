
#include <iostream>

#include "WorkerThread.hpp"


namespace ilrd
{
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