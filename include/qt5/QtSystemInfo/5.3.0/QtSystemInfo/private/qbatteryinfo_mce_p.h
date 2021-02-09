/****************************************************************************
**
** Copyright (C) 2019 Jolla Ltd.
** Copyright (c) 2019 Open Mobile Platform LLC.
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

#ifndef QBATTERYINFO_MCE_P_H
#define QBATTERYINFO_MCE_P_H

#include <qbatteryinfo.h>

class QMceChargerType;
class QMceBatteryState;
class QMceBatteryStatus;
class QMceBatteryLevel;

QT_BEGIN_NAMESPACE

enum class Prop;
class QBatteryInfoPrivate : public QObject
{
    Q_OBJECT

public:
    QBatteryInfoPrivate(QBatteryInfo *);
    QBatteryInfoPrivate(int, QBatteryInfo *);
    ~QBatteryInfoPrivate() {}

    bool isValid() const;
    int level() const;
    int cycleCount() const;
    float temperature() const;
    int batteryCount() const;
    int batteryIndex() const;
    int currentFlow() const;
    int maximumCapacity() const;
    int remainingCapacity() const;
    int remainingChargingTime() const;
    int voltage() const;
    QBatteryInfo::ChargerType chargerType() const;
    QBatteryInfo::ChargingState chargingState() const;
    QBatteryInfo::LevelStatus levelStatus() const;
    QBatteryInfo::Health health() const;

    void setBatteryIndex(int);

Q_SIGNALS:
    void validChanged(bool);
    void chargerTypeChanged(QBatteryInfo::ChargerType);
    void chargingStateChanged(QBatteryInfo::ChargingState);
    void levelChanged(int);
    void currentFlowChanged(int);
    void cycleCountChanged(int);
    void remainingCapacityChanged(int);
    void remainingChargingTimeChanged(int);
    void voltageChanged(int);
    void levelStatusChanged(QBatteryInfo::LevelStatus);
    void healthChanged(QBatteryInfo::Health);
    void temperatureChanged(float);

private slots:
    void onValidChanged();
    void onChargerTypeChanged();
    void onBatteryStateChanged();
    void onBatteryStatusChanged();
    void onBatteryLevelChanged();

private:
    void init();
    bool m_isValid;
    QMceChargerType   *m_mceChargerType;
    QMceBatteryState  *m_mceBatteryState;
    QMceBatteryStatus *m_mceBatteryStatus;
    QMceBatteryLevel  *m_mceBatteryLevel;
};

QT_END_NAMESPACE

#endif // QBATTERYINFO_MCE_P_H
