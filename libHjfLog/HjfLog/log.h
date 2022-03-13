#pragma once
#include <string>
#include <stdio.h>
#include "logger.h"

#define CLOG_FUNCTION static_cast<const char *>(__FUNCTION__)

template<typename... Args>
static std::string loglineprintf(const char *fmt, Args... args)
{
    char cstr[1024];
    snprintf(cstr, sizeof(cstr), fmt, args...);
    return std::string(cstr);
}

static std::string loglineprintf(const char *fmt)
{
    return std::string(fmt);
}

#define cTrace(id, ...) LOG::LoggerMgr::GetLog(id)->trace(__FILE__, __LINE__, CLOG_FUNCTION, loglineprintf(__VA_ARGS__).c_str())
#define cDebug(id, ...) LOG::LoggerMgr::GetLog(id)->debug(__FILE__, __LINE__, CLOG_FUNCTION, loglineprintf(__VA_ARGS__).c_str())
#define cInfo(id, ...)  LOG::LoggerMgr::GetLog(id)->info(__FILE__, __LINE__, CLOG_FUNCTION, loglineprintf(__VA_ARGS__).c_str())
#define cWarn(id, ...)  LOG::LoggerMgr::GetLog(id)->warn(__FILE__, __LINE__, CLOG_FUNCTION, loglineprintf(__VA_ARGS__).c_str())
#define cError(id, ...) LOG::LoggerMgr::GetLog(id)->error(__FILE__, __LINE__, CLOG_FUNCTION, loglineprintf(__VA_ARGS__).c_str())
#define cCritical(id, ...) LOG::LoggerMgr::GetLog(id)->critical(__FILE__, __LINE__, CLOG_FUNCTION, loglineprintf(__VA_ARGS__).c_str()