#pragma once
#include "logger.h"
#include "spdlog/spdlog.h"

namespace LOG {

constexpr static int MAX_CHANNEL_NUMBER = (16);
constexpr static int MAX_FileSizeByte_PerLog = (50 * 1024 * 1024);

class LoggerPrivate
{
public:
    LoggerPrivate();
    ~LoggerPrivate();
    bool bToMainLog{false};
    std::shared_ptr<spdlog::logger> spdLog{nullptr};
};

class LoggerMgrPrivate
{
public:
    LoggerMgrPrivate();
    ~LoggerMgrPrivate();
    static Logger *mainLog;
    Logger loggers[MAX_CHANNEL_NUMBER]; /* ����ͨ����ӡ��Ϣ�����Զ��㼯���˴� MainLog:idx=0 ���� */
};

} // namespace CZLOG
