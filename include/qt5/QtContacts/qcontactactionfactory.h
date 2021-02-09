/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtContacts module of the Qt Toolkit.
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


#ifndef QCONTACTACTIONFACTORY_H
#define QCONTACTACTIONFACTORY_H

#include <qcontactsglobal.h>
#include <qcontactactiondescriptor.h>
#include <qcontactactiontarget.h>

#include <QObject>
#include <QtPlugin>
#include <QString>
#include <QList>
#include <QVariantMap>
#include <QStringList>
#include <QHash>

QT_BEGIN_NAMESPACE_CONTACTS

class QContactAction;
class Q_CONTACTS_EXPORT QContactActionFactory : public QObject
{
    Q_OBJECT

public:
    QContactActionFactory(QObject *parent_ = 0) : QObject(parent_) {}
    virtual ~QContactActionFactory();
    virtual QList<QContactActionDescriptor> actionDescriptors() const = 0;
    virtual QContactAction* create(const QContactActionDescriptor& which) const = 0;

    // Backend functionality for QCAD
    virtual QSet<QContactActionTarget> supportedTargets(const QContact& contact, const QContactActionDescriptor& which) const = 0;
    virtual QContactFilter contactFilter(const QContactActionDescriptor& which) const = 0;
    virtual QVariant metaData(const QString& key, const QList<QContactActionTarget>& targets, const QVariantMap& parameters, const QContactActionDescriptor& which) const = 0;

    virtual bool supportsContact(const QContact& contact, const QContactActionDescriptor& which) const; // virtual but not pure virtual; default impl. calls supportedTargets.isEmpty().

    inline static const QString InterfaceName() {return QStringLiteral("org.qt-project.Qt.QContactActionFactory");};

protected:
    QContactActionDescriptor createDescriptor(const QString& actionName, const QString& serviceName, const QString& actionIdentifier, int implementationVersion) const;
};

QT_END_NAMESPACE_CONTACTS

#endif
