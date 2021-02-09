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

#ifndef QCONTACTREQUESTS_P_H
#define QCONTACTREQUESTS_P_H

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

#include <qcontactabstractrequest_p.h>
#include <qcontactfilter.h>
#include <qcontactrelationshipfilter.h>
#include <qcontactsortorder.h>
#include <qcontact.h>
#include <qcontactdetail.h>

#include <QStringList>
#include <QList>

QT_BEGIN_NAMESPACE_CONTACTS

class QContactSaveRequestPrivate : public QContactAbstractRequestPrivate
{
public:
    QContactSaveRequestPrivate()
        : QContactAbstractRequestPrivate(),
          m_storageLocation(QContactAbstractRequest::UserDataStorage)
    {
    }

    ~QContactSaveRequestPrivate()
    {
    }

    QContactAbstractRequest::RequestType type() const
    {
        return QContactAbstractRequest::ContactSaveRequest;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug& dbg) const
    {
        dbg.nospace() << "QContactSaveRequest(";
        dbg.nospace() << "contacts=" << m_contacts << ","
                      << "typeMask=" << m_typeMask << ","
                      << "errorMap=" << m_errors << ","
                      << "storageLocation=" << m_storageLocation;
        dbg.nospace() << ")";
        return dbg.maybeSpace();
    }
#endif

    QList<QContact> m_contacts;
    QMap<int, QContactManager::Error> m_errors;
    QList<QContactDetail::DetailType> m_typeMask;
    QContactAbstractRequest::StorageLocation m_storageLocation;
};

class QContactFetchRequestPrivate : public QContactAbstractRequestPrivate
{
public:
    QContactFetchRequestPrivate()
        : QContactAbstractRequestPrivate(),
          m_storageLocations(QContactAbstractRequest::UserDataStorage)
    {
    }

    ~QContactFetchRequestPrivate()
    {
    }

    QContactAbstractRequest::RequestType type() const
    {
        return QContactAbstractRequest::ContactFetchRequest;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug& dbg) const
    {
        dbg.nospace() << "QContactFetchRequest("
                      << "filter=" << m_filter << ","
                      << "sorting=" << m_sorting << ","
                      << "fetchHint=" << m_fetchHint << ","
                      << "storageLocations=" << m_storageLocations;
        dbg.nospace() << ")";
        return dbg.maybeSpace();
    }
#endif

    QContactFilter m_filter;
    QList<QContactSortOrder> m_sorting;
    QContactFetchHint m_fetchHint;

    QList<QContact> m_contacts;
    QContactAbstractRequest::StorageLocations m_storageLocations;
};

class QContactFetchByIdRequestPrivate : public QContactAbstractRequestPrivate
{
public:
    QContactFetchByIdRequestPrivate()
        : QContactAbstractRequestPrivate()
    {
    }

    ~QContactFetchByIdRequestPrivate()
    {
    }

    QContactAbstractRequest::RequestType type() const
    {
        return QContactAbstractRequest::ContactFetchByIdRequest;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug& dbg) const
    {
        dbg.nospace() << "QContactFetchByIdRequest(\n"
                      << "* contactIds=" << m_contactIds << ",\n"
                      << "* contacts=" << m_contacts << ",\n"
                      << "* fetchHint=" << m_fetchHint << ",\n"
                      << "* errorMap=" << m_errors;
        dbg.nospace() << "\n)";
        return dbg.maybeSpace();
    }
#endif

    QList<QContactId> m_contactIds;
    QContactFetchHint m_fetchHint;

    QList<QContact> m_contacts;
    QMap<int, QContactManager::Error> m_errors;
};

class QContactRemoveRequestPrivate : public QContactAbstractRequestPrivate
{
public:
    QContactRemoveRequestPrivate()
        : QContactAbstractRequestPrivate()
    {
    }

    ~QContactRemoveRequestPrivate()
    {
    }

