#pragma once

#define FORMAT_PRINT (90)

#include "ITask.hpp"
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

}


