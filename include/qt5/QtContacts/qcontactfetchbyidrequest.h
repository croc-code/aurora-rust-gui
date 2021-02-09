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

#ifndef QCONTACTFETCHBYIDREQUEST_H
#define QCONTACTFETCHBYIDREQUEST_H

#include <qcontactsglobal.h>
#include <qcontactabstractrequest.h>
#include <qcontact.h>
#include <qcontactfetchhint.h>

#include <QList>
#include <QStringList>

QT_BEGIN_NAMESPACE_CONTACTS

class QContactFetchByIdRequestPrivate;
class Q_CONTACTS_EXPORT QContactFetchByIdRequest : public QContactAbstractRequest
{
    Q_OBJECT

public:
    QContactFetchByIdRequest(QObject* parent = 0);
    ~QContactFetchByIdRequest();

    /* Selection, restriction and sorting */
    void setIds(const QList<QContactId>& ids);
    void setFetchHint(const QContactFetchHint& fetchHint);
    QList<QContactId> contactIds() const;
    QContactFetchHint fetchHint() const;

    /* Results */
    QList<QContact> contacts() const;
    QMap<int, QContactManager::Error> errorMap() const;

private:
    Q_DISABLE_COPY(QContactFetchByIdRequest)
    friend class QContactManagerEngine;
    Q_DECLARE_PRIVATE_D(d_ptr, QContactFetchByIdRequest)
};

QT_END_NAMESPACE_CONTACTS

#endif
