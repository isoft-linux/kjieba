/*
 * Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 * Copyright 2014 Marco Martin <mart@kde.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "daemon.h"

#include <QApplication>
#include <QDebug>

#include <KLocalizedString>

#include "appadaptor.h"

#include "include/Application.hpp"

Daemon::Daemon(QObject *parent)
    : QObject(parent)
{
    new AppAdaptor(this);
    QDBusConnection::sessionBus().registerObject(QLatin1String("/App"), this);
}

Daemon::~Daemon()
{
}

void Daemon::query(const QString &term)
{
    emit finished(term);
}

#include "moc_daemon.cpp"
