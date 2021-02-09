/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtDocGallery module of the Qt Toolkit.
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

#ifndef QGALLERYTRACKERITEMLIST_P_P_H
#define QGALLERYTRACKERITEMLIST_P_P_H

#include "qgallerytrackerresultset_p.h"
#include "qgalleryresultset_p.h"

#include "qgallerytrackerlistcolumn_p.h"
#include "qgallerytrackermetadataedit_p.h"
#include "qgallerytrackerschema_p.h"

#include <QtCore/qcoreapplication.h>
#include <QtCore/qbasictimer.h>
#include <QtCore/qcoreevent.h>
#include <QtCore/qmutex.h>
#include <QtCore/qqueue.h>
#include <QtCore/qrunnable.h>
#include <QtCore/qthread.h>
#include <QtCore/qwaitcondition.h>

QT_BEGIN_NAMESPACE_DOCGALLERY

class QGalleryTrackerResultSetThread : public QThread
{
public:
    QGalleryTrackerResultSetThread(QRunnable *runnable) : runnable(runnable) {}

    void run() { runnable->run(); }

private:
    QRunnable *runnable;
};

class QGalleryTrackerResultSetPrivate : public QGalleryResultSetPrivate, public QRunnable
{
    Q_DECLARE_PUBLIC(QGalleryTrackerResultSet)
public:
    struct SyncEvent
    {
        enum Type
        {
            Update,
            Replace,
            Finish
        };

        const Type type;
        const int rIndex;
        const int rCount;
        const int iIndex;
        const int iCount;

        static SyncEvent *updateEvent(int aIndex, int iIndex, int count) {
            return new SyncEvent(Update, aIndex, count, iIndex, count); }

        static SyncEvent *replaceEvent(int aIndex, int aCount, int iIndex, int iCount) {
            return new SyncEvent(Replace, aIndex, aCount, iIndex, iCount); }

        static SyncEvent *finishEvent(int aIndex, int iIndex) {
            return new SyncEvent(Finish, aIndex, 0, iIndex, 0); }

    private:
        SyncEvent(Type type, int rIndex, int rCount, int iIndex, int iCount)
            : type(type), rIndex(rIndex), rCount(rCount), iIndex(iIndex), iCount(iCount) {}

    };

    class SyncEventQueue
    {
    public:
        SyncEventQueue() {}
        ~SyncEventQueue() { qDeleteAll(m_queue); }

        bool enqueue(SyncEvent *event)
        {
            QMutexLocker locker(&m_mutex);

            m_queue.enqueue(event);
            m_wait.wakeOne();

            return m_queue.count() == 1;
        }

        SyncEvent *dequeue()
        {
            QMutexLocker locker(&m_mutex);

            return !m_queue.isEmpty() ? m_queue.dequeue() : 0;
        }

        bool waitForEvent(int msecs)
        {
            QMutexLocker locker(&m_mutex);

            if (!m_queue.isEmpty())
                return true;

            return m_wait.wait(&m_mutex, msecs);
        }

    private:
        QQueue<SyncEvent *> m_queue;
        QMutex m_mutex;
        QWaitCondition m_wait;
    };

    struct Row
    {
        Row() {}
        Row(QVector<QVariant>::iterator begin, QVector<QVariant>::iterator end)
            : begin(begin), end(end) {}

        QVector<QVariant>::iterator begin;
        QVector<QVariant>::iterator end;
    };

    struct row_iterator
    {
        row_iterator() {}
        row_iterator(QVector<QVariant>::iterator begin, int width) : begin(begin), width(width) {}

        bool operator != (const row_iterator &other) const { return begin != other.begin; }
        bool operator <(const row_iterator &other) const { return begin < other.begin; }

        row_iterator &operator ++() { begin += width; return *this; }
        row_iterator &operator --() { begin -= width; return *this; }

        row_iterator operator ++(int) { row_iterator n(*this); begin += width; return n; }
        row_iterator operator --(int) { row_iterator n(*this); begin -= width; return n; }

