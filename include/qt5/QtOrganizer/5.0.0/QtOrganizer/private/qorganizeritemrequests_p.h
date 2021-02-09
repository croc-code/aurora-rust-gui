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

#ifndef QORGANIZERITEMREQUESTS_P_H
#define QORGANIZERITEMREQUESTS_P_H

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

#include <private/qorganizerabstractrequest_p.h>

QT_BEGIN_NAMESPACE_ORGANIZER

class QOrganizerItemSaveRequestPrivate : public QOrganizerAbstractRequestPrivate
{
public:
    QOrganizerItemSaveRequestPrivate()
        : QOrganizerAbstractRequestPrivate()
    {
    }

    ~QOrganizerItemSaveRequestPrivate()
    {
    }

    QOrganizerAbstractRequest::RequestType type() const
    {
        return QOrganizerAbstractRequest::ItemSaveRequest;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug &dbg) const
    {
        dbg.nospace() << "QOrganizerItemSaveRequest(\n";
        dbg.nospace() << "* items=";
        dbg.nospace() << m_organizeritems;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* definitionMask=";
        dbg.nospace() << m_detailMask;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* errorMap=";
        dbg.nospace() << m_errors;
        dbg.nospace() << "\n)";
        return dbg.maybeSpace();
    }
#endif

    QList<QOrganizerItem> m_organizeritems;
    QMap<int, QOrganizerManager::Error> m_errors;
    QList<QOrganizerItemDetail::DetailType> m_detailMask;
};

class QOrganizerItemFetchRequestPrivate : public QOrganizerAbstractRequestPrivate
{
public:
    QOrganizerItemFetchRequestPrivate()
        : QOrganizerAbstractRequestPrivate()
        , m_maxCount(-1)
    {
    }

    ~QOrganizerItemFetchRequestPrivate()
    {
    }

    QOrganizerAbstractRequest::RequestType type() const
    {
        return QOrganizerAbstractRequest::ItemFetchRequest;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug &dbg) const
    {
        dbg.nospace() << "QOrganizerItemFetchRequest(\n";
        dbg.nospace() << "* items=";
        dbg.nospace() << m_organizeritems;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* filter=";
        dbg.nospace() << m_filter;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* sorting=";
        dbg.nospace() << m_sorting;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* startDate=";
        dbg.nospace() << m_startDate;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* endDate=";
        dbg.nospace() << m_endDate;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* fetchHint=";
        dbg.nospace() << m_fetchHint;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* maxCount=";
        dbg.nospace() << m_maxCount;
        dbg.nospace() << "\n)";
        return dbg.maybeSpace();
    }
#endif

    QOrganizerItemFilter m_filter;
    QList<QOrganizerItemSortOrder> m_sorting;
    QOrganizerItemFetchHint m_fetchHint;

    QList<QOrganizerItem> m_organizeritems;

    QDateTime m_startDate;
    QDateTime m_endDate;

    int m_maxCount;
};

class QOrganizerItemFetchForExportRequestPrivate : public QOrganizerAbstractRequestPrivate
{
public:
    QOrganizerItemFetchForExportRequestPrivate()
        : QOrganizerAbstractRequestPrivate()
    {
    }

    ~QOrganizerItemFetchForExportRequestPrivate()
    {
    }

    QOrganizerAbstractRequest::RequestType type() const
    {
        return QOrganizerAbstractRequest::ItemFetchForExportRequest;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug &dbg) const
    {
        dbg.nospace() << "QOrganizerItemFetchForExportRequest(\n";
        dbg.nospace() << "* items=";
        dbg.nospace() << m_organizeritems;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* filter=";
        dbg.nospace() << m_filter;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* sorting=";
        dbg.nospace() << m_sorting;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* startDate=";
        dbg.nospace() << m_startDate;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* endDate=";
        dbg.nospace() << m_endDate;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* fetchHint=";
        dbg.nospace() << m_fetchHint;
        dbg.nospace() << "\n)";
        return dbg.maybeSpace();
    }
#endif

    QOrganizerItemFilter m_filter;
    QList<QOrganizerItemSortOrder> m_sorting;
    QOrganizerItemFetchHint m_fetchHint;

    QList<QOrganizerItem> m_organizeritems;

    QDateTime m_startDate;
    QDateTime m_endDate;
};

