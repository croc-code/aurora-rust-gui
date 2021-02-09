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

#ifndef QORGANIZERABSTRACTREQUEST_H
#define QORGANIZERABSTRACTREQUEST_H

#include <qorganizermanager.h>

QT_BEGIN_NAMESPACE_ORGANIZER

class QOrganizerManagerEngine;
class QOrganizerAbstractRequestPrivate;
class Q_ORGANIZER_EXPORT QOrganizerAbstractRequest : public QObject
{
    Q_OBJECT

public:
    ~QOrganizerAbstractRequest();

    enum State {
        InactiveState = 0,
        ActiveState,
        CanceledState,
        FinishedState
    };

    State state() const;
    bool isInactive() const;
    bool isActive() const;
    bool isFinished() const;
    bool isCanceled() const;

    QOrganizerManager::Error error() const;

    enum RequestType {
        InvalidRequest = 0,
        ItemOccurrenceFetchRequest,
        ItemFetchRequest,
        ItemFetchForExportRequest,
        ItemIdFetchRequest,
        ItemFetchByIdRequest,
        ItemRemoveRequest,
        ItemRemoveByIdRequest,
        ItemSaveRequest,
        CollectionFetchRequest,
        CollectionRemoveRequest,
        CollectionSaveRequest
    };

    RequestType type() const;

    QOrganizerManager* manager() const;
    void setManager(QOrganizerManager *manager);

public Q_SLOTS:
    bool start();
    bool cancel();
    bool waitForFinished(int msecs = 0);

Q_SIGNALS:
    void stateChanged(QOrganizerAbstractRequest::State newState);
    void resultsAvailable();

protected:
    QOrganizerAbstractRequest(QOrganizerAbstractRequestPrivate *other, QObject *parent = 0);
    QOrganizerAbstractRequestPrivate *d_ptr;

private:
    QOrganizerAbstractRequest(QObject *parent = 0) : QObject(parent), d_ptr(0) {}
    Q_DISABLE_COPY(QOrganizerAbstractRequest)
    friend class QOrganizerManagerEngine;
    friend class QOrganizerAbstractRequestPrivate;

#ifndef QT_NO_DEBUG_STREAM
    friend Q_ORGANIZER_EXPORT QDebug operator<<(QDebug dbg, const QOrganizerAbstractRequest &request);
#endif
};

QT_END_NAMESPACE_ORGANIZER

#endif // QORGANIZERABSTRACTREQUEST_H