        int operator -(const row_iterator &other) const { return (begin - other.begin) / width; }
        int operator -(const QVector<QVariant>::const_iterator &iterator) const {
            return (begin - iterator) / width; }

        row_iterator operator +(int span) const {
            return row_iterator(begin + (span * width), width); }

        row_iterator &operator +=(int span) { begin += span * width; return *this; }

        Row &operator *() {  return row = Row(begin, begin + width); }
        const Row &operator *() const {  return row = Row(begin, begin + width); }

        bool isEqual(const row_iterator &other, int count) const {
            return std::equal(begin, begin + count, other.begin); }
        bool isEqual(const row_iterator &other, int index, int count) {
            return std::equal(begin + index, begin + count, other.begin + index); }

        const QVariant &operator[] (int column) const { return *(begin + column); }

        QVector<QVariant>::iterator begin;
        int width;
        mutable Row row;
    };

    struct const_row_iterator
    {
        const_row_iterator() {}
        const_row_iterator(QVector<QVariant>::const_iterator begin, int width)
            : begin(begin), width(width) {}

        bool operator != (const const_row_iterator &other) const { return begin != other.begin; }
        bool operator <(const const_row_iterator &other) const { return begin < other.begin; }

        const_row_iterator &operator ++() { begin += width; return *this; }
        const_row_iterator operator --(int) {
            const_row_iterator n(*this); begin -= width; return n; }

        int operator -(const const_row_iterator &other) const {
            return (begin - other.begin) / width; }
        int operator -(const QVector<QVariant>::const_iterator &iterator) const {
            return (begin - iterator) / width; }

        const_row_iterator operator +(int span) const {
            return const_row_iterator(begin + (span * width), width); }

        const_row_iterator &operator +=(int span) { begin += span * width; return *this; }

        bool isEqual(const const_row_iterator &other, int count) const {
            return std::equal(begin, begin + count, other.begin); }
        bool isEqual(const const_row_iterator &other, int index, int count) {
            return std::equal(begin + index, begin + count, other.begin + index); }

        QVector<QVariant>::const_iterator begin;
        int width;
    };

    struct Cache
    {
        Cache() : count(0), cutoff(0) {}

        int count;
        union
        {
            int offset;
            int cutoff;
        };
        QVector<QVariant> values;
    };

    enum Flag
    {
        Cancelled       = 0x01,
        Live            = 0x02,
        Refresh         = 0x04,
        UpdateRequested = 0x10,
        Active          = 0x20,
        SyncFinished    = 0x40
    };

    Q_DECLARE_FLAGS(Flags, Flag)

    QGalleryTrackerResultSetPrivate(
            TrackerSparqlConnection *connection,
            QGalleryTrackerResultSetArguments *arguments,
            bool autoUpdate)
        : connection(connection)
        , m_service( arguments->service )
        , idColumn(arguments->idColumn.take())
        , urlColumn(arguments->urlColumn.take())
        , typeColumn(arguments->typeColumn.take())
        , updateMask(arguments->updateMask)
        , identityWidth(arguments->identityWidth)
        , tableWidth(arguments->tableWidth)
        , valueOffset(arguments->valueOffset)
        , compositeOffset(arguments->compositeOffset)
        , aliasOffset(compositeOffset + arguments->compositeColumns.count())
        , columnCount(aliasOffset + arguments->aliasColumns.count())
        , currentRow(0)
        , currentIndex(-1)
        , rowCount(0)
        , progressMaximum(0)
        , queryError(QDocumentGallery::NoError)
        , sparql(arguments->sparql)
        , propertyNames(arguments->propertyNames)
        , propertyAttributes(arguments->propertyAttributes)
        , propertyTypes(arguments->propertyTypes)
        , valueColumns(arguments->valueColumns)
        , compositeColumns(arguments->compositeColumns)
        , aliasColumns(arguments->aliasColumns)
        , resourceKeys(arguments->resourceKeys)
        , parserThread(this)
    {
        arguments->clear();

        if (autoUpdate)
            flags |= Live;
    }

