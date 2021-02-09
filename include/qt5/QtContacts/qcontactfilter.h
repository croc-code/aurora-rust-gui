/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtContacts module of the Qt Toolkit.
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

#ifndef QCONTACTFILTER_H
#define QCONTACTFILTER_H

#include <QVariant>
#include <QList>
#include <QDateTime>
#include <QSharedData>

#include <qcontactsglobal.h>

QT_BEGIN_NAMESPACE_CONTACTS

/* Manual Q_DECLARE_CONTACTFILTER_PRIVATE macro */

#define Q_DECLARE_CONTACTFILTER_PRIVATE(Class) \
    inline Class##Private* d_func(); \
    inline const Class##Private* d_func() const; \
    friend class Class##Private;

class QContactFilterPrivate;

// MSVC needs the function declared before the friend declaration
class QContactFilter;
#ifndef QT_NO_DATASTREAM
Q_CONTACTS_EXPORT QDataStream& operator<<(QDataStream& out, const QContactFilter& filter);
Q_CONTACTS_EXPORT QDataStream& operator>>(QDataStream& in, QContactFilter& filter);
#endif

class Q_CONTACTS_EXPORT QContactFilter
{
public:
    QContactFilter();
    ~QContactFilter();
    QContactFilter(const QContactFilter& other);
    QContactFilter& operator=(const QContactFilter& other);

    enum FilterType {
        InvalidFilter,
        ContactDetailFilter,
        ContactDetailRangeFilter,
        ChangeLogFilter,
        ActionFilter,
        RelationshipFilter,
        IntersectionFilter,
        UnionFilter,
        IdFilter,
        DefaultFilter
    };

    FilterType type() const;

    enum MatchFlag {
        MatchExactly = 0x0000,        // 0
        MatchContains = 0x0001,       // 1
        MatchStartsWith = 0x0002,     // 2
        MatchEndsWith = 0x0004,       // 4
        MatchFixedString = 0x0008,      // 8
        MatchCaseSensitive = 0x0010,    // 16
        MatchPhoneNumber = 0x400,    //1024
        MatchKeypadCollation = 0x800 //2048
    };
    Q_DECLARE_FLAGS(MatchFlags, MatchFlag)

    bool operator==(const QContactFilter& other) const;
    bool operator!=(const QContactFilter& other) const {return !operator==(other);}

protected:
    explicit QContactFilter(QContactFilterPrivate* d);

protected:
    friend class QContactFilterPrivate;
#ifndef QT_NO_DATASTREAM
    Q_CONTACTS_EXPORT friend QDataStream& operator<<(QDataStream& out, const QContactFilter& filter);
    Q_CONTACTS_EXPORT friend QDataStream& operator>>(QDataStream& in, QContactFilter& filter);
#endif
#ifndef QT_NO_DEBUG_STREAM
    Q_CONTACTS_EXPORT friend QDebug operator<<(QDebug dbg, const QContactFilter& filter);
#endif
    QSharedDataPointer<QContactFilterPrivate> d_ptr;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QContactFilter::MatchFlags)

const Q_CONTACTS_EXPORT QContactFilter operator&(const QContactFilter& left, const QContactFilter& right);
const Q_CONTACTS_EXPORT QContactFilter operator|(const QContactFilter& left, const QContactFilter& right);

QT_END_NAMESPACE_CONTACTS

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO(QTCONTACTS_PREPEND_NAMESPACE(QContactFilter), Q_MOVABLE_TYPE);
QT_END_NAMESPACE

#endif
