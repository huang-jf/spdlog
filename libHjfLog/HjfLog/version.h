#pragma once
#include "spdlog/version.h"

#define STR(a) #a
#define GET_SPDLOG_VER(i, a, b, c) STR(##i:##a.##b.##c)
#define SPDLOG_VER GET_SPDLOG_VER(spdlog, SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH)


#define FILE_VERSION        1,0,0,313 // 文件版本
#define FILE_VERSION_STR    "1.0.0.313"
#define COMPANY_NAME        "HJF"
#define INTERNAL_NAME       "HJFLog.dll"
#ifdef _WIN64 // x64在RC编译器中添加预处理宏_WIN64
#ifdef _DEBUG
#define FILE_DESCRIPTION "libHJFLog(x64_Debug)" // 文件说明，数字为编译时间
#else
#define FILE_DESCRIPTION "libHJFLog(x64_Release)"
#endif
#else
#ifdef _DEBUG
#define FILE_DESCRIPTION "libHJFLog(x86_Debug)"
#else
#define FILE_DESCRIPTION "libHJFLog(x86_Release)"
#endif
#endif
#define LEGAL_COPYRIGHT         "Copyright 2021-2021 HJF, Ltd. All rights reserved." // 版权
#define ORIGINAL_FILE_NAME      "libHJFLog.dll"                                                    // 原始文件名
#define PRODUCT_NAME            SPDLOG_VER                                                        // 产品名称
#define ORGANIZATION_DOMAIN     "http://www.cztek.cn/"                                           // 域名

