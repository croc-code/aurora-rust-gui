/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtLocation module of the Qt Toolkit.
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

#ifndef QPLACEMATCHREQUEST_H
#define QPLACEMATCHREQUEST_H

#include <QtCore/QSharedDataPointer>
#include <QtLocation/QPlaceSearchResult>

QT_BEGIN_NAMESPACE

class QPlaceMatchRequestPrivate;

class Q_LOCATION_EXPORT QPlaceMatchRequest
{
public:
    static const QString AlternativeId;

    QPlaceMatchRequest();
    QPlaceMatchRequest(const QPlaceMatchRequest &other);


    QPlaceMatchRequest &operator=(const QPlaceMatchRequest &other);

    bool operator==(const QPlaceMatchRequest &other) const;
    bool operator!=(const QPlaceMatchRequest &other) const;

    ~QPlaceMatchRequest();

    QList<QPlace> places() const;
    void setPlaces(const QList<QPlace> places);

    void setResults(const QList<QPlaceSearchResult> &results);

    QVariantMap parameters() const;
    void setParameters(const QVariantMap &parameters);

    void clear();

private:
    QSharedDataPointer<QPlaceMatchRequestPrivate> d_ptr;
    inline QPlaceMatchRequestPrivate *d_func();
    inline const QPlaceMatchRequestPrivate *d_func() const;
};

QT_END_NAMESPACE

#endif
