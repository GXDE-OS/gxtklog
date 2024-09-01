// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "dloghelper.h"
#include "Logger.h"

#include <QCoreApplication>
#include <QElapsedTimer>
#include <private/qobject_p.h>

#include <iostream>

DLOG_CORE_BEGIN_NAMESPACE

class GLogHelperPrivate : public QObjectPrivate
{
public:
    // Functions.
    explicit GLogHelperPrivate(int version = QObjectPrivateVersion)
        : QObjectPrivate(version)
    {
    }
    ~GLogHelperPrivate()
    {
    }

    void setContext(const QMessageLogContext &ctx)
    {
        file = ctx.file;
        line = ctx.line;
        function = ctx.function;
        category = ctx.category;
    }
    void setLevel(Logger::LogLevel lvl)
    {
        level = lvl;
    }

    const char *file = nullptr;
    const char *function = nullptr;
    const char *category = nullptr;
    int line = 0;
    Logger::LogLevel level = Logger::LogLevel::Debug;
};

GLogHelper::GLogHelper(Logger::LogLevel level, const QMessageLogContext &context, QObject *parent)
    : QObject(*new GLogHelperPrivate, parent)
{
    d_func()->setContext(context);
    d_func()->setLevel(level);
}

GLogHelper::~GLogHelper()
{
}

void GLogHelper::write(const char *msg, ...)
{
    QString message;
    va_list va;
    va_start(va, msg);
    message = QString::vasprintf(msg, va);
    va_end(va);

    write(message);
}

void GLogHelper::write(const QString &msg)
{
    Q_D(GLogHelper);
    Logger::globalInstance()->write(d->level, d->file, d->line,
                                    d->function, d->category, msg);
}

QDebug GLogHelper::write()
{
    Q_D(GLogHelper);
    return Logger::globalInstance()->write(d->level, d->file, d->line,
                                           d->function, d->category);
}

void GLogHelper::timing(const QString &msg, QObject *context /* = nullptr*/)
{
    if (!context)
        context = this;

    QElapsedTimer *elapsedTimer = new QElapsedTimer;
    elapsedTimer->start();
    QObject::connect(context, &QObject::destroyed, [elapsedTimer, msg, this]()
                     {
        QString message;
        message = msg + (QLatin1String(" finished in "));

        qint64 elapsed = elapsedTimer->elapsed();
        delete elapsedTimer;

        if (elapsed >= 10000)
            message += QString::number(elapsed / 1000) + QLatin1String("s.");
        else
            message += QString::number(elapsed) + QLatin1String("ms.");

        write(message); });
}

Logger::LogLevel GLogHelper::levelFromQtMsgType(QtMsgType mt)
{
    Logger::LogLevel level;
    switch (mt)
    {
    case QtDebugMsg:
        level = Logger::Debug;
        break;
#if QT_VERSION >= 0x050500
    case QtInfoMsg:
        level = Logger::Info;
        break;
#endif
    case QtWarningMsg:
        level = Logger::Warning;
        break;
    case QtCriticalMsg:
        level = Logger::Error;
        break;
    case QtFatalMsg:
        level = Logger::Fatal;
        break;
    }
    return level;
}

QtMsgType GLogHelper::qtMsgTypeFromLogLevel(Logger::LogLevel lvl)
{
    QtMsgType mt;
    switch (lvl)
    {
    case Logger::Debug:
        mt = QtDebugMsg;
        break;
#if QT_VERSION >= 0x050500
    case Logger::Info:
        mt = QtInfoMsg;
        break;
#endif
    case Logger::Warning:
        mt = QtWarningMsg;
        break;
    case Logger::Error:
        mt = QtCriticalMsg;
        break;
    case Logger::Fatal:
        mt = QtFatalMsg;
        break;
    default:
        mt = QtWarningMsg;
    }
    return mt;
}

DLOG_CORE_END_NAMESPACE
