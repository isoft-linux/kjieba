/*
 *   Copyright (C) 2016 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License version 2 as
 *   published by the Free Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef KJIEBARUNNER_H
#define KJIEBARUNNER_H

#include <krunner/abstractrunner.h>

#include <KJieba/KJieba_Interface>

#include <QScopedPointer>

using namespace KJieba;

class KJiebaRunner : public Plasma::AbstractRunner
{
    Q_OBJECT

public:
    explicit KJiebaRunner(QObject *parent, const QVariantList &args);
    ~KJiebaRunner();

    void match(Plasma::RunnerContext &context);
    void run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &action);
    virtual QStringList categories() const;
    virtual QIcon categoryIcon(const QString& category) const;

protected Q_SLOTS:
    QMimeData *mimeDataForMatch(const Plasma::QueryMatch &match);

private:
    QScopedPointer<KJiebaInterface> kjiebaPtr;
};

#endif  // KJIEBARUNNER_H