class QOrganizerItemFetchByIdRequestPrivate : public QOrganizerAbstractRequestPrivate
{
public:
    QOrganizerItemFetchByIdRequestPrivate()
        : QOrganizerAbstractRequestPrivate()
    {
    }

    ~QOrganizerItemFetchByIdRequestPrivate()
    {
    }

    QOrganizerAbstractRequest::RequestType type() const
    {
        return QOrganizerAbstractRequest::ItemFetchByIdRequest;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug &dbg) const
    {
        dbg.nospace() << "QOrganizerItemFetchByIdRequest(\n";
        dbg.nospace() << "* items=";
        dbg.nospace() << m_items;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* ids=";
        dbg.nospace() << m_ids;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* fetchHint=";
        dbg.nospace() << m_fetchHint;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* errorMap=";
        dbg.nospace() << m_errors;
        dbg.nospace() << "\n)";
        return dbg.maybeSpace();
    }
#endif

    QList<QOrganizerItemId> m_ids;
    QOrganizerItemFetchHint m_fetchHint;

    QList<QOrganizerItem> m_items;
    QMap<int, QOrganizerManager::Error> m_errors;
};

class QOrganizerItemOccurrenceFetchRequestPrivate : public QOrganizerAbstractRequestPrivate
{
public:
    QOrganizerItemOccurrenceFetchRequestPrivate()
        : QOrganizerAbstractRequestPrivate(), m_maxOccurrences(-1)
    {
    }

    ~QOrganizerItemOccurrenceFetchRequestPrivate()
    {
    }

    QOrganizerAbstractRequest::RequestType type() const
    {
        return QOrganizerAbstractRequest::ItemOccurrenceFetchRequest;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug &dbg) const
    {
        dbg.nospace() << "QOrganizerItemOccurrenceFetchRequest(\n";
        dbg.nospace() << "* itemOccurrences=";
        dbg.nospace() << m_organizeritems;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* parentItem=";
        dbg.nospace() << m_generator;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* startDate=";
        dbg.nospace() << m_startDate;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* endDate=";
        dbg.nospace() << m_endDate;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* fetchHint=";
        dbg.nospace() << m_fetchHint;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* maxOccurrences=";
        dbg.nospace() << m_maxOccurrences;
        dbg.nospace() << "\n)";
        return dbg.maybeSpace();
    }
#endif

    QOrganizerItem m_generator;
    QDateTime m_startDate;
    QDateTime m_endDate;
    int m_maxOccurrences;
    QOrganizerItemFetchHint m_fetchHint;

    QList<QOrganizerItem> m_organizeritems;
};

class QOrganizerItemRemoveRequestPrivate : public QOrganizerAbstractRequestPrivate
{
public:
    QOrganizerItemRemoveRequestPrivate()
        : QOrganizerAbstractRequestPrivate()
    {
    }

    ~QOrganizerItemRemoveRequestPrivate()
    {
    }

    QOrganizerAbstractRequest::RequestType type() const
    {
        return QOrganizerAbstractRequest::ItemRemoveRequest;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug &dbg) const
    {
        dbg.nospace() << "QOrganizerItemRemoveRequest(";
        dbg.nospace() << "items=";
        dbg.nospace() << m_organizeritems;
        dbg.nospace() << ",";
        dbg.nospace() << "errorMap=";
        dbg.nospace() << m_errors;
        dbg.nospace() << "\n)";
        return dbg.maybeSpace();
    }
#endif

    QList<QOrganizerItem> m_organizeritems;
    QMap<int, QOrganizerManager::Error> m_errors;
};

class QOrganizerItemRemoveByIdRequestPrivate : public QOrganizerAbstractRequestPrivate
{
public:
    QOrganizerItemRemoveByIdRequestPrivate()
        : QOrganizerAbstractRequestPrivate()
    {
    }

    ~QOrganizerItemRemoveByIdRequestPrivate()
    {
    }

    QOrganizerAbstractRequest::RequestType type() const
    {
        return QOrganizerAbstractRequest::ItemRemoveByIdRequest;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug& dbg) const
    {
        dbg.nospace() << "QOrganizerItemRemoveByIdRequest(";
        dbg.nospace() << "itemIds=";
        dbg.nospace() << m_organizeritemIds;
        dbg.nospace() << ",";
        dbg.nospace() << "errorMap=";
        dbg.nospace() << m_errors;
        dbg.nospace() << "\n)";
        return dbg.maybeSpace();
    }
#endif

