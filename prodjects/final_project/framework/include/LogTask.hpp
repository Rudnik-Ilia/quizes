#pragma once 

#include <iostream>

#include "ITask.hpp"
#include "LogMessage.hpp"
#include "LogLevel.hpp"

namespace ilrd
{
    class LogTask: public ITask
    {
        public:
            LogTask(const std::string &message, const LogLevel &level);
            void Execute();
        
        private:
            const std::string m_message;
            const LogLevel m_level;
    };

    LogTask::LogTask(const std::string &message, const LogLevel &level): m_message(message) , m_level(level){}

    void LogTask::Execute()
    {
        std::cout << m_message << m_level << std::endl;
    }

}
