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

#ifndef QOFONOWRAPPER_P_H
#define QOFONOWRAPPER_P_H

#include <qnetworkinfo.h>

#include <QtCore/qobject.h>
#include <QtCore/qmap.h>
#include <QtCore/qstringlist.h>
#include <QtDBus/qdbuscontext.h>
#include <QtDBus/qdbusextratypes.h>

#if !defined(QT_NO_OFONO)

QT_BEGIN_NAMESPACE

class QOfonoWrapper : public QObject, protected QDBusContext
{
    Q_OBJECT

public:
    QOfonoWrapper(QObject *parent = 0);

    static bool isOfonoAvailable();

    // Manager Interface
    QStringList allModems();

    // Network Registration Interface
    int signalStrength(const QString &modemPath);
    QNetworkInfo::CellDataTechnology currentCellDataTechnology(const QString &modemPath);
    QNetworkInfo::NetworkStatus networkStatus(const QString &modemPath);
    QString cellId(const QString &modemPath);
    QString currentMcc(const QString &modemPath);
    QString currentMnc(const QString &modemPath);
    QString lac(const QString &modemPath);
    QString operatorName(const QString &modemPath);

    QNetworkInfo::NetworkMode networkMode(const QString& modemPath);

    // SIM Manager Interface
    QString homeMcc(const QString &modemPath);
    QString homeMnc(const QString &modemPath);
    QString imsi(const QString &modemPath);

    // Modem Interface
    QString imei(const QString &modemPath);

Q_SIGNALS:
    void cellIdChanged(int interface, const QString &id);
    void currentCellDataTechnologyChanged(int interface, QNetworkInfo::CellDataTechnology tech);
    void currentMobileCountryCodeChanged(int interface, const QString &mcc);
    void currentMobileNetworkCodeChanged(int interface, const QString &mnc);
    void currentNetworkModeChanged(QNetworkInfo::NetworkMode mode);
    void locationAreaCodeChanged(int interface, const QString &lac);
    void networkInterfaceCountChanged(QNetworkInfo::NetworkMode mode, int count);
    void networkNameChanged(QNetworkInfo::NetworkMode mode, int interface, const QString &name);
    void networkSignalStrengthChanged(QNetworkInfo::NetworkMode mode, int interface, int strength);
    void networkStatusChanged(QNetworkInfo::NetworkMode mode, int interface, QNetworkInfo::NetworkStatus status);

protected:
    void connectNotify(const QMetaMethod &signal);
    void disconnectNotify(const QMetaMethod &signal);

private Q_SLOTS:
    void onOfonoModemAdded(const QDBusObjectPath &path);
    void onOfonoModemRemoved(const QDBusObjectPath &path);
    void onOfonoPropertyChanged(const QString &property, const QDBusVariant &value);

private:
    static int available;

    QNetworkInfo::CellDataTechnology technologyStringToEnum(const QString &technology);
    QNetworkInfo::NetworkMode technologyToMode(const QString &technology);
    QNetworkInfo::NetworkStatus statusStringToEnum(const QString &status);
    QString currentTechnology(const QString &modemPath);

    // Manager Interface
    QStringList getAllModems();

    // Network Registration Interface
    int getSignalStrength(const QString &modemPath);
    QNetworkInfo::CellDataTechnology getCurrentCellDataTechnology(const QString &modemPath);
    QNetworkInfo::NetworkStatus getNetworkStatus(const QString &modemPath);
    QString getCellId(const QString &modemPath);
    QString getCurrentMcc(const QString &modemPath);
    QString getCurrentMnc(const QString &modemPath);
    QString getLac(const QString &modemPath);
    QString getOperatorName(const QString &modemPath);

    bool watchAllModems;
    bool watchProperties;
    QMap<QString, int> signalStrengths;
    QMap<QString, QNetworkInfo::CellDataTechnology> currentCellDataTechnologies;
    QMap<QString, QNetworkInfo::NetworkStatus> networkStatuses;
    QMap<QString, QString> cellIds;
    QMap<QString, QString> currentMccs;
    QMap<QString, QString> currentMncs;
    QMap<QString, QString> lacs;
    QMap<QString, QString> operatorNames;
    QStringList allModemPaths;
};

QT_END_NAMESPACE

#endif // QT_NO_OFONO

#endif // QOFONOWRAPPER_P_H
