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

#ifndef DAEMON_H
#define DAEMON_H

#include <QObject>

#include "pinyin.h"

#include "include/Application.hpp"

class Daemon : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.isoftlinux.kjieba.App")

public:
    explicit Daemon(QObject *parent = nullptr);
    virtual ~Daemon();

public Q_SLOTS:
    QString query(const QString &term, int method);
    QString topinyin(const QString &chinese, bool initial_letter);

private:
    CppJieba::Application *m_app = nullptr;
    PinYinInit *m_pinyin = nullptr;
};

#endif // DAEMON_H
