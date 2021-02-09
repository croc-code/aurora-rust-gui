/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtFeedback module of the Qt Toolkit.
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

#ifndef QFEEDBACKACTUATOR_H
#define QFEEDBACKACTUATOR_H

#include "qfeedbackglobal.h"
#include <QtCore/QObject>

QT_BEGIN_HEADER
QT_BEGIN_NAMESPACE

class QFeedbackEffect;

class Q_FEEDBACK_EXPORT QFeedbackActuator : public QObject
{
    Q_OBJECT

    Q_ENUMS(Capability)
    Q_ENUMS(State)

    Q_PROPERTY(int id READ id)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QFeedbackActuator::State state READ state)
    Q_PROPERTY(bool valid READ isValid)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)

public:
    enum Capability {
        Envelope,
        Period
    };

    enum State {
        Busy,
        Ready,
        Unknown
    };

    QFeedbackActuator(QObject *parent = 0);

    int id() const;
    bool isValid() const;

    QString name() const;
    State state() const;

    Q_INVOKABLE bool isCapabilitySupported(Capability) const;

    bool isEnabled() const;
    void setEnabled(bool);

    static QList<QFeedbackActuator*> actuators();
    bool operator==(const QFeedbackActuator&) const;

Q_SIGNALS:
    void enabledChanged();

private:
    QFeedbackActuator(QObject *parent, int id);
    friend class QFeedbackHapticsInterface;
    int m_id;
};

QT_END_NAMESPACE
QT_END_HEADER

#endif // QFEEDBACKACTUATOR_H
