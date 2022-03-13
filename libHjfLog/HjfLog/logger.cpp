#include "logger.h"
#include "logger_p.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "version.h"
#include <string>

namespace LOG {
    Logger::Logger()
    {
        this->d = new LoggerPrivate();
    }

    Logger::~Logger()
    {
        delete this->d;
        this->d = nullptr;
    }

    void Logger::trace(const char* filename_in, int line_in, const char* funcname_in, const char* info) const
    {
        this->d->spdLog->log(spdlog::source_loc{ filename_in, line_in, funcname_in }, spdlog::level::trace, info);
        if (this->d->bToMainLog && (LoggerMgrPrivate::mainLog->d->spdLog.get() != nullptr))
            LoggerMgrPrivate::mainLog->d->spdLog->log(spdlog::source_loc{ filename_in, line_in, funcname_in }, spdlog::level::trace, info);
    }

    void Logger::debug(const char* filename_in, int line_in, const char* funcname_in, const char* info) const
    {
        this->d->spdLog->log(spdlog::source_loc{ filename_in, line_in, funcname_in }, spdlog::level::debug, info);
        if (this->d->bToMainLog && (LoggerMgrPrivate::mainLog->d->spdLog.get() != nullptr))
            LoggerMgrPrivate::mainLog->d->spdLog->log(spdlog::source_loc{ filename_in, line_in, funcname_in }, spdlog::level::debug, info);
    }

    void Logger::info(const char* filename_in, int line_in, const char* funcname_in, const char* info) const
    {
        this->d->spdLog->log(spdlog::source_loc{ filename_in, line_in, funcname_in }, spdlog::level::info, info);
        if (this->d->bToMainLog && (LoggerMgrPrivate::mainLog->d->spdLog.get() != nullptr))
            LoggerMgrPrivate::mainLog->d->spdLog->log(spdlog::source_loc{ filename_in, line_in, funcname_in }, spdlog::level::info, info);
    }

    void Logger::warn(const char* filename_in, int line_in, const char* funcname_in, const char* info) const
    {
        this->d->spdLog->log(spdlog::source_loc{ filename_in, line_in, funcname_in }, spdlog::level::warn, info);
        if (this->d->bToMainLog && (LoggerMgrPrivate::mainLog->d->spdLog.get() != nullptr))
            LoggerMgrPrivate::mainLog->d->spdLog->log(spdlog::source_loc{ filename_in, line_in, funcname_in }, spdlog::level::warn, info);
    }

    void Logger::error(const char* filename_in, int line_in, const char* funcname_in, const char* info) const
    {
        this->d->spdLog->log(spdlog::source_loc{ filename_in, line_in, funcname_in }, spdlog::level::err, info);
        if (this->d->bToMainLog && (LoggerMgrPrivate::mainLog->d->spdLog.get() != nullptr))
            LoggerMgrPrivate::mainLog->d->spdLog->log(spdlog::source_loc{ filename_in, line_in, funcname_in }, spdlog::level::err, info);
    }

    void Logger::critical(const char* filename_in, int line_in, const char* funcname_in, const char* info) const
    {
        this->d->spdLog->log(spdlog::source_loc{ filename_in, line_in, funcname_in }, spdlog::level::critical, info);
        if (this->d->bToMainLog && (LoggerMgrPrivate::mainLog->d->spdLog.get() != nullptr))
            LoggerMgrPrivate::mainLog->d->spdLog->log(spdlog::source_loc{ filename_in, line_in, funcname_in }, spdlog::level::critical, info);
    }

    LoggerPrivate::LoggerPrivate() {}

    LoggerPrivate::~LoggerPrivate() {}


    bool LoggerMgr::GetVersion(char* libVer, int len)
    {
        char cstr[256];
        snprintf(cstr, sizeof(cstr), "libCzLog:V%s;spdLog:V%d.%d.%d", FILE_VERSION_STR, SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);
        int size = (int)(std::string(cstr).size() + 1);
        memcpy(libVer, cstr, size);
        if (len < size)
            libVer[len - 1] = '\0';
        return len >= size;
    }

    Logger* LoggerMgr::GetLog(int idx /*id*/)
    {
        assert(LoggerMgr::instance->dMgr->loggers[idx].d->spdLog != nullptr);
        return &(LoggerMgr::instance->dMgr->loggers[idx]);
    }

    bool LoggerMgr::InitFileLog(int idx /*id*/, const char* logPath, const char* moduleName, Level lvl, bool toMainLog)
    {
        if (idx >= MAX_CHANNEL_NUMBER)
            return false;

        const Logger& logger = LoggerMgr::instance->dMgr->loggers[idx];
        if (logger.d->spdLog.get() == nullptr)
        {
            logger.d->spdLog = std::make_shared<spdlog::logger>(moduleName);
        }
        logger.d->bToMainLog = (idx == 0) ? false : toMainLog;
        {
            const std::string strLogFileName = logPath + std::string("/") + moduleName + ".log";
            auto rotating = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(strLogFileName, (int)(MAX_FileSizeByte_PerLog / 3), 2, false);
            rotating->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%l] [%s@%!:+%#] %v");
            logger.d->spdLog->sinks().push_back(rotating);
        }

        logger.d->spdLog->set_level((spdlog::level::level_enum)lvl);
        logger.d->spdLog->flush_on((spdlog::level::level_enum)lvl);
        return true;
    }

    LoggerMgr* LoggerMgr::instance = new LoggerMgr();
    LoggerMgr::LoggerMgr()
    {
        this->dMgr = new LoggerMgrPrivate();
        LoggerMgrPrivate::mainLog = &(this->dMgr->loggers[0]);
    }

    LoggerMgr::~LoggerMgr()
    {
        delete this->dMgr;
        this->dMgr = nullptr;
    }
    Logger* LoggerMgrPrivate::mainLog = nullptr;
    LoggerMgrPrivate::LoggerMgrPrivate() {}

    LoggerMgrPrivate::~LoggerMgrPrivate() {}

} // namespace CZLOG