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


#ifndef QCONTACTACTIONTARGET_H
#define QCONTACTACTIONTARGET_H

#include <qcontactsglobal.h>
#include "qcontact.h"
#include "qcontactdetail.h"

#include <QDebug>
#include <QList>
#include <QString>
#include <QSharedDataPointer>

QT_BEGIN_NAMESPACE_CONTACTS

// MSVC needs the function declared before the friend declaration
class QContactActionTarget;
Q_CONTACTS_EXPORT uint qHash(const QContactActionTarget& key);
#ifndef QT_NO_DATASTREAM
Q_CONTACTS_EXPORT QDataStream& operator<<(QDataStream& out, const QContactActionTarget& target);
Q_CONTACTS_EXPORT QDataStream& operator>>(QDataStream& in, QContactActionTarget& target);
#endif
#ifndef QT_NO_DEBUG_STREAM
Q_CONTACTS_EXPORT QDebug& operator<<(QDebug dbg, const QContactActionTarget& target);
#endif

class QContactActionTargetPrivate;
class Q_CONTACTS_EXPORT QContactActionTarget
{
public:
    explicit QContactActionTarget(const QContact& contact = QContact(), const QList<QContactDetail>& details = QList<QContactDetail>());
    QContactActionTarget(const QContact& contact, const QContactDetail& detail);

    QContactActionTarget(const QContactActionTarget& other);

    QContactActionTarget& operator=(const QContactActionTarget& other);
    ~QContactActionTarget();

    enum Type {
        Invalid, // no contact
        WholeContact, // no details
        SingleDetail, // a single detail
        MultipleDetails,
    };

    Type type() const; // No setter
    bool isValid() const;
    bool operator==(const QContactActionTarget& other) const;
    bool operator!=(const QContactActionTarget& other) const;

    void setContact(const QContact& contact);
    void setDetails(const QList<QContactDetail>& details);

    QContact contact() const;
    QList<QContactDetail> details() const;

private:
#ifndef QT_NO_DATASTREAM
    Q_CONTACTS_EXPORT friend QDataStream& operator<<(QDataStream& out, const QContactActionTarget& target);
    Q_CONTACTS_EXPORT friend QDataStream& operator>>(QDataStream& in, QContactActionTarget& target);
#endif
    QSharedDataPointer<QContactActionTargetPrivate> d;
};

QT_END_NAMESPACE_CONTACTS

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO(QTCONTACTS_PREPEND_NAMESPACE(QContactActionTarget), Q_MOVABLE_TYPE);
QT_END_NAMESPACE

#endif
