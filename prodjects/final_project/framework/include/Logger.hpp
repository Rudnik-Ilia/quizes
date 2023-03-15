#ifndef __ILRD_RD132_LOGGER_HPP__
#define __ILRD_RD132_LOGGER_HPP__


#include <iostream>

#include "LogMessage.hpp"
#include "Singleton.hpp"
// #include "Handleton.hpp"


namespace ilrd
{
    class Logger
    {
        public:
            Logger(const Logger &) = delete;
            Logger(Logger &&) = delete;
            Logger &operator=(const Logger &) = delete;
            Logger &operator=(Logger &&) = delete;

            void Log(const LogMessage & msg_);
            void SetLevel(LogLevel level_);

        private:
            LogLevel m_level;

            Logger() = default;
            ~Logger() = default;

            friend Singleton<Logger>;
            friend Handleton<Logger>;
    };

} // namespace ilrd

#endif //__ILRD_RD132_LOGGER_HPP__
