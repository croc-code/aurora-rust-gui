/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtVersit module of the Qt Toolkit.
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

#ifndef QVERSITCONTACTIMPORTER_P_H
#define QVERSITCONTACTIMPORTER_P_H

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

#include <qversitcontactimporter.h>
#include "qvcardrestorehandler_p.h"

#include <QList>
#include <QDateTime>
#include <QHash>
#include <QPair>
#include <QMap>
#include <QSet>

QT_BEGIN_NAMESPACE_CONTACTS
class QContact;
class QContactDetail;
class QContactOrganization;
QT_END_NAMESPACE_CONTACTS

QTCONTACTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE_VERSIT
class QVersitProperty;
class QVersitDocument;
class QVersitContactHandler;

class QVersitContactImporterPrivate
{
public:
    QVersitContactImporterPrivate(const QStringList& profiles = QStringList());
    ~QVersitContactImporterPrivate();

    bool importContact(const QVersitDocument& versitDocument, int contactIndex,
                       QContact* contact, QVersitContactImporter::Error* error);

private:
    void importProperty(const QVersitDocument& document, const QVersitProperty& property, int contactIndex, QContact* contact);
    bool createName(const QVersitProperty& property, QContact* contact, QList<QContactDetail>* updatedDetails);
    bool createPhone(const QVersitProperty& property, QContact* contact, QList<QContactDetail>* updatedDetails);
    bool createAddress(const QVersitProperty& property, QContact* contact, QList<QContactDetail>* updatedDetails);
    bool createOrganization(const QVersitProperty& property, QContact* contact, QList<QContactDetail>* updatedDetails);
    void setOrganizationNames(QContactOrganization& org, const QVersitProperty& property) const;
    void setOrganizationLogo(QContactOrganization& org, const QVersitProperty& property) const;
    bool createTimeStamp(const QVersitProperty& property, QContact* contact, QList<QContactDetail>* updatedDetails);
    bool createVersion(const QVersitProperty& property, QContact* contact, QList<QContactDetail>* updatedDetails);
    bool createAnniversary(const QVersitProperty& property, QContact* contact, QList<QContactDetail>* updatedDetails);
    bool createBirthday(const QVersitProperty& property, QContact* contact, QList<QContactDetail>* updatedDetails);
    bool createDisplaylabel(const QVersitProperty& property, QContact* contact, QList<QContactDetail>* updatedDetails);
    bool createNicknames(const QVersitProperty& property, QContact* contact, QList<QContactDetail>* updatedDetails);
    bool createTags(const QVersitProperty& property, QContact* contact, QList<QContactDetail>* updatedDetails);
    bool createOnlineAccount(const QVersitProperty& property, QContact* contact, QList<QContactDetail>* updatedDetails);
    bool createRingtone(const QVersitProperty& property, QContact* contact, QList<QContactDetail>* updatedDetails);
    bool createAvatar(const QVersitProperty& property, QContact* contact, QList<QContactDetail>* updatedDetails);
    bool createGeoLocation(const QVersitProperty& property, QContact* contact, QList<QContactDetail>* updatedDetails);
    bool createFamily(const QVersitProperty& property, QContact* contact, QList<QContactDetail>* updatedDetails);
    bool createFavorite(const QVersitProperty& property, QContact* contact, QList<QContactDetail>* updatedDetails);
    bool createNameValueDetail(const QVersitProperty& property, QContact* contact, QList<QContactDetail>* updatedDetails);
    bool createGender(const QVersitProperty& property, QContact* contact, QList<QContactDetail>* updatedDetails);
    bool createExtendedDetail(const QVersitProperty& property, QContact* contact, QList<QContactDetail>* updatedDetails);
    QList<int> extractContexts(const QVersitProperty& property) const;
    QStringList extractSubTypes(const QVersitProperty& property) const;
    QString takeFirst(QList<QString>& list) const;
    QDateTime parseDateTime(QString text, bool *justDate = 0) const;
    QString saveContentToFile(const QVersitProperty& property, const QByteArray& data) const;
    bool saveDataFromProperty(const QVersitProperty& property, QString* location, QByteArray* data) const;
    void saveDetailWithContext(QList<QContactDetail>* updatedDetails, QContactDetail detail, const QList<int>& contexts);

public: // Data
    QList<QContact> mContacts;
    QMap<int, QVersitContactImporter::Error> mErrors;
    QVersitContactImporterPropertyHandler* mPropertyHandler;
    QVersitContactImporterPropertyHandlerV2* mPropertyHandler2;
    QList<QVersitContactHandler*> mPluginPropertyHandlers;
    int mPropertyHandlerVersion;
    QVersitDefaultResourceHandler* mDefaultResourceHandler;
    QVersitResourceHandler* mResourceHandler;
    QVCardRestoreHandler mRestoreHandler;

    QHash<QString, QPair<QContactDetail::DetailType, int> > mDetailMappings;
    QMap< QPair<QContactDetail::DetailType, int>, QString> mSubTypeMappings;
    QHash< int ,QString> mContextMappings;
};

QT_END_NAMESPACE_VERSIT

#endif // QVERSITCONTACTIMPORTER_P_H
