#ifndef __ILRD_RD132_WORKERTHREAD_HPP__
#define __ILRD_RD132_WORKERTHREAD_HPP__

#include <thread>
#include <functional>

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
}

#endif // __ILRD_RD132_WORKERTHREAD_HPP__
