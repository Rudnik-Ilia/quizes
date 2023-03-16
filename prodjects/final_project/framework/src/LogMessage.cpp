#include <string>

#include "LogLevel.hpp"
#include "LogMessage.hpp"

namespace ilrd
{

    LogMessage::LogMessage(const std::string& s_, LogLevel level_): m_string(s_), m_level(level_){} 

    std::string LogMessage::GetMessage() const
    {
        return m_string;
    }
    LogLevel LogMessage::GetLogLevel() const
    {
        return m_level;
    }

}