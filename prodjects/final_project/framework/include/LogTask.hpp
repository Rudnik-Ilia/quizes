#ifndef __ILRD_RD132_LOG_TASK_HPP__
#define __ILRD_RD132_LOG_TASK_HPP__

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

#endif // __ILRD_RD132_LOG_TASK_HPP__
