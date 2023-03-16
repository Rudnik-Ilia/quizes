#pragma once
#include <iostream>
#include <cstring>
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

    // TraceLog::TraceLog(const std::string &message): LogMessage(message, TRACE){}
    
    // std::string TraceLog::GetMessage() const
    // {
    //     return "[TRACE]: " + LogMessage::GetMessage() + "!";
    // }

    // LogLevel TraceLog::GetLogLevel() const
    // {
    //     return LogMessage::GetLogLevel();
    // }
    /**************************************************************************************************************/
     class DebugLog: public LogMessage
    {
        public:
            DebugLog(const std::string &message);
            virtual std::string GetMessage() const;
            virtual LogLevel GetLogLevel() const;
    };

    // DebugLog::DebugLog(const std::string &message): LogMessage(message, DEBUG){}
     
    // std::string DebugLog::GetMessage() const
    // {
    //     return "[DEBUGLOG]: " + LogMessage::GetMessage() + "!";
    // }

    // LogLevel DebugLog::GetLogLevel() const
    // {
    //     return LogMessage::GetLogLevel();
    // }
    /**************************************************************************************************************/
    class InfoLog: public LogMessage
    {
        public:
            InfoLog(const std::string &message);
            virtual std::string GetMessage() const;
            virtual LogLevel GetLogLevel() const;
    };

    // InfoLog::InfoLog(const std::string &message): LogMessage(message, INFO){}
    
    // std::string InfoLog::GetMessage() const
    // {
    //     return "[INFORMATION]: " + LogMessage::GetMessage() + "!";
    // }

    // LogLevel InfoLog::GetLogLevel() const
    // {
    //     return LogMessage::GetLogLevel();
    // }
    /**************************************************************************************************************/
    class WarnLog: public LogMessage
    {
        public:
            WarnLog(const std::string &message);
            virtual std::string GetMessage() const;
            virtual LogLevel GetLogLevel() const;
    };

    // WarnLog::WarnLog(const std::string &message): LogMessage(message, WARN){}
    
    // std::string WarnLog::GetMessage() const
    // {
    //     return "[WARNING]: " + LogMessage::GetMessage() + "!";
    // }

    // LogLevel WarnLog::GetLogLevel() const
    // {
    //     return LogMessage::GetLogLevel();
    // }
    /**************************************************************************************************************/
    class ErrorLog: public LogMessage
    {
        public:
            ErrorLog(const std::string &message);
            virtual std::string GetMessage() const;
            virtual LogLevel GetLogLevel() const;
    };

    // ErrorLog::ErrorLog(const std::string &message): LogMessage(message, ERROR){}
    
    // std::string ErrorLog::GetMessage() const
    // {
    //     return "[ERROR]: " + LogMessage::GetMessage() + "!";
    // }

    // LogLevel ErrorLog::GetLogLevel() const
    // {
    //     return LogMessage::GetLogLevel();
    // }
    /**************************************************************************************************************/
    class FatalLog: public LogMessage
    {
        public:
            FatalLog(const std::string &message);
            virtual std::string GetMessage() const;
            virtual LogLevel GetLogLevel() const;
    };

    // FatalLog::FatalLog(const std::string &message): LogMessage(message, FATAL){}
    
    // std::string FatalLog::GetMessage() const
    // {
    //     return "[FATAL]: " + LogMessage::GetMessage() + "!";
    // }

    // LogLevel FatalLog::GetLogLevel() const
    // {
    //     return LogMessage::GetLogLevel();
    // }

}