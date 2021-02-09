/****************************************************************************
**
** Copyright (C) 2013 Jolla Ltd.
** Contact: Valério Valério <valerio.valerio@jollamobile.com>
**
** This file is part of the Qt Messaging Framework.
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

#ifndef SSOAUTHPLUGIN_H
#define SSOAUTHPLUGIN_H

#include "qmailglobal.h"
#include <QObject>
#include <QString>
#include <QVariantMap>
#include <SignOn/SessionData>

class QMF_EXPORT SSOAuthService : public QObject
{
    Q_OBJECT

public:
    SSOAuthService(QObject* parent = 0);
    ~SSOAuthService();

    virtual QString key() const = 0;
    virtual QMap<QString, QList<QByteArray> > authentication(const SignOn::SessionData &sessionData,
                                         const QString &serviceType, const QString &userName) const = 0;
    virtual void credentialsNeedUpdate(int accountId) = 0;
    virtual SignOn::SessionData sessionData(const QString &accountProvider, QVariantMap authParameters) const = 0;
    virtual SSOAuthService *createService() = 0;
};

class QMF_EXPORT SSOAuthFactory
{
public:
    static QStringList keys();
    static SSOAuthService *createService(const QString& key);
};

#endif // SSOAUTHPLUGIN_H
