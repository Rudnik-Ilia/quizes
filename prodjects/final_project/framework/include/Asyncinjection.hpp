#ifndef __ILRD_RD132_ASYNC_INJECTION_HPP__
#define __ILRD_RD132_ASYNC_INJECTION_HPP__

#include <functional> // std::function
#include <chrono> //std::chrono::milliseconds

#include "ITask.hpp"

namespace ilrd
{
    
class AsyncInjection
{
public:
    
    explicit AsyncInjection(const std::function<bool()>& action_, std::chrono::milliseconds timeout_);
    
    // Non-copyable, non-movable
    AsyncInjection(const AsyncInjection&) = delete;
    AsyncInjection& operator=(const AsyncInjection&) = delete;
    AsyncInjection(AsyncInjection&&) = delete;
    AsyncInjection& operator=(AsyncInjection&&) = delete;
      
    //static AsyncInjection *CreateAsyncInjection(const std::function<bool()>& action_,
    //                                            std::chrono::milliseconds timeout_);

private:
    ~AsyncInjection();
    std::function<bool()> m_action;
    class AsyncTask : public ITask;
    
};
    
} // namespace ilrd

#endif // __ILRD_RD132_ASYNC_INJECTION_HPP__
