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

#ifndef QCONTACTID_H
#define QCONTACTID_H

#include <QString>
#include <QSharedDataPointer>

#include <qcontactsglobal.h>

#ifndef QT_NO_DEBUG_STREAM
#include <QtCore/qdebug.h>
#endif
#include <QtCore/qshareddata.h>


QT_BEGIN_NAMESPACE
class QDataStream;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE_CONTACTS

class QContactId;
Q_CONTACTS_EXPORT uint qHash(const QContactId &key);

class QContactEngineId;
class QContactManagerEngine;

class Q_CONTACTS_EXPORT QContactId
{
public:
    QContactId();
    ~QContactId();

    QContactId(const QContactId &other);
    QContactId& operator=(const QContactId &other);
    explicit QContactId(QContactEngineId *engineId);

    bool operator==(const QContactId &other) const;
    bool operator!=(const QContactId &other) const;
    bool operator<(const QContactId &other) const;

    QString managerUri() const;
    bool isNull() const;
    QString toString() const;
    static QContactId fromString(const QString &idString);

private:
    static bool parseIdString(const QString &idString, QString* managerName, QMap<QString, QString> *params, QString *engineIdString);
    static QString escapeUriParam(const QString &param);

    QSharedDataPointer<QContactEngineId> d;
    friend class QContactManager;
    friend class QContactManagerEngine;
    Q_CONTACTS_EXPORT friend uint qHash(const QContactId &key);

#ifndef QT_NO_DEBUG_STREAM
    Q_CONTACTS_EXPORT friend QDebug operator<<(QDebug dbg, const QContactId &id);
#endif
};

#ifndef QT_NO_DEBUG_STREAM
Q_CONTACTS_EXPORT QDebug operator<<(QDebug dbg, const QContactId &id);
#endif
#ifndef QT_NO_DATASTREAM
Q_CONTACTS_EXPORT QDataStream& operator<<(QDataStream &out, const QContactId &id);
Q_CONTACTS_EXPORT QDataStream& operator>>(QDataStream &in, QContactId &id);
#endif

QT_END_NAMESPACE_CONTACTS

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO(QTCONTACTS_PREPEND_NAMESPACE(QContactId), Q_MOVABLE_TYPE);
QT_END_NAMESPACE

Q_DECLARE_METATYPE(QTCONTACTS_PREPEND_NAMESPACE(QContactId))


#endif

