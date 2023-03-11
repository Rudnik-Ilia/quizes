# pragma once

#include <cstddef>
#include <mutex>
#include <condition_variable>

namespace ilrd
{
    class Semaphore{

        public:
            inline explicit Semaphore(size_t value_ = 0);
            
            explicit Semaphore(const Semaphore &other_) = delete;
            explicit Semaphore(Semaphore &&other_) = delete;

            Semaphore& operator=(const Semaphore &other_) = delete;
            Semaphore& operator=(Semaphore &&other_) = delete;

            ~Semaphore() = default;

            inline void Wait();
            inline void Post();
            inline bool TryWait();

        private:
            int m_counter;
            std::mutex m_mutex;
            std::condition_variable condition;
        }; 

        Semaphore::Semaphore(size_t value_):m_counter(value_) {}

        void Semaphore::Post()
        {
            {
                std::unique_lock<std::mutex> lock(m_mutex);
                ++m_counter;
            }
            condition.notify_one();
        }

        void Semaphore::Wait()
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            while (m_counter <= 0)
            {
                condition.wait(lock);
            }
            --m_counter;
        }

        bool Semaphore::TryWait()
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            if(m_counter)
            {
                --m_counter;
                return true;
            }
            return false;
        }
}
