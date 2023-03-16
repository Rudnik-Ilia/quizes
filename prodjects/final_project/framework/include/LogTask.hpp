#pragma once 

#include <iostream>
#include <fstream>
#include <cstring>

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
        std::ofstream fout("txt.txt", std::ios_base::app);

        int lenght = m_message.length();
        int i = 0;
        char buffer[60];
        struct tm *newtime;
        int count = 60 - lenght;
        time_t ltime;
        time(&ltime);
        newtime = localtime(&ltime);

        if(count)
        {
            while (--count)
            {
                buffer[ i++] = '.';
            }
            buffer[i] = '\0';
        }

        fout << m_message << buffer << asctime(newtime) << std::endl;
        std::cout << m_message << buffer << asctime(newtime) << std::endl;
        fout.close();

    }

}
