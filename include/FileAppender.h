/*
  Copyright (c) 2010 Boris Moiseev (cyberbobs at gmail dot com)

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License version 2.1
  as published by the Free Software Foundation and appearing in the file
  LICENSE.LGPL included in the packaging of this file.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.
*/
#ifndef FILEAPPENDER_H
#define FILEAPPENDER_H

// Logger
#include "dlog_global.h"
#include "AbstractStringAppender.h"

// Qt
#include <QFile>
#include <QTextStream>

DLOG_CORE_BEGIN_NAMESPACE

class LIBDLOG_SHARED_EXPORT FileAppender : public AbstractStringAppender
{
public:
    FileAppender(const QString &fileName = QString());
    ~FileAppender();

    QString fileName() const;
    void setFileName(const QString &s);

    qint64 size() const;

protected:
    virtual void append(const QDateTime &time, Logger::LogLevel level, const char *file, int line,
                        const char *func, const QString &category, const QString &msg);
    bool openFile();
    void closeFile();

private:
    QFile m_logFile;
    QTextStream m_logStream;
    mutable QMutex m_logFileMutex;
};

DLOG_CORE_END_NAMESPACE

#endif // FILEAPPENDER_H
