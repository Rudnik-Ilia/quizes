
#include "LogMessage.hpp"
#include "LogInherited.hpp"

#define COLOR_RED "\033[1;31m" 
#define COLOR_BLUE "\033[1;34m" 
#define OFFCOLOR "\033[0m" 

namespace ilrd
{

/**************************************************************************************************************/
TraceLog::TraceLog(const std::string &message): LogMessage(message, TRACE){}

std::string TraceLog::GetMessage() const
{
    return "[TRACE]: " + LogMessage::GetMessage() + "!";
}

LogLevel TraceLog::GetLogLevel() const
{
    return LogMessage::GetLogLevel();
}
/**************************************************************************************************************/

DebugLog::DebugLog(const std::string &message): LogMessage(message, DEBUG){}
    
std::string DebugLog::GetMessage() const
{
    return "[DEBUGLOG]: " + LogMessage::GetMessage() + "!";
}

LogLevel DebugLog::GetLogLevel() const
{
    return LogMessage::GetLogLevel();
}
/**************************************************************************************************************/
InfoLog::InfoLog(const std::string &message): LogMessage(message, INFO){}

std::string InfoLog::GetMessage() const
{
    return "[INFORMATION]: " + LogMessage::GetMessage() + "!";
}

LogLevel InfoLog::GetLogLevel() const
{
    return LogMessage::GetLogLevel();
}
/**************************************************************************************************************/
WarnLog::WarnLog(const std::string &message): LogMessage(message, WARN){}

std::string WarnLog::GetMessage() const
{
    return "[WARNING]: " + LogMessage::GetMessage() + "!";
}

LogLevel WarnLog::GetLogLevel() const
{
    return LogMessage::GetLogLevel();
}
/**************************************************************************************************************/

ErrorLog::ErrorLog(const std::string &message): LogMessage(message, ERROR){}

std::string ErrorLog::GetMessage() const
{
    return "[ERROR]: " + LogMessage::GetMessage() + "!";
}

LogLevel ErrorLog::GetLogLevel() const
{
    return LogMessage::GetLogLevel();
}
/**************************************************************************************************************/

FatalLog::FatalLog(const std::string &message): LogMessage(message, FATAL){}

std::string FatalLog::GetMessage() const
{
    return "[FATAL]: " + LogMessage::GetMessage() + "!";
}

LogLevel FatalLog::GetLogLevel() const
{
    return LogMessage::GetLogLevel();
}
/**************************************************************************************************************/
}