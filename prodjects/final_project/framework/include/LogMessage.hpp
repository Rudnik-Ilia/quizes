#ifndef __ILRD_RD132_LOG_MESSAGE_HPP__
#define __ILRD_RD132_LOG_MESSAGE_HPP__

#include <string>

#include "LogLevel.hpp"

namespace ilrd
{

    class LogMessage
    {
        public:
            LogMessage(const std::string& s_);
            virtual ~LogMessage() = default;

            virtual std::string GetMessage() const;
            virtual LogLevel GetLogLevel() const;

        private: 
    };
}
    

#endif // __ILRD_RD132_LOG_MESSAGE_HPP__
