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

#include "kjieba_interface.h"
#include "kjieba_interface_p.h"

#include <iostream>

namespace KJieba {

KJiebaInterfacePrivate::KJiebaInterfacePrivate(const QDBusConnection &bus)
{
    interface = new OrgIsoftlinuxKjiebaAppInterface(
        QStringLiteral("org.isoftlinux.kjieba"),
        QStringLiteral("/App"),
        bus);
}

KJiebaInterfacePrivate::~KJiebaInterfacePrivate()
{
    delete interface;
}

KJiebaInterface::KJiebaInterface(const QDBusConnection &bus)
    : d_ptr(new KJiebaInterfacePrivate(bus))
{
    d_ptr->q_ptr = this;
}

KJiebaInterface::~KJiebaInterface()
{
    delete d_ptr;
}

QStringList KJiebaInterface::query(const QString &term, CutMethod method)
{
    Q_D(KJiebaInterface);

    QString words = "";
    QDBusPendingReply<QString> reply = d->interface->query(term, int(method));
    reply.waitForFinished();

    if (reply.isError()) {
        std::cerr << "ERROR: failed to query" << std::endl;
    } else {
        words = reply.argumentAt<0>();
    }

    return words.split("/");
}

QString KJiebaInterface::topinyin(const QString &chinese, PinyinInit init) 
{
    Q_D(KJiebaInterface);

    QString pinyin = "";
    QDBusPendingReply<QString> reply = d->interface->topinyin(chinese, int(init));
    reply.waitForFinished();

    if (reply.isError()) {
        std::cerr << "ERROR: failed topinyin" << std::endl;
    } else {
        pinyin = reply.argumentAt<0>();
    }

    return pinyin;
}

}

#include "moc_kjieba_interface.cpp"
