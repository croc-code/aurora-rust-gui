/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtOrganizer module of the Qt Toolkit.
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

#ifndef QORGANIZERITEM_H
#define QORGANIZERITEM_H

#include <qorganizeritemid.h>
#include <qorganizeritemdetail.h>
#include <qorganizeritemtype.h>
#include <qorganizercollectionid.h>

QT_BEGIN_NAMESPACE_ORGANIZER

class QOrganizerItemData;

// MSVC needs the function declared before the friend declaration
#ifndef QT_NO_DATASTREAM
class QOrganizerItem;
Q_ORGANIZER_EXPORT QDataStream &operator<<(QDataStream &out, const QOrganizerItem &item);
Q_ORGANIZER_EXPORT QDataStream &operator>>(QDataStream &in, QOrganizerItem &item);
#endif // QT_NO_DATASTREAM

class Q_ORGANIZER_EXPORT QOrganizerItem
{
public:
    QOrganizerItem();
    QOrganizerItem(const QOrganizerItem &other);
    ~QOrganizerItem();

    QOrganizerItem &operator=(const QOrganizerItem &other);

    bool operator==(const QOrganizerItem &other) const;
    bool operator!=(const QOrganizerItem &other) const {return !(other == *this);}

    QOrganizerItemId id() const;
    void setId(const QOrganizerItemId &id);

    QOrganizerCollectionId collectionId() const;
    void setCollectionId(const QOrganizerCollectionId &collectionId);

    bool isEmpty() const;
    void clearDetails();

    QOrganizerItemDetail detail(QOrganizerItemDetail::DetailType detailType = QOrganizerItemDetail::TypeUndefined) const;
    QList<QOrganizerItemDetail> details(QOrganizerItemDetail::DetailType detailType = QOrganizerItemDetail::TypeUndefined) const;

    bool saveDetail(QOrganizerItemDetail *detail);
    bool removeDetail(QOrganizerItemDetail *detail);

    QOrganizerItemType::ItemType type() const;
    void setType(QOrganizerItemType::ItemType type);

    QString displayLabel() const;
    void setDisplayLabel(const QString &label);

    QString description() const;
    void setDescription(const QString &description);

    QStringList comments() const;
    void clearComments();
    void setComments(const QStringList &comments);
    void addComment(const QString &comment);

    QStringList tags() const;
    void clearTags();
    void addTag(const QString &tag);
    void setTags(const QStringList &tags);

    QString guid() const;
    void setGuid(const QString &guid);

    QVariant data(const QString &name) const;
    void setData(const QString &name, const QVariant &data);

protected:
    explicit QOrganizerItem(QOrganizerItemType::ItemType type);
    QOrganizerItem(const QOrganizerItem &other, QOrganizerItemType::ItemType expectedType);
    QOrganizerItem &assign(const QOrganizerItem &other, QOrganizerItemType::ItemType expectedType);

protected:
    friend class QOrganizerItemData;
    friend class QOrganizerManager;
    friend class QOrganizerManagerData;
    friend class QOrganizerManagerEngine;

#ifndef QT_NO_DATASTREAM
    Q_ORGANIZER_EXPORT friend QDataStream &operator<<(QDataStream &out, const QOrganizerItem &item);
    Q_ORGANIZER_EXPORT friend QDataStream &operator>>(QDataStream &in, QOrganizerItem &item);
#endif // QT_NO_DATASTREAM

    QSharedDataPointer<QOrganizerItemData> d;
};

Q_ORGANIZER_EXPORT uint qHash(const QOrganizerItem &key);

#ifndef QT_NO_DEBUG_STREAM
Q_ORGANIZER_EXPORT QDebug operator<<(QDebug dbg, const QOrganizerItem &item);
#endif // QT_NO_DEBUG_STREAM

#define Q_DECLARE_CUSTOM_ORGANIZER_ITEM(className, typeConstant) \
    className() : QOrganizerItem(typeConstant) {} \
    className(const QOrganizerItem &other) : QOrganizerItem(other, typeConstant) {} \
    className& operator=(const QOrganizerItem &other) {assign(other, typeConstant); return *this;}

QT_END_NAMESPACE_ORGANIZER

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO(QTORGANIZER_PREPEND_NAMESPACE(QOrganizerItem), Q_MOVABLE_TYPE);
QT_END_NAMESPACE

#endif // QORGANIZERITEM_H
