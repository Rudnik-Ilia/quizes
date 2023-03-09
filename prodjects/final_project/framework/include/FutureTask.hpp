#pragma once

#include <functional>

namespace ilrd
{
    template <class ReturnType, class... ARGS>
    class FutureTask : public ITask
    {
        public:
            explicit FutureTask(const std::function<ReturnType (ARGS...)> &task_, const ARGS&... args_);

            void Execute() override;
            ReturnType GetResult() const;
            
        private:
            std::function<ReturnType (ARGS...)> m_task;
            std::tuple<ARGS...> m_args; // it is not needed if you will use ARGS instead of ARGS...(pack)
            ReturnType m_result;
            mutable ilrd::Semaphore m_semaphore;
    };
    template <class ReturnType, class... ARGS>
    FutureTask<ReturnType, ARGS...>::FutureTask(const std::function<ReturnType (ARGS...)> &task_, const ARGS&... args_)
    {

    }

    template <class ReturnType, class... ARGS>
    void FutureTask<ReturnType, ARGS...>::Execute()
    {

    }

    template <class ReturnType, class... ARGS>
    ReturnType FutureTask<ReturnType, ARGS...>::GetResult() const
    {

    }
}



    