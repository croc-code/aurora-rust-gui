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


#ifndef QCONTACTMANAGERENGINE_H
#define QCONTACTMANAGERENGINE_H

#include <QSharedData>
#include <QMap>
#include <QList>
#include <QString>
#include <QDateTime>
#include <QVariant>
#include <QObject>

#include "qcontact.h"
#include "qcontactmanager.h"
#include "qcontactabstractrequest.h"
#include "qcontactrequests.h"
#include "qcontactfetchhint.h"

QT_BEGIN_NAMESPACE_CONTACTS

class QContactFilter;
class QContactSortOrder;

class Q_CONTACTS_EXPORT QContactManagerEngine : public QObject
{
    Q_OBJECT

public:
    QContactManagerEngine() {}

    /* URI reporting */
    virtual QString managerName() const = 0;                       // e.g. "memory"
    virtual QMap<QString, QString> managerParameters() const;  // e.g. "filename=private.db"
    virtual int managerVersion() const = 0;

    /* Default and only implementation of this */
    QString managerUri() const;

    /* Filtering */
    virtual QList<QContactId> contactIds(const QContactFilter &filter, const QList<QContactSortOrder> &sortOrders, QContactManager::Error *error) const;
    virtual QList<QContact> contacts(const QContactFilter &filter, const QList<QContactSortOrder>& sortOrders, const QContactFetchHint &fetchHint, QContactManager::Error *error) const;
    virtual QList<QContact> contacts(const QList<QContactId> &contactIds, const QContactFetchHint& fetchHint, QMap<int, QContactManager::Error> *errorMap, QContactManager::Error *error) const;
    virtual QContact contact(const QContactId &contactId, const QContactFetchHint &fetchHint, QContactManager::Error *error) const;

    virtual bool saveContact(QContact *contact, QContactManager::Error *error);
    virtual bool removeContact(const QContactId &contactId, QContactManager::Error *error);
    virtual bool saveRelationship(QContactRelationship *relationship, QContactManager::Error *error);
    virtual bool removeRelationship(const QContactRelationship &relationship, QContactManager::Error *error);

    virtual bool saveContacts(QList<QContact> *contacts, QMap<int, QContactManager::Error> *errorMap, QContactManager::Error *error);
    virtual bool saveContacts(QList<QContact> *contacts,  const QList<QContactDetail::DetailType> &typeMask, QMap<int, QContactManager::Error> *errorMap, QContactManager::Error *error);
    virtual bool removeContacts(const QList<QContactId> &contactIds, QMap<int, QContactManager::Error> *errorMap, QContactManager::Error *error);

    /* "Self" contact id (MyCard) */
    virtual bool setSelfContactId(const QContactId &contactId, QContactManager::Error *error);
    virtual QContactId selfContactId(QContactManager::Error *error) const;

    /* Relationships between contacts */
    virtual QList<QContactRelationship> relationships(const QString &relationshipType, const QContact& participant, QContactRelationship::Role role, QContactManager::Error *error) const;
    virtual bool saveRelationships(QList<QContactRelationship> *relationships, QMap<int, QContactManager::Error>* errorMap, QContactManager::Error *error);
    virtual bool removeRelationships(const QList<QContactRelationship> &relationships, QMap<int, QContactManager::Error> *errorMap, QContactManager::Error *error);

    /* Validation for saving */
    virtual bool validateContact(const QContact &contact, QContactManager::Error *error) const;

    /* Asynchronous Request Support */
    virtual void requestDestroyed(QContactAbstractRequest *req);
    virtual bool startRequest(QContactAbstractRequest *req);
    virtual bool cancelRequest(QContactAbstractRequest *req);
    virtual bool waitForRequestFinished(QContactAbstractRequest *req, int msecs);

    /* Capabilities reporting */
    virtual bool isRelationshipTypeSupported(const QString &relationshipType, QContactType::TypeValues contactType) const;
    virtual bool isFilterSupported(const QContactFilter &filter) const;
    virtual QList<QVariant::Type> supportedDataTypes() const;
    virtual QList<QContactType::TypeValues> supportedContactTypes() const;
    virtual QList<QContactDetail::DetailType> supportedContactDetailTypes() const;

Q_SIGNALS:
    void dataChanged();
    void contactsAdded(const QList<QContactId> &contactIds);
    void contactsChanged(const QList<QContactId> &contactIds);
    void contactsRemoved(const QList<QContactId> &contactIds);
    void relationshipsAdded(const QList<QContactId> &affectedContactIds);
    void relationshipsRemoved(const QList<QContactId> &affectedContactIds);
    void selfContactIdChanged(const QContactId &oldId, const QContactId &newId);

public:
    // Async update functions
    static void updateRequestState(QContactAbstractRequest *req, QContactAbstractRequest::State state);

    static void updateContactIdFetchRequest(QContactIdFetchRequest *req, const QList<QContactId>& result, QContactManager::Error error, QContactAbstractRequest::State);
    static void updateContactFetchRequest(QContactFetchRequest *req, const QList<QContact> &result, QContactManager::Error error, QContactAbstractRequest::State);
    static void updateContactFetchByIdRequest(QContactFetchByIdRequest *req, const QList<QContact>& result, QContactManager::Error error, const QMap<int, QContactManager::Error> &errorMap, QContactAbstractRequest::State);
    static void updateContactRemoveRequest(QContactRemoveRequest *req, QContactManager::Error error, const QMap<int, QContactManager::Error> &errorMap, QContactAbstractRequest::State);
    static void updateContactSaveRequest(QContactSaveRequest *req, const QList<QContact> &result, QContactManager::Error error, const QMap<int, QContactManager::Error> &errorMap, QContactAbstractRequest::State);
    static void updateRelationshipSaveRequest(QContactRelationshipSaveRequest *req, const QList<QContactRelationship> &result, QContactManager::Error error, const QMap<int, QContactManager::Error> &errorMap, QContactAbstractRequest::State);
    static void updateRelationshipRemoveRequest(QContactRelationshipRemoveRequest *req, QContactManager::Error error, const QMap<int, QContactManager::Error> &errorMap, QContactAbstractRequest::State);
    static void updateRelationshipFetchRequest(QContactRelationshipFetchRequest *req, const QList<QContactRelationship> &result, QContactManager::Error error, QContactAbstractRequest::State);

    // Other protected area update functions
    static void setDetailAccessConstraints(QContactDetail *detail, QContactDetail::AccessConstraints constraints);
    static void setContactRelationships(QContact *contact, const QList<QContactRelationship> &relationships);

    /* Helper functions */
    static const QContactEngineId *engineId(const QContactId &contactId);
    static int compareContact(const QContact &a, const QContact &b, const QList<QContactSortOrder> &sortOrders);
    static void addSorted(QList<QContact>* sorted, const QContact &toAdd, const QList<QContactSortOrder> &sortOrders);
    static int compareVariant(const QVariant &first, const QVariant &second, Qt::CaseSensitivity sensitivity);
    static bool testFilter(const QContactFilter& filter, const QContact &contact);
    static QList<QContactId> sortContacts(const QList<QContact> &contacts, const QList<QContactSortOrder> &sortOrders);

    static QContactFilter canonicalizedFilter(const QContactFilter &filter);


private:
    /* QContactChangeSet is a utility class used to emit the appropriate signals */
    friend class QContactChangeSet;
};

QT_END_NAMESPACE_CONTACTS

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(QtContacts::QContactManagerEngine, "org.qt-project.Qt.QContactManagerEngine")
QT_END_NAMESPACE

#endif
