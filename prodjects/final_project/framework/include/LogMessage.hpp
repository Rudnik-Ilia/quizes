#ifndef __ILRD_RD132_LOG_MESSAGE_HPP__
#define __ILRD_RD132_LOG_MESSAGE_HPP__

#include <string>

#include "LogLevel.hpp"

namespace ilrd
{
    class LogMessage
    {
        public:

            LogMessage(const std::string& s_,  LogLevel level_);
            virtual ~LogMessage() = default;

            virtual std::string GetMessage() const;
            virtual LogLevel GetLogLevel() const;

        private: 
            const std::string m_string;
            LogLevel m_level;

    };

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
    

#endif // __ILRD_RD132_LOG_MESSAGE_HPP__