    QList<QOrganizerItemId> m_organizeritemIds;
    QMap<int, QOrganizerManager::Error> m_errors;
};

class QOrganizerItemIdFetchRequestPrivate : public QOrganizerAbstractRequestPrivate
{
public:
    QOrganizerItemIdFetchRequestPrivate()
        : QOrganizerAbstractRequestPrivate()
    {
    }

    ~QOrganizerItemIdFetchRequestPrivate()
    {
    }

    QOrganizerAbstractRequest::RequestType type() const
    {
        return QOrganizerAbstractRequest::ItemIdFetchRequest;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug &dbg) const
    {
        dbg.nospace() << "QOrganizerItemIdFetchRequest(\n";
        dbg.nospace() << "* itemIds=";
        dbg.nospace() << m_ids;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* filter=";
        dbg.nospace() << m_filter;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* sorting=";
        dbg.nospace() << m_sorting;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* startDate=";
        dbg.nospace() << m_startDate;
        dbg.nospace() << ",\n";
        dbg.nospace() << "* endDate=";
        dbg.nospace() << m_endDate;
        dbg.nospace() << "\n)";
        return dbg.maybeSpace();
    }
#endif

    QOrganizerItemFilter m_filter;
    QList<QOrganizerItemSortOrder> m_sorting;

    QList<QOrganizerItemId> m_ids;

    QDateTime m_startDate;
    QDateTime m_endDate;
};

class QOrganizerCollectionFetchRequestPrivate : public QOrganizerAbstractRequestPrivate
{
public:
    QOrganizerCollectionFetchRequestPrivate()
        : QOrganizerAbstractRequestPrivate()
    {
    }

    ~QOrganizerCollectionFetchRequestPrivate()
    {
    }

    QOrganizerAbstractRequest::RequestType type() const
    {
        return QOrganizerAbstractRequest::CollectionFetchRequest;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug &dbg) const
    {
        dbg.nospace() << "QOrganizerCollectionFetchRequest(";
        dbg.nospace() << "collections=";
        dbg.nospace() << m_collections;
        dbg.nospace() << ")";
        return dbg.maybeSpace();
    }
#endif

    QList<QOrganizerCollection> m_collections;
};

class QOrganizerCollectionRemoveRequestPrivate : public QOrganizerAbstractRequestPrivate
{
public:
    QOrganizerCollectionRemoveRequestPrivate()
        : QOrganizerAbstractRequestPrivate()
    {
    }

    ~QOrganizerCollectionRemoveRequestPrivate()
    {
    }

    QOrganizerAbstractRequest::RequestType type() const
    {
        return QOrganizerAbstractRequest::CollectionRemoveRequest;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug &dbg) const
    {
        dbg.nospace() << "QOrganizerCollectionRemoveRequest(";
        dbg.nospace() << "collectionIds=";
        dbg.nospace() << m_collectionIds;
        dbg.nospace() << ",";
        dbg.nospace() << "errorMap=";
        dbg.nospace() << m_errors;
        dbg.nospace() << ")";
        return dbg.maybeSpace();
    }
#endif

    QList<QOrganizerCollectionId> m_collectionIds;
    QMap<int, QOrganizerManager::Error> m_errors;
};

class QOrganizerCollectionSaveRequestPrivate : public QOrganizerAbstractRequestPrivate
{
public:
    QOrganizerCollectionSaveRequestPrivate()
        : QOrganizerAbstractRequestPrivate()
    {
    }

    ~QOrganizerCollectionSaveRequestPrivate()
    {
    }

    QOrganizerAbstractRequest::RequestType type() const
    {
        return QOrganizerAbstractRequest::CollectionSaveRequest;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug &dbg) const
    {
        dbg.nospace() << "QOrganizerCollectionSaveRequest(";
        dbg.nospace() << "collections=";
        dbg.nospace() << m_collections;
        dbg.nospace() << ",";
        dbg.nospace() << "errorMap=";
        dbg.nospace() << m_errors;
        dbg.nospace() << ")";
        return dbg.maybeSpace();
    }
#endif

    QList<QOrganizerCollection> m_collections;
    QMap<int, QOrganizerManager::Error> m_errors;
};

QT_END_NAMESPACE_ORGANIZER

#endif // QORGANIZERITEMREQUESTS_P_H
