/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Copyright (C) 2014 BlackBerry Limited. All rights reserved.
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

#ifndef QBATTERYINFO_LINUX_P_H
#define QBATTERYINFO_LINUX_P_H

#include <qbatteryinfo.h>

#include <QtCore/qmap.h>

QT_BEGIN_NAMESPACE

#if !defined(QT_NO_UDEV)
class QUDevWrapper;
#else
class QTimer;
#endif // QT_NO_UDEV

class QBatteryInfoPrivate : public QObject
{
    Q_OBJECT

public:
    QBatteryInfoPrivate(QBatteryInfo *parent);
    QBatteryInfoPrivate(int batteryIndex, QBatteryInfo *parent);
    ~QBatteryInfoPrivate();

    int batteryCount();
    int batteryIndex() const;
    bool isValid();
    int level(int battery);
    int level();
    int currentFlow(int battery);
    int currentFlow();
    int cycleCount(int battery);
    int cycleCount();
    int maximumCapacity(int battery);
    int maximumCapacity();
    int remainingCapacity(int battery);
    int remainingCapacity();
    int remainingChargingTime(int battery);
    int remainingChargingTime();
    int voltage(int battery);
    int voltage();
    QBatteryInfo::ChargerType chargerType();
    QBatteryInfo::ChargingState chargingState(int battery);
    QBatteryInfo::ChargingState chargingState();
    QBatteryInfo::LevelStatus levelStatus(int battery);
    QBatteryInfo::LevelStatus levelStatus();
    QBatteryInfo::Health health(int battery);
    QBatteryInfo::Health health();
    float temperature(int battery);
    float temperature();

    void setBatteryIndex(int batteryIndex);

Q_SIGNALS:
    void batteryCountChanged(int count);
    void batteryIndexChanged(int batteryIndex);
    void validChanged(bool isValid);
    void chargerTypeChanged(QBatteryInfo::ChargerType type);
    void chargingStateChanged(QBatteryInfo::ChargingState state);
    void levelChanged(int level);
    void currentFlowChanged(int flow);
    void cycleCountChanged(int cycleCount);
    void remainingCapacityChanged(int capacity);
    void remainingChargingTimeChanged(int seconds);
    void voltageChanged(int voltage);
    void levelStatusChanged(QBatteryInfo::LevelStatus levelStatus);
    void healthChanged(QBatteryInfo::Health health);
    void temperatureChanged(float temperature);

protected:
    void connectNotify(const QMetaMethod &signal);
    void disconnectNotify(const QMetaMethod &signal);

private Q_SLOTS:
#if !defined(QT_NO_UDEV)
    void onBatteryDataChanged(int battery, const QByteArray &attribute, const QByteArray &value);
    void onChargerTypeChanged(const QByteArray &value, bool enabled);
#else
    void onTimeout();
#endif // QT_NO_UDEV

private:
    QBatteryInfo * const q_ptr;
    Q_DECLARE_PUBLIC(QBatteryInfo)

    bool watchIsValid;
    bool forceWatchBatteryCount;
    bool watchBatteryCount;
    bool watchChargerType;
    bool watchChargingState;
    bool watchCurrentFlow;
    bool watchRemainingCapacity;
    bool watchRemainingChargingTime;
    bool watchVoltage;
    bool watchLevelStatus;
    int batteryCounts;
    int index;
    QMap<int, int> currentFlows; // <battery ID, current value> pair
    QMap<int, int> voltages;
    QMap<int, int> remainingCapacities;
    QMap<int, int> remainingChargingTimes;
    QMap<int, int> maximumCapacities;
    QMap<int, QBatteryInfo::ChargingState> chargingStates;
    QBatteryInfo::ChargerType currentChargerType;
    QMap<int, QBatteryInfo::LevelStatus> levelStatuss;
#if !defined(QT_NO_UDEV)
    QUDevWrapper *uDevWrapper;
#else
    QTimer *timer;
#endif // QT_NO_UDEV

    int getBatteryCount();
    int getCurrentFlow(int battery);
    int getRemainingCapacity(int battery);
    int getRemainingChargingTime(int battery);
    int getVoltage(int battery);
    QBatteryInfo::ChargerType getChargerType();
    QBatteryInfo::ChargingState getChargingState(int battery);
    QBatteryInfo::LevelStatus getLevelStatus(int battery);
};

QT_END_NAMESPACE

#endif // QBATTERYINFO_LINUX_P_H
