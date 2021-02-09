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

#ifndef QVALUESPACE_H
#define QVALUESPACE_H

#include <qpublishsubscribeglobal.h>

#include <QtCore/qlist.h>
#include <QtCore/quuid.h>

QT_BEGIN_NAMESPACE

namespace QValueSpace {
    enum LayerOption {
        UnspecifiedLayer = 0x0000,
        PermanentLayer = 0x0001,
        TransientLayer = 0x0002,
        WritableLayer = 0x0004,
        ReadOnlyLayer = 0x0008
    };
    Q_DECLARE_FLAGS(LayerOptions, LayerOption)

    Q_PUBLISHSUBSCRIBE_EXPORT QList<QUuid> availableLayers();
}

Q_DECLARE_OPERATORS_FOR_FLAGS(QValueSpace::LayerOptions)

#define QVALUESPACE_VOLATILEREGISTRY_LAYER QUuid(0x8ceb5811, 0x4968, 0x470f, 0x8f, 0xc2, 0x26, 0x47, 0x67, 0xe0, 0xbb, 0xd9)
#define QVALUESPACE_NONVOLATILEREGISTRY_LAYER QUuid(0x8e29561c, 0xa0f0, 0x4e89, 0xba, 0x56, 0x08, 0x06, 0x64, 0xab, 0xc0, 0x17)
#define QVALUESPACE_GCONF_LAYER QUuid(0x0e2e5da0, 0x0044, 0x11df, 0x94, 0x1c, 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b)

QT_END_NAMESPACE

#endif // QVALUESPACE_H
