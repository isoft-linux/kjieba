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

#include <iostream>
#include <string>
#include <vector>

Daemon::Daemon(QObject *parent)
    : QObject(parent)
{
    m_app = new CppJieba::Application(LIBCPPJIEBAR_DICT_DIR + std::string("/jieba.dict.utf8"), 
                                      LIBCPPJIEBAR_DICT_DIR + std::string("/hmm_model.utf8"), 
                                      LIBCPPJIEBAR_DICT_DIR + std::string("/user.dict.utf8"), 
                                      LIBCPPJIEBAR_DICT_DIR + std::string("/idf.utf8"), 
                                      LIBCPPJIEBAR_DICT_DIR + std::string("/stop_words.utf8"));

    new AppAdaptor(this);
    QDBusConnection::sessionBus().registerObject(QLatin1String("/App"), this);
}

Daemon::~Daemon()
{
    if (m_app) {
        delete m_app;
        m_app = nullptr;
    }
}

void Daemon::query(const QString &term)
{
    std::vector<std::string> words;
    std::string ret;
    m_app->cut(term.toStdString(), words, CppJieba::METHOD_QUERY);
    ret = CppJieba::join(words.begin(), words.end(), "/");
#if DEBUG
    std::cout << "DEBUG: " << __FILE__ << " " << __PRETTY_FUNCTION__ << ret << std::endl;
#endif
    emit finished(QString::fromStdString(ret));
}

#include "moc_daemon.cpp"
