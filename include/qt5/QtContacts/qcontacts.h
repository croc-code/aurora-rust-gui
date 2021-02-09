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

#ifndef QTCONTACTS_H
#define QTCONTACTS_H

// this file includes all of the public header files
// provided by the Qt Contacts API

#include <qcontactsglobal.h>                    // global exports
#include <qcontactmanager.h>                    // manager
#include <qcontactmanagerengine.h>              // manager backend
#include <qcontactmanagerenginefactory.h>       // manage backend instantiator
#include <qcontact.h>                           // contact
#include <qcontactid.h>                         // contact identifier
#include <qcontactobserver.h>                   // contact observer
#include <qcontactdetail.h>                     // contact detail
#include <qcontactdetails.h>                    // leaf detail classes
#include <qcontactfetchhint.h>                  // backend optimization hint class
#include <qcontactfilter.h>                     // contact filter
#include <qcontactfilters.h>                    // leaf filter classes
#include <qcontactsortorder.h>                  // contact sorting
#include <qcontactaction.h>                     // actions
#include <qcontactactiondescriptor.h>           // action descriptors
#include <qcontactactionfactory.h>              // action factory
#include <qcontactactiontarget.h>               // action target (contact + detail(s))
#include <qcontactabstractrequest.h>            // asynchronous request
#include <qcontactrequests.h>                   // request leaf classes
#include <qcontactrelationship.h>               // contact relationships

QT_BEGIN_NAMESPACE_CONTACTS
QT_END_NAMESPACE_CONTACTS

#endif
