#pragma once
#include "spdlog/version.h"

#define STR(a) #a
#define GET_SPDLOG_VER(i, a, b, c) STR(##i:##a.##b.##c)
#define SPDLOG_VER GET_SPDLOG_VER(spdlog, SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH)


#define FILE_VERSION        1,0,0,313 // �ļ��汾
#define FILE_VERSION_STR    "1.0.0.313"
#define COMPANY_NAME        "HJF"
#define INTERNAL_NAME       "HJFLog.dll"
#ifdef _WIN64 // x64��RC�����������Ԥ�����_WIN64
#ifdef _DEBUG
#define FILE_DESCRIPTION "libHJFLog(x64_Debug)" // �ļ�˵��������Ϊ����ʱ��
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
#define LEGAL_COPYRIGHT         "Copyright 2021-2021 HJF, Ltd. All rights reserved." // ��Ȩ
#define ORIGINAL_FILE_NAME      "libHJFLog.dll"                                                    // ԭʼ�ļ���
#define PRODUCT_NAME            SPDLOG_VER                                                        // ��Ʒ����
#define ORGANIZATION_DOMAIN     "http://www.cztek.cn/"                                           // ����

