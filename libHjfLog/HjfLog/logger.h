#pragma once
/* ############  Export/Import  ############ */
#ifndef HJFLOG_API
#ifdef HJFLOG_EXPORTS
#ifdef __GNUC__
#define HJFLOG_API __attribute__((visibility("default")))
#else
#define HJFLOG_API __declspec(dllexport)
#endif
#else
#ifdef __GNUC__
#define HJFLOG_API __attribute__((visibility("default")))
#else
#define HJFLOG_API __declspec(dllimport)
#endif
#endif /* CZLOG_EXPORTS */
#endif /* CZLOG_API */
#include <stdint.h>
#include <string>

namespace LOG {

enum class Level
{
    Log_Trace = 0,
    Log_Debug = 1,
    Log_Info = 2,
    Log_Warn = 3,
    Log_Error = 4,
    Log_Critical = 5,
    Log_OFF = 6,
};

class LoggerMgr;
class LoggerPrivate;
class LoggerMgrPrivate;
class HJFLOG_API Logger
{
    friend class LoggerMgr;
    friend class LoggerMgrPrivate;

private:
    Logger();
    ~Logger();

public:
    void trace(const char *filename_in, int line_in, const char *funcname_in, const char *info) const;
    void debug(const char *filename_in, int line_in, const char *funcname_in, const char *info) const;
    void info(const char *filename_in, int line_in, const char *funcname_in, const char *info) const;
    void warn(const char *filename_in, int line_in, const char *funcname_in, const char *info) const;
    void error(const char *filename_in, int line_in, const char *funcname_in, const char *info) const;
    void critical(const char *filename_in, int line_in, const char *funcname_in, const char *info) const;

private:
    LoggerPrivate *d;
};

class HJFLOG_API LoggerMgr
{
private:
    LoggerMgr();
    ~LoggerMgr();

public:
    static bool GetVersion(char* libVer, int len);
    static Logger *GetLog(int id);
    // mainlog[id=0] collect the information of all other loggers.
    // id È¡Öµ·¶Î§[0,15]
    static bool InitFileLog(int id, const char *logPath, const char *moduleName, Level lvl, bool toMainLog = true);

private:
    static LoggerMgr *instance;
    LoggerMgrPrivate *dMgr;
};

} // namespace CZLOG
