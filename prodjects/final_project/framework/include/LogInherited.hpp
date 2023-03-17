#pragma once

#include "LogMessage.hpp"

namespace ilrd
{
    /**************************************************************************************************************/
    class TraceLog: public LogMessage
    {
        public:
            TraceLog(const std::string &message);
            virtual std::string GetMessage() const;
            virtual LogLevel GetLogLevel() const;
    };

    /**************************************************************************************************************/
     class DebugLog: public LogMessage
    {
        public:
            DebugLog(const std::string &message);
            virtual std::string GetMessage() const;
            virtual LogLevel GetLogLevel() const;
    };

    /**************************************************************************************************************/
    class InfoLog: public LogMessage
    {
        public:
            InfoLog(const std::string &message);
            virtual std::string GetMessage() const;
            virtual LogLevel GetLogLevel() const;
    };

    /**************************************************************************************************************/
    class WarnLog: public LogMessage
    {
        public:
            WarnLog(const std::string &message);
            virtual std::string GetMessage() const;
            virtual LogLevel GetLogLevel() const;
    };

    /**************************************************************************************************************/
    class ErrorLog: public LogMessage
    {
        public:
            ErrorLog(const std::string &message);
            virtual std::string GetMessage() const;
            virtual LogLevel GetLogLevel() const;
    };

    /**************************************************************************************************************/
    class FatalLog: public LogMessage
    {
        public:
            FatalLog(const std::string &message);
            virtual std::string GetMessage() const;
            virtual LogLevel GetLogLevel() const;
    };

}