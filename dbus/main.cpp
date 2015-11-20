/*
 * Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 * Copyright 2012 Marco Martin <mart@kde.org>
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

#include <QApplication>
#include <KLocalizedString>

#include <qcommandlineparser.h>
#include <qcommandlineoption.h>
#include <QDebug>
#include <QSessionManager>

#include <kdbusservice.h>

#include "daemon.h"

static QCommandLineParser parser;

int main(int argc, char *argv[])
{
    KLocalizedString::setApplicationDomain("kjieba");

    QApplication app(argc, argv);
    app.setApplicationName("kjieba");
    app.setOrganizationDomain("isoftlinux.org");
    app.setApplicationVersion(PROJECT_VERSION);
    app.setQuitOnLastWindowClosed(false);
    parser.setApplicationDescription(i18n("libcppjieba interface"));
    KDBusService service(KDBusService::Unique);

    parser.addVersionOption();
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(app);

    auto disableSessionManagement = [](QSessionManager &sm) {
        sm.setRestartHint(QSessionManager::RestartNever);
    };
    QObject::connect(&app, &QGuiApplication::commitDataRequest, disableSessionManagement);
    QObject::connect(&app, &QGuiApplication::saveStateRequest, disableSessionManagement);

    Daemon daemon;

    return app.exec();
}
