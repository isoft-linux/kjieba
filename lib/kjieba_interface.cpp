/****************************************************************************
 *
 * Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 * Copyright (C) 2012-2015 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:LGPL2.1+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QtCore/QDebug>
#include <QtDBus/QDBusPendingCallWatcher>

#include "kjieba_interface.h"
#include "kjieba_interface_p.h"

namespace KJieba {

/*
 * KJiebaInterfacePrivate
 */

KJiebaInterfacePrivate::KJiebaInterfacePrivate(const QDBusConnection &bus)
{
    interface = new OrgIsoftlinuxKjiebaAppInterface(
        QStringLiteral("org.isoftlinux.kjieba"),
        QStringLiteral("/org/isoftlinux/kjieba"),
        bus);
}

KJiebaInterfacePrivate::~KJiebaInterfacePrivate()
{
    delete interface;
}

void KJiebaInterfacePrivate::_q_finished(const QString &words)
{
    Q_Q(KJiebaInterface);
    Q_EMIT q->finished(words);
}

KJiebaInterface::KJiebaInterface(const QDBusConnection &bus)
    : d_ptr(new KJiebaInterfacePrivate(bus))
{
    d_ptr->q_ptr = this;

    connect(d_ptr->interface, SIGNAL(finished(const QString &)),
            this, SLOT(_q_finished(const QString &)));
}

KJiebaInterface::~KJiebaInterface()
{
    delete d_ptr;
}

void KJiebaInterface::query(const QString &term)
{
    Q_D(KJiebaInterface);
    d->interface->query(term);
}

}

#include "moc_kjieba_interface.cpp"
