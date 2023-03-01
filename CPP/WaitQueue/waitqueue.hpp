#ifndef __ILRD_RD132_WAITABLEQUEUE_H__
#define __ILRD_RD132_WAITABLEQUEUE_H__

#include <iostream>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <chrono>


namespace ilrd 
{

    template <typename T, typename CONTAINER = std::queue<T>> class WaitableQueue 
    {
    public:
    explicit WaitableQueue() = default;
    explicit WaitableQueue(const WaitableQueue &other_) = delete;
    explicit WaitableQueue(WaitableQueue &&other_) = default;
    WaitableQueue &operator=(const WaitableQueue &other_) = delete;
    WaitableQueue &operator=(WaitableQueue &&other_) = default;
    ~WaitableQueue() = default;

    bool Pop(std::chrono::milliseconds time_ms_, T &outparam_);
    void Pop(T &outparam_);
    void Push(const T &element);
    bool IsEmpty() const;

    private:
    CONTAINER m_container{};
    mutable std::mutex m_mutex{};
    std::condition_variable m_nonEmptyCond{};

    }; // class WQueue


    template<typename T, typename CONTAINER> 
    void WaitableQueue<T, CONTAINER>::Push(const T &element)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_container.push(element);
        lock.unlock();
        m_nonEmptyCond.notify_one();
    }

    template<typename T, typename CONTAINER> 
    bool WaitableQueue<T, CONTAINER>::IsEmpty() const
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_container.empty();
    }

    template<typename T, typename CONTAINER> 
    void WaitableQueue<T, CONTAINER>::Pop(T &outparam_)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        while(m_container.empty())
        {
            m_nonEmptyCond.wait(lock);
        }
        outparam_ = m_container.front();
        m_container.pop();
    }

    template<typename T, typename CONTAINER> 
    bool WaitableQueue<T, CONTAINER>::Pop(std::chrono::milliseconds time_ms_, T &outparam_)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        std::chrono::time_point<std::chrono::system_clock> time_until = std::chrono::system_clock::now() + time_ms_;

        while(m_container.empty())
        {
            if(std::cv_status::timeout == m_nonEmptyCond.wait_until(lock, time_until))
            {
                return false;
            }
        }

        // if(false == m_nonEmptyCond.wait_for(lock, time_ms_, !m_container.empty))
        // {
        //     return false;
        // }

        outparam_ = m_container.front();
        m_container.pop();

        return true;
    }


} // namespace ilrd

#endif /* __ILRD_RD132_WAITABLEQUEUE_H__ */