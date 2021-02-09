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

#ifndef QORGANIZERITEMSORTORDER_H
#define QORGANIZERITEMSORTORDER_H

#include <qorganizeritemdetail.h>
#include <QtCore/qlist.h>
#include <QtCore/qshareddata.h>
#include <QtCore/qstring.h>

QT_BEGIN_NAMESPACE_ORGANIZER

class QOrganizerItemSortOrderPrivate;
class Q_ORGANIZER_EXPORT QOrganizerItemSortOrder
{
public:
    QOrganizerItemSortOrder();
    ~QOrganizerItemSortOrder();

    QOrganizerItemSortOrder(const QOrganizerItemSortOrder &other);
    QOrganizerItemSortOrder &operator=(const QOrganizerItemSortOrder &other);

    enum BlankPolicy {
        BlanksFirst,
        BlanksLast
    };

    // mutators
    void setDetail(QOrganizerItemDetail::DetailType detailType, int field);
    void setBlankPolicy(BlankPolicy blankPolicy);
    void setDirection(Qt::SortOrder direction);
    void setCaseSensitivity(Qt::CaseSensitivity sensitivity);

    // accessors
    QOrganizerItemDetail::DetailType detailType() const;
    int detailField() const;
    BlankPolicy blankPolicy() const;
    Qt::SortOrder direction() const;
    Qt::CaseSensitivity caseSensitivity() const;

    bool isValid() const;

    bool operator==(const QOrganizerItemSortOrder &other) const;
    bool operator!=(const QOrganizerItemSortOrder &other) const { return !operator==(other); }

    // convenience cast
    operator QList<QOrganizerItemSortOrder>() const { return QList<QOrganizerItemSortOrder>() << *this; }

private:
    QSharedDataPointer<QOrganizerItemSortOrderPrivate> d;
};

#ifndef QT_NO_DATASTREAM
Q_ORGANIZER_EXPORT QDataStream &operator<<(QDataStream &out, const QOrganizerItemSortOrder &sortOrder);
Q_ORGANIZER_EXPORT QDataStream &operator>>(QDataStream &in, QOrganizerItemSortOrder &sortOrder);
#endif // QT_NO_DATASTREAM

#ifndef QT_NO_DEBUG_STREAM
Q_ORGANIZER_EXPORT QDebug operator<<(QDebug dbg, const QOrganizerItemSortOrder &sortOrder);
#endif // QT_NO_DEBUG_STREAM

QT_END_NAMESPACE_ORGANIZER

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO(QTORGANIZER_PREPEND_NAMESPACE(QOrganizerItemSortOrder), Q_MOVABLE_TYPE);
QT_END_NAMESPACE

#endif // QORGANIZERITEMSORTORDER_H
