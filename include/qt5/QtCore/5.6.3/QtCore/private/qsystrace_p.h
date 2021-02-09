/****************************************************************************
**
** Copyright (C) 2014 Jolla Ltd, author: <robin.burchell@jollamobile.com>
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSYSTRACE_P_H
#define QSYSTRACE_P_H

#include <qglobal.h>

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

QT_BEGIN_NAMESPACE

namespace QSystrace
{
    void Q_CORE_EXPORT begin(const char *module, const char *tracepoint, const char *message, ...);
    void Q_CORE_EXPORT end(const char *module, const char *tracepoint, const char *message, ...);
    void Q_CORE_EXPORT counter(const char *module, const char *tracepoint, const char *message, ...);
};

// simple RAII wrapper we can use elsewhere in the codebase. must be inside Qt
// so QT_NO_DEBUG (& our feature macro) can easily disable the functionality
// while not littering the codebase with defines
struct QSystraceEvent
{
    QSystraceEvent(const char *module, const char *tracepoint)
        : m_module(module)
        , m_tracepoint(tracepoint)
    {
        QSystrace::begin(m_module, m_tracepoint, "");
    }

    ~QSystraceEvent()
    {
        QSystrace::end(m_module, m_tracepoint, "");
    }

private:
    const char *m_module;
    const char *m_tracepoint;
};

QT_END_NAMESPACE

#endif // QSYSTRACE_P_H
