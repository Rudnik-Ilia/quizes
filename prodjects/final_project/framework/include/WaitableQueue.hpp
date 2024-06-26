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

    template <typename T, typename CONTAINER = std::queue<T>> 
    class WaitableQueue 
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
    bool isEmpty() const;

    private:
    CONTAINER m_container{};
    mutable std::mutex m_mutex{};
    std::condition_variable m_nonEmptyCond{};

    }; // class WQueue


    template<typename T, typename CONTAINER> 
    void WaitableQueue<T, CONTAINER>::Push(const T &element)
    {
        {
            std::unique_lock<std::mutex> m_lock(m_mutex);
            m_container.push(element);
        }
        
        m_nonEmptyCond.notify_one();
    }

    template<typename T, typename CONTAINER> 
    bool WaitableQueue<T, CONTAINER>::isEmpty() const
    {
        std::unique_lock<std::mutex> m_lock(m_mutex);
        return m_container.empty();
    }

    template<typename T, typename CONTAINER> 
    void WaitableQueue<T, CONTAINER>::Pop(T &outparam_)
    {
        std::unique_lock<std::mutex> m_lock(m_mutex);
        m_nonEmptyCond.wait(m_lock, [&]{return this->m_container.empty() == false;});
        outparam_ = m_container.front();
        m_container.pop();
    }

    template<typename T, typename CONTAINER> 
    bool WaitableQueue<T, CONTAINER>::Pop(std::chrono::milliseconds time_ms_, T &outparam_)
    {
        std::unique_lock<std::mutex> m_lock(m_mutex);
        if(false == m_nonEmptyCond.wait_for(m_lock, time_ms_, [&]{return this->m_container.empty() == false;}))
        {
            return false;
        }
        
        outparam_ = m_container.front();
        m_container.pop();

        return true;
    }

} // namespace ilrd

#endif /* __ILRD_RD132_WAITABLEQUEUE_H__ */