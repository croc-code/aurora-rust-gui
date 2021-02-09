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

#ifndef QORGANIZERITEMDETAILFIELDFILTER_P_H
#define QORGANIZERITEMDETAILFIELDFILTER_P_H

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

#include "qorganizeritemfilter_p.h"
#include <qorganizeritemdetailfilter.h>

QT_BEGIN_NAMESPACE_ORGANIZER

class QOrganizerItemDetailFieldFilterPrivate : public QOrganizerItemFilterPrivate
{
public:
    QOrganizerItemDetailFieldFilterPrivate()
        : QOrganizerItemFilterPrivate(), m_detailType(QOrganizerItemDetail::TypeUndefined), m_detailField(-1), m_flags(0)
    {
    }

    QOrganizerItemDetailFieldFilterPrivate(const QOrganizerItemDetailFieldFilterPrivate& other)
        : QOrganizerItemFilterPrivate(other), m_detailType(other.m_detailType), m_detailField(other.m_detailField),
          m_exactValue(other.m_exactValue), m_flags(other.m_flags)
    {
    }

    virtual bool compare(const QOrganizerItemFilterPrivate *other) const
    {
        const QOrganizerItemDetailFieldFilterPrivate *od = static_cast<const QOrganizerItemDetailFieldFilterPrivate *>(other);
        if (od) {
            return (m_detailType == od->m_detailType) && (m_detailField == od->m_detailField)
                   && (m_exactValue == od->m_exactValue) && (m_flags == od->m_flags);
        }
        return false;
    }

#ifndef QT_NO_DATASTREAM
    QDataStream &outputToStream(QDataStream &stream, quint8 formatVersion) const
    {
        if (formatVersion == 1)
            stream << m_detailType << m_detailField << m_exactValue << static_cast<quint32>(m_flags);
        return stream;
    }

    QDataStream &inputFromStream(QDataStream &stream, quint8 formatVersion)
    {
        if (formatVersion == 1) {
            quint32 flags;
            quint32 defId;
            stream >> defId >> m_detailField >> m_exactValue >> flags;
            m_detailType = static_cast<QOrganizerItemDetail::DetailType>(defId);
            m_flags = static_cast<QOrganizerItemFilter::MatchFlags>(flags);
        }
        return stream;
    }
#endif // QT_NO_DATASTREAM

#ifndef QT_NO_DEBUG_STREAM
    QDebug &debugStreamOut(QDebug &dbg) const
    {
        dbg.nospace() << "QOrganizerItemDetailFieldFilter(";
        dbg.nospace() << "detailType=";
        dbg.nospace() << m_detailType;
        dbg.nospace() << ",";
        dbg.nospace() << "detailField=";
        dbg.nospace() << m_detailField;
        dbg.nospace() << ",";
        dbg.nospace() << "value=";
        dbg.nospace() << m_exactValue;
        dbg.nospace() << ",";
        dbg.nospace() << "matchFlags=";
        dbg.nospace() << static_cast<quint32>(m_flags);
        dbg.nospace() << ")";
        return dbg.maybeSpace();
    }
#endif // QT_NO_DEBUG_STREAM

    Q_IMPLEMENT_ORGANIZERITEMFILTER_VIRTUALCTORS(QOrganizerItemDetailFieldFilter, QOrganizerItemFilter::DetailFieldFilter)

    QOrganizerItemDetail::DetailType m_detailType;
    int m_detailField;
    QVariant m_exactValue;
    QOrganizerItemFilter::MatchFlags m_flags;
};

QT_END_NAMESPACE_ORGANIZER

#endif // QORGANIZERITEMDETAILFIELDFILTER_P_H
