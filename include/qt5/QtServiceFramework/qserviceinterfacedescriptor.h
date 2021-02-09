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

#ifndef QSERVICEINTERFACEDESCRIPTOR_H
#define QSERVICEINTERFACEDESCRIPTOR_H

#include "qserviceframeworkglobal.h"
#include <QString>
#include <QVariant>
#include "qservice.h"

QT_USE_NAMESPACE

#ifdef SERVICE_XML_GENERATOR
#undef Q_SERVICEFW_EXPORT
#define Q_SERVICEFW_EXPORT
#endif


QT_BEGIN_NAMESPACE

class QDebug;
class QStringList;
class QDataStream;


class QServiceInterfaceDescriptorPrivate;
class Q_SERVICEFW_EXPORT QServiceInterfaceDescriptor
{
public:
    enum Attribute {
        Capabilities = 0,
        Location,
        ServiceDescription,
        InterfaceDescription,
        ServiceType
    };

    QServiceInterfaceDescriptor();
    QServiceInterfaceDescriptor(const QServiceInterfaceDescriptor& other);
    ~QServiceInterfaceDescriptor();

    QServiceInterfaceDescriptor& operator=(const QServiceInterfaceDescriptor& other);
    bool operator==(const QServiceInterfaceDescriptor& other) const;
    inline bool operator!=(const QServiceInterfaceDescriptor& other) const
    { return !operator==(other); }

    QString serviceName() const;
    QString interfaceName() const;
    int majorVersion() const;
    int minorVersion() const;

    bool isValid() const;

    QService::Scope scope() const;

    QVariant attribute(QServiceInterfaceDescriptor::Attribute which) const;
    QString customAttribute(const QString& which) const;
    QStringList customAttributes() const;

private:
    QServiceInterfaceDescriptorPrivate* d;

    friend class QServiceInterfaceDescriptorPrivate;
    friend class QServiceManager;
    friend class ServiceDatabase;
    friend class ServiceMetaData;
    friend class DatabaseManager;
#ifndef QT_NO_DATASTREAM
    friend Q_SERVICEFW_EXPORT QDataStream &operator<<(QDataStream &, const QServiceInterfaceDescriptor &);
    friend Q_SERVICEFW_EXPORT QDataStream &operator>>(QDataStream &, QServiceInterfaceDescriptor &);
#endif
};

inline uint qHash(const QServiceInterfaceDescriptor &desc)
{
    return qHash(desc.serviceName()) + qHash(desc.interfaceName()) + desc.majorVersion() * 7 + desc.minorVersion() * 7;
}

#ifndef QT_NO_DATASTREAM
Q_SERVICEFW_EXPORT QDataStream &operator<<(QDataStream &, const QServiceInterfaceDescriptor &);
Q_SERVICEFW_EXPORT QDataStream &operator>>(QDataStream &, QServiceInterfaceDescriptor &);
#endif
#ifndef QT_NO_DEBUG_STREAM
Q_SERVICEFW_EXPORT QDebug operator<<(QDebug, const QServiceInterfaceDescriptor &);
#endif


QT_END_NAMESPACE

#endif
