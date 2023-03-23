
#include "Logger.hpp"
#include "LogMessage.hpp"

namespace ilrd
{
    Logger::Logger(): m_pool(1), m_level(ALL){} 
 
    Logger& Logger::Log(const LogMessage &msg_)
    {
        if(msg_.GetLogLevel() >= this->m_level)
        {
            m_pool.AddTask(std::shared_ptr<LogTask>(new LogTask(msg_.GetMessage(), msg_.GetLogLevel()))); 
        }
        return *this;
    }

    Logger& Logger::SetLevel(LogLevel level_)
    {
        m_level = level_;
        return *this;
    }
}