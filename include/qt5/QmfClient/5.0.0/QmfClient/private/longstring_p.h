/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Messaging Framework.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
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

#ifndef LONGSTRING_P_H
#define LONGSTRING_P_H

#include <QString>
#include <QByteArray>
#include <QFile>
#include "qmailglobal.h"

QT_BEGIN_NAMESPACE

class QDataStream;
class QTextStream;

QT_END_NAMESPACE

class LongStringPrivate;

class QMF_EXPORT LongString
{
public:
    LongString();
    LongString(const LongString &other);
    LongString(const QByteArray &ba);
    LongString(const QString &fileName);
    virtual ~LongString();

    LongString &operator=(const LongString &);

    bool isEmpty() const;
    int length() const;

    void close();

    int indexOf(const QByteArray &ba, int from = 0) const;

    LongString mid(int i, int len = -1) const;
    LongString left(int len) const;
    LongString right(int len) const;

    // WARNING the QByteArray returned may become invalid when this LongString
    // is destroyed
    const QByteArray toQByteArray() const;

    QDataStream* dataStream() const;
    QTextStream* textStream() const;

    template <typename Stream> void serialize(Stream &stream) const;
    template <typename Stream> void deserialize(Stream &stream);

private:
    LongStringPrivate* d;
};

template <typename Stream>
Stream& operator<<(Stream &stream, const LongString& ls) { ls.serialize(stream); return stream; }

template <typename Stream>
Stream& operator>>(Stream &stream, LongString& ls) { ls.deserialize(stream); return stream; }

#endif