    QContactAbstractRequest::RequestType type() const
    {
        return QContactAbstractRequest::ContactRemoveRequest;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug& dbg) const
    {
        dbg.nospace() << "QContactRemoveRequest("
                      << "contactIds=" << m_contactIds << ","
                      << "errorMap=" << m_errors;
        dbg.nospace() << ")";
        return dbg.maybeSpace();
    }
#endif

    QList<QContactId> m_contactIds;
    QMap<int, QContactManager::Error> m_errors;
};

class QContactIdFetchRequestPrivate : public QContactAbstractRequestPrivate
{
public:
    QContactIdFetchRequestPrivate()
        : QContactAbstractRequestPrivate(),
          m_storageLocations(QContactAbstractRequest::UserDataStorage)
    {
    }

    ~QContactIdFetchRequestPrivate()
    {
    }

    QContactAbstractRequest::RequestType type() const
    {
        return QContactAbstractRequest::ContactIdFetchRequest;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug& dbg) const
    {
        dbg.nospace() << "QContactIdFetchRequest("
                      << "filter=" << m_filter << ","
                      << "sorting=" << m_sorting << ","
                      << "ids=" << m_ids << ","
                      << "storageLocations=" << m_storageLocations;
        dbg.nospace() << ")";
        return dbg.maybeSpace();
    }
#endif

    QContactFilter m_filter;
    QList<QContactSortOrder> m_sorting;

    QList<QContactId> m_ids;
    QContactAbstractRequest::StorageLocations m_storageLocations;
};

class QContactRelationshipFetchRequestPrivate : public QContactAbstractRequestPrivate
{
public:
    QContactRelationshipFetchRequestPrivate()
        : QContactAbstractRequestPrivate()
    {
    }

    ~QContactRelationshipFetchRequestPrivate()
    {
    }

    QContactAbstractRequest::RequestType type() const
    {
        return QContactAbstractRequest::RelationshipFetchRequest;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug& dbg) const
    {
        dbg.nospace() << "QContactRelationshipFetchRequest("
                      << "first=" << m_first << ","
                      << "second=" << m_second << ","
                      << "relationshipType=" << m_relationshipType << ","
                      << "relationships=" << m_relationships;
        dbg.nospace() << ")";
        return dbg.maybeSpace();
    }
#endif

    // selection criteria
    QContact m_first;
    QContact m_second;
    QString m_relationshipType;

    // results
    QList<QContactRelationship> m_relationships;
};

class QContactRelationshipSaveRequestPrivate : public QContactAbstractRequestPrivate
{
public:
    QContactRelationshipSaveRequestPrivate()
        : QContactAbstractRequestPrivate()
    {
    }

    ~QContactRelationshipSaveRequestPrivate()
    {
    }

    QContactAbstractRequest::RequestType type() const
    {
        return QContactAbstractRequest::RelationshipSaveRequest;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug& dbg) const
    {
        dbg.nospace() << "QContactRelationshipSaveRequest("
                      << "relationships=" << m_relationships << ","
                      << "errorMap=" << m_errors;
        dbg.nospace() << ")";
        return dbg.maybeSpace();
    }
#endif

    QList<QContactRelationship> m_relationships;
    QMap<int, QContactManager::Error> m_errors;
};

class QContactRelationshipRemoveRequestPrivate : public QContactAbstractRequestPrivate
{
public:
    QContactRelationshipRemoveRequestPrivate()
        : QContactAbstractRequestPrivate()
    {
    }

    ~QContactRelationshipRemoveRequestPrivate()
    {
    }

    QContactAbstractRequest::RequestType type() const
    {
        return QContactAbstractRequest::RelationshipRemoveRequest;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug& dbg) const
    {
        dbg.nospace() << "QContactRelationshipRemoveRequest("
                      << "relationships=" << m_relationships << ","
                      << "errorMap=" << m_errors;
        dbg.nospace() << ")";
        return dbg.maybeSpace();
    }
#endif

    QList<QContactRelationship> m_relationships;
    QMap<int, QContactManager::Error> m_errors;
};

QT_END_NAMESPACE_CONTACTS

#endif
