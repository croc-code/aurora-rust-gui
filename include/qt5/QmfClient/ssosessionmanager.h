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

#ifndef SSOSESSIONMANAGER_H
#define SSOSESSIONMANAGER_H

#include "ssoauthplugin.h"
#include "qmailglobal.h"
#include "qmailaccount.h"
#include <QString>
#include <qglobal.h>

// Accounts
#include <Accounts/Account>
#include <SignOn/Identity>
#include <SignOn/SessionData>

using namespace SignOn;

class QMF_EXPORT SSOSessionManager : public QObject
{
    Q_OBJECT
public:
    SSOSessionManager(QObject* parent);
    ~SSOSessionManager();

    void cancel();
    bool createSsoIdentity(const QMailAccountId &id, const QString &serviceType);
    bool checkingCredentials() const;
    void credentialsNeedUpdate();
    void deleteSsoIdentity();
    void recreateSsoIdentity();
    void removeSsoIdentity();
    bool waitForSso();

signals:
    void ssoSessionResponse(const QMap<QString,QList<QByteArray> > &ssoLogin);
    void ssoSessionError(const QString &error);

protected slots:
    void ssoResponse(const SignOn::SessionData &sessionData);
    void ssoSessionError(const SignOn::Error &code);

private slots:
    void reAuthenticate();

private:
    bool authPluginAvailable(const QString &method) const;
    QString serviceUsername(const QString &serviceType) const;
    QString serviceCredentialsId(const QString &serviceType) const;
    void forceTokenRefresh();
    void sessionResponse(const SignOn::SessionData &sessionData);

    int _accountId;
    bool _waitForSso;
    bool _recreatingSession;
    bool _reAuthenticate;
    bool _credentialsCheck;
    QString _authMethod;
    QString _authMechanism;
    QString _authUsername;
    QVariantMap _authParameters;
    QString _serviceType;
    QString _accountProvider;
    QStringList _availableAuthMethods;
    SSOAuthService *_authService;
    SignOn::Identity *_identity;
    SignOn::AuthSession *_session;
    SignOn::SessionData _sessionData;
    QVariantMap _oldToken;
    QVariantMap _refreshSessionData;
};

#endif // SSOSESSIONMANAGER_H
