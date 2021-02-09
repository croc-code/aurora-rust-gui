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

#ifndef QVERSITCONTACTEXPORTER_P_H
#define QVERSITCONTACTEXPORTER_P_H

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

#include <qversitdocument.h>
#include <qversitproperty.h>

#include <QHash>
#include <QObject>

QT_BEGIN_NAMESPACE_CONTACTS
class QContact;
class QContactDetail;
QT_END_NAMESPACE_CONTACTS

QTCONTACTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE_VERSIT
class QVersitContactHandler;

class QVersitContactExporterPrivate
{
public:
    QVersitContactExporterPrivate(const QStringList& profiles = QStringList());
    ~QVersitContactExporterPrivate();

    void exportContact(const QContact& contact, QVersitDocument& versitDocument);

protected:
    static void ensureDocumentContainsName(QVersitDocument* document);
    void encodeName(const QContactDetail& detail,
            const QVersitDocument& document,
            QList<QVersitProperty>* removedProperties,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);
    void encodePhoneNumber(const QContactDetail& detail,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);
    void encodeEmail(const QContactDetail& detail,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);
    void encodeAddress(const QContactDetail& detail,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);
    void encodeUrl(const QContactDetail& detail,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);
    void encodeUid(const QContactDetail& detail,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);
    void encodeRev(const QContactDetail& detail,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);
    void encodeVersion(const QContactDetail &detail,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);
    void encodeBirthDay(const QContactDetail& detail,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);
    void encodeNote(const QContactDetail& detail,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);
    void encodeGeoLocation(
            const QContactDetail& detail,
            QList<QVersitProperty>* generatedProperties,
            QSet<int>* processedFields);
    void encodeOrganization(const QContactDetail& detail,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);
    void encodeRingtone(const QContactDetail &detail,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);
    void encodeAvatar(const QContactDetail &detail,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);
    void encodeGender(const QContactDetail &detail,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);
    void encodeNickname(const QContactDetail &detail,
            const QVersitDocument& document,
            QList<QVersitProperty>* removedProperties,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);
    void encodeTag(const QContactDetail &detail,
            const QVersitDocument& document,
            QList<QVersitProperty>* removedProperties,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);
    void encodeAnniversary(const QContactDetail &detail,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);
    void encodeOnlineAccount(const QContactDetail &detail,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);
    void encodeFamily(const QContactDetail &detail,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);
    void encodeFavorite(const QContactDetail &detail,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);
    void encodeDisplayLabel(
            const QContactDetail &detail,
            const QVersitDocument& document,
            QList<QVersitProperty>* removedProperties,
            QList<QVersitProperty>* generatedProperties,
            QSet<int>* processedFields);
    void encodeExtendedDetail(const QContactDetail &detail,
            QList<QVersitProperty>* generatedProperties,
            QSet<int> *processedFields);

    bool isValidRemoteUrl(const QString& resourceIdentifier);
    void encodeParameters(QVersitProperty& property,
        const QContactDetail::DetailType detailType,
        const QList<int> &contexts,
        const QList<int> &subTypes=QList<int>());
    bool encodeContentFromFile(const QString& resourcePath, QVersitProperty& property);

public: // Data
    QList<QVersitDocument> mDocuments;
    QMap<int, QVersitContactExporter::Error> mErrors;
    QVersitContactExporterDetailHandler* mDetailHandler;
    QVersitContactExporterDetailHandlerV2* mDetailHandler2;
    QList<QVersitContactHandler*> mPluginDetailHandlers;
    int mDetailHandlerVersion;
    QVersitDefaultResourceHandler* mDefaultResourceHandler;
    QVersitResourceHandler* mResourceHandler;

    // detail type -> <field type, versit property name>:
    QMap<QContactDetail::DetailType, QPair<int, QString> > mPropertyMappings;
    QMap< QPair<QContactDetail::DetailType, int>, QString> mSubTypeMappings;
    QHash< int ,QString> mContextMappings;
};

QT_END_NAMESPACE_VERSIT

#endif // QVERSITCONTACTEXPORTER_P_H
