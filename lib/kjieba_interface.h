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

#ifndef KJIEBA_KJIEBA_INTERFACE_H
#define KJIEBA_KJIEBA_INTERFACE_H

#include <QtCore/QObject>
#include <QtDBus/QDBusConnection>

#include <kjieba/kjieba_export.h>

namespace KJieba {

enum CutMethod {
    METHOD_MP,
    METHOD_HMM,
    METHOD_MIX,
    METHOD_FULL,
    METHOD_QUERY
};

class KJiebaInterfacePrivate;

class KJIEBA_EXPORT KJiebaInterface : public QObject
{
    Q_OBJECT
public:
    explicit KJiebaInterface(const QDBusConnection &bus = QDBusConnection::sessionBus());
    ~KJiebaInterface();

    QStringList query(const QString &term, CutMethod method = METHOD_MIX);
    
    QString topinyin(const QString &chinese, bool initialLetter = true);

protected:
    KJiebaInterfacePrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(KJiebaInterface)
};

}

#endif // KJIEBA_KJIEBA_INTERFACE_H
