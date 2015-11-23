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

#include "sds.h"
#include "functions.h"

Daemon::Daemon(QObject *parent)
    : QObject(parent)
{
    m_app = new CppJieba::Application(LIBCPPJIEBAR_DICT_DIR + std::string("/jieba.dict.utf8"), 
                                      LIBCPPJIEBAR_DICT_DIR + std::string("/hmm_model.utf8"), 
                                      LIBCPPJIEBAR_DICT_DIR + std::string("/user.dict.utf8"), 
                                      LIBCPPJIEBAR_DICT_DIR + std::string("/idf.utf8"), 
                                      LIBCPPJIEBAR_DICT_DIR + std::string("/stop_words.utf8"));
    
    m_fp = fopen(CHINESE2PINYIN_DIR "/PinyinData.txt", "r");
    if (m_fp == nullptr) 
        std::cerr << "ERROR: failed to open c2p data" << std::endl;

    new AppAdaptor(this);
    QDBusConnection::sessionBus().registerObject(QLatin1String("/App"), this);
}

Daemon::~Daemon()
{
    if (m_app) {
        delete m_app;
        m_app = nullptr;
    }

    if (m_fp) {
        fclose(m_fp);
        m_fp = nullptr;
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

void Daemon::pinyin(const QString &chinese) 
{
    m_mutex.lock();

    sds words = nullptr;
    sds out = nullptr;

    words = sdsnew(chinese.toStdString().c_str());
    int len = sdslen(words);
    if (!is_text_utf8(words, len)) {
        std::cerr << "ERROR: " << words << " is not utf8 text" << std::endl;
        goto exit;
    }

    out = sdsempty();
    if (m_fp == nullptr) {
        std::cerr << "ERROR: failed to open c2p data" << std::endl;
        goto exit;
    }
    
    utf8_to_pinyin(words, out, m_fp);
#if DEBUG
    std::cout << "DEBUG: " << __FILE__ << " " << __PRETTY_FUNCTION__ << " " << out << std::endl;
#endif
    emit finished(QString(out));

exit:
    if (words) {
        sdsfree(words);
        words = nullptr;
    }

    if (out) {
        sdsfree(out);
        out = nullptr;
    }

    m_mutex.unlock();
}

#include "moc_daemon.cpp"
