/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSystems module of the Qt Toolkit.
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

#ifndef QDEVICEINFO_LINUX_P_H
#define QDEVICEINFO_LINUX_P_H

#include <qdeviceinfo.h>

#include <QStringList>
#ifndef QT_NO_DBUS
#include <QtDBus/QDBusVariant>
#endif

QT_BEGIN_NAMESPACE

class QTimer;

#if !defined(QT_NO_OFONO)
class QOfonoWrapper;
#endif // QT_NO_OFONO

class QDeviceInfoPrivate : public QObject
{
    Q_OBJECT

public:
    QDeviceInfoPrivate(QDeviceInfo *parent = 0);

    bool hasFeature(QDeviceInfo::Feature feature);
    int imeiCount();
    QDeviceInfo::LockTypeFlags activatedLocks();
    QDeviceInfo::LockTypeFlags enabledLocks();
    QDeviceInfo::ThermalState thermalState();
    QString imei(int interface);
    QString manufacturer();
    QString model();
    QString productName();
    QString uniqueDeviceID();
    QString version(QDeviceInfo::Version type);
    QString operatingSystemName();
    QString boardName();

    bool currentBluetoothPowerState();

Q_SIGNALS:
    void thermalStateChanged(QDeviceInfo::ThermalState state);
    void bluetoothStateChanged(bool on);

protected:
    void connectNotify(const QMetaMethod &signal);
    void disconnectNotify(const QMetaMethod &signal);

private Q_SLOTS:
    void onTimeout();
#ifndef QT_NO_DBUS
    void connectBtPowered();
    void bluezPropertyChanged(const QString&, QDBusVariant);
#endif
private:
#if !defined(QT_SIMULATOR)
    QDeviceInfo * const q_ptr;
    Q_DECLARE_PUBLIC(QDeviceInfo)
#endif

    bool watchThermalState;
    QDeviceInfo::ThermalState currentThermalState;
    QString manufacturerBuffer;
    QString modelBuffer;
    QStringList imeiBuffer;
    QString productNameBuffer;
    QString uniqueDeviceIDBuffer;
    QString versionBuffer[2];
    QTimer *timer;
    QString boardNameString;
    QString osName;

    QDeviceInfo::ThermalState getThermalState();

#if !defined(QT_NO_OFONO)
    QOfonoWrapper *ofonoWrapper;
#endif // QT_NO_OFONO
    QString findInRelease(const QString &searchTerm, const QString &file = QString());
    bool isUuid(const QString &id);

    bool connectedBtPower;
    bool btPowered;
};

QT_END_NAMESPACE

#endif // QDEVICEINFO_LINUX_P_H
