#include <iostream>
#include <fstream>

#include "LogTask.hpp"

namespace ilrd
{
    LogTask::LogTask(const std::string &message, const LogLevel &level): m_message(message) , m_level(level){}

    void LogTask::Execute()
    {
        std::ofstream fout("log.txt", std::ios_base::app);

        int i = 0;
        char buffer[FORMAT_PRINT];
        struct tm *newtime;
        int count = FORMAT_PRINT - m_message.length();
        time_t ltime;
        time(&ltime);
        newtime = localtime(&ltime);

        if(count)
        {
            while (--count)
            {
                buffer[i++] = '.';
            }
            buffer[i] = '\0';
        }

        fout << m_message << buffer << asctime(newtime) << std::endl;
        fout.close();
    }

}