    ~QGalleryTrackerResultSetPrivate()
    {
        qDeleteAll(valueColumns);
        qDeleteAll(compositeColumns);
    }

    TrackerSparqlConnection *connection;

    QString m_service;

    Flags flags;
    const QScopedPointer<QGalleryTrackerCompositeColumn> idColumn;
    const QScopedPointer<QGalleryTrackerCompositeColumn> urlColumn;
    const QScopedPointer<QGalleryTrackerCompositeColumn> typeColumn;

    const int updateMask;
    const int identityWidth;
    const int tableWidth;
    const int valueOffset;
    const int compositeOffset;
    const int aliasOffset;
    const int columnCount;
    QVector<QVariant>::const_iterator currentRow;
    int currentIndex;
    int rowCount;
    int progressMaximum;
    int queryError;
    QString queryErrorString;
    const QString sparql;
    const QStringList propertyNames;
    const QList<int> propertyKeys;
    const QVector<QGalleryProperty::Attributes> propertyAttributes;
    const QVector<QVariant::Type> propertyTypes;
    const QVector<QGalleryTrackerValueColumn *> valueColumns;
    const QVector<QGalleryTrackerCompositeColumn *> compositeColumns;
    const QVector<int> aliasColumns;
    const QVector<int> resourceKeys;
    Cache rCache;   // Remove cache.
    Cache iCache;   // Insert cache.

    QGalleryTrackerResultSetThread parserThread;
    QList<QGalleryTrackerMetaDataEdit *> edits;
    QBasicTimer updateTimer;
    SyncEventQueue syncEvents;

    inline int rCacheIndex(const const_row_iterator &iterator) const {
        return iterator - rCache.values.begin(); }
    inline int iCacheIndex(const const_row_iterator &iterator) const {
        return iterator - iCache.values.begin(); }

    void update();
    void requestUpdate()
    {
        if (!(flags & UpdateRequested)) {
            flags |= UpdateRequested;
            QCoreApplication::postEvent(q_func(), new QEvent(QEvent::UpdateRequest));
        }
    }

    void query();

    void run();

    void synchronize();

    void postSyncEvent(SyncEvent *event)
    {
        if (syncEvents.enqueue(event))
            QCoreApplication::postEvent(q_func(), new QEvent(QEvent::UpdateLater));
    }

    void processSyncEvents();
    void removeItems(const int rIndex, const int iIndex, const int count);
    void insertItems(const int rIndex, const int iIndex, const int count);
    void syncUpdate(const int aIndex, const int aCount, const int iIndex, const int iCount);
    void syncReplace(const int aIndex, const int aCount, const int iIndex, const int iCount);
    void syncFinish(const int aIndex, const int iIndex);
    bool waitForSyncFinish(int msecs);

    void _q_queryFinished(QDBusPendingCallWatcher *watcher);
    void _q_parseFinished();
    void _q_editFinished(QGalleryTrackerMetaDataEdit *edit);
};

QT_END_NAMESPACE_DOCGALLERY

template <> inline void qSwap<QT_DOCGALLERY_PREPEND_NAMESPACE(QGalleryTrackerResultSetPrivate::Row)>(
        QT_DOCGALLERY_PREPEND_NAMESPACE(QGalleryTrackerResultSetPrivate::Row) &row1,
        QT_DOCGALLERY_PREPEND_NAMESPACE(QGalleryTrackerResultSetPrivate::Row) &row2)
{
    typedef QVector<QVariant>::iterator iterator;

    for (iterator it1 = row1.begin, it2 = row2.begin; it1 != row1.end; ++it1, ++it2)
        qSwap(*it1, *it2);
}

#endif

Q_DECLARE_OPERATORS_FOR_FLAGS(QT_DOCGALLERY_PREPEND_NAMESPACE(QGalleryTrackerResultSetPrivate::Flags))

