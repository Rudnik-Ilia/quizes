#pragma once

#include <functional>

#include "Semaphore.hpp"

namespace ilrd
{
    template<int ...>
    struct seq { };

    template<int N, int ...S>
    struct gens : gens<N-1, N-1, S...> { };

    template<int ...S>
    struct gens<0, S...> {
    typedef seq<S...> type;
    };

    template <class T, class... ARGS>
    class FutureTask : public ITask
    {
        public:
            explicit FutureTask(const std::function<T (ARGS...)> &task_, const ARGS&... args_);
            void Execute();
            T GetResult() const;
            
        private:
            std::function<T (ARGS...)> m_task;
            std::tuple<ARGS...> m_args; // it is not needed if you will use ARGS instead of ARGS...(pack)
            T m_result;
            mutable Semaphore m_semaphore;

            template<int ...S>
            void callFunc(seq<S...>){ m_result = m_func(std::get<S>(m_args)...); }

    };

    template <class T, class... ARGS>
    FutureTask<T, ARGS...>::FutureTask(const std::function<T (ARGS...)> &task_, const ARGS&... args_): m_task(tas), m_args(args_), m_semaphore(0){}

    template <class T, class... ARGS>
    void FutureTask<T, ARGS...>::Execute()
    {
        callFunc(typename gens<sizeof...(ARGS) > ::type());
        m_semaphore.Post();
    }

    template <class T, class... ARGS>
    T FutureTask<T, ARGS...>::GetResult() const
    {
        m_semaphore.Wait();
        return m_result;
    }
}



    