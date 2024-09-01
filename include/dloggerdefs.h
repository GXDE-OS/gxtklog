// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-2.1-or-later
#ifndef DLOGGER_DEFINE_H
#define DLOGGER_DEFINE_H

#include "dlog_global.h"
#include <QLoggingCategory>

DLOG_CORE_BEGIN_NAMESPACE

class Logger;
class GLogHelper;
LIBDLOG_SHARED_EXPORT Logger *loggerInstance();
#define dlogger loggerInstance()

#define DLOG_CTX(category) QMessageLogContext(__FILE__, __LINE__, Q_FUNC_INFO, category)

// include GLog or dloghelper.h
#define dTrace GLogHelper(Logger::Trace, DLOG_CTX("default")).write
#define dDebug GLogHelper(Logger::Debug, DLOG_CTX("default")).write
#define dInfo GLogHelper(Logger::Info, DLOG_CTX("default")).write
#define dWarning GLogHelper(Logger::Warning, DLOG_CTX("default")).write
#define dError GLogHelper(Logger::Error, DLOG_CTX("default")).write
#define dFatal GLogHelper(Logger::Fatal, DLOG_CTX("default")).write

#define dCDebug(category) GLogHelper(Logger::Debug, DLOG_CTX(category)).write()
#define dCInfo(category) GLogHelper(Logger::Info, DLOG_CTX(category)).write()
#define dCWarning(category) GLogHelper(Logger::Warning, DLOG_CTX(category)).write()
#define dCError(category) GLogHelper(Logger::Error, DLOG_CTX(category)).write()
#define dCFatal(category) GLogHelper(Logger::Fatal, DLOG_CTX(category)).write()

#define dTraceTime                                         \
    GLogHelper helper(Logger::Trace, DLOG_CTX("default")); \
    helper.timing
#define dDebugTime                                         \
    GLogHelper helper(Logger::Debug, DLOG_CTX("default")); \
    helper.timing
#define dInfoTime                                         \
    GLogHelper helper(Logger::Info, DLOG_CTX("default")); \
    helper.timing

#define dAssert(cond) ((!(cond)) ? loggerInstance()->writeAssert(__FILE__, __LINE__, Q_FUNC_INFO, #cond) : qt_noop())
#define dAssertX(cond, msg) ((!(cond)) ? loggerInstance()->writeAssert(__FILE__, __LINE__, Q_FUNC_INFO, msg) : qt_noop())

DLOG_CORE_END_NAMESPACE

#endif // DLOGGER_DEFINE_H
