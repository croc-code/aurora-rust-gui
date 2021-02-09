/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtOrganizer module of the Qt Toolkit.
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

#ifndef QORGANIZERITEMID_H
#define QORGANIZERITEMID_H

#include <qorganizerglobal.h>

#ifndef QT_NO_DEBUG_STREAM
#include <QtCore/qdebug.h>
#endif
#include <QtCore/qshareddata.h>

#ifndef QT_NO_DATASTREAM
QT_BEGIN_NAMESPACE
class QDataStream;
QT_END_NAMESPACE
#endif

QT_BEGIN_NAMESPACE_ORGANIZER

// MSVC needs the function declared before the friend declaration
class QOrganizerItemId;
class QOrganizerItemEngineId;
Q_ORGANIZER_EXPORT uint qHash(const QOrganizerItemId &key);

#ifndef QT_NO_DATASTREAM
Q_ORGANIZER_EXPORT QDataStream &operator<<(QDataStream &out, const QOrganizerItemId &itemId);
Q_ORGANIZER_EXPORT QDataStream &operator>>(QDataStream &in, QOrganizerItemId &itemId);
#endif

#ifndef QT_NO_DEBUG_STREAM
Q_ORGANIZER_EXPORT QDebug operator<<(QDebug dbg, const QOrganizerItemId &itemId);
#endif

class QOrganizerManagerEngine;

class Q_ORGANIZER_EXPORT QOrganizerItemId
{
public:
    QOrganizerItemId();
    QOrganizerItemId(const QOrganizerItemId &other);
    explicit QOrganizerItemId(QOrganizerItemEngineId *engineId);
    ~QOrganizerItemId();

    QOrganizerItemId &operator=(const QOrganizerItemId &other);

    bool operator==(const QOrganizerItemId &other) const;
    bool operator!=(const QOrganizerItemId &other) const;
    bool operator<(const QOrganizerItemId &other) const;

    bool isNull() const;

    QString managerUri() const;

    QString toString() const;
    static QOrganizerItemId fromString(const QString &idString);

private:
    QSharedDataPointer<QOrganizerItemEngineId> d;

#ifndef QT_NO_DEBUG_STREAM
    friend Q_ORGANIZER_EXPORT QDebug operator<<(QDebug dbg, const QOrganizerItemId &itemId);
#endif
    friend Q_ORGANIZER_EXPORT uint qHash(const QOrganizerItemId &key);
    friend class QOrganizerManagerEngine;
};

QT_END_NAMESPACE_ORGANIZER

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO(QTORGANIZER_PREPEND_NAMESPACE(QOrganizerItemId), Q_MOVABLE_TYPE);
QT_END_NAMESPACE

Q_DECLARE_METATYPE(QTORGANIZER_PREPEND_NAMESPACE(QOrganizerItemId));

#endif // QORGANIZERITEMID_H
