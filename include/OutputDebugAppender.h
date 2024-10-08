/*
  Copyright (c) 2010 Karl-Heinz Reichel (khreichel at googlemail dot com)

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License version 2.1
  as published by the Free Software Foundation and appearing in the file
  LICENSE.LGPL included in the packaging of this file.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.
*/

#ifndef OUTPUTDEBUGAPPENDER_H
#define OUTPUTDEBUGAPPENDER_H

#include "dlog_global.h"
#include "AbstractStringAppender.h"

DLOG_CORE_BEGIN_NAMESPACE

class LIBDLOG_SHARED_EXPORT OutputDebugAppender : public AbstractStringAppender
{
protected:
  virtual void append(const QDateTime &time, Logger::LogLevel level, const char *file, int line,
                      const char *func, const QString &category, const QString &msg);
};

DLOG_CORE_END_NAMESPACE

#endif // OUTPUTDEBUGAPPENDER_H
