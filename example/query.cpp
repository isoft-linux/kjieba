/****************************************************************************
 *
 * Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 * Copyright (C) 2015 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:GPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QtCore/QCoreApplication>

#include <KJieba/KJieba_Interface>

#include <iostream>

using namespace KJieba;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    KJiebaInterface *interface = new KJiebaInterface;
    QStringList words = interface->query(argv[1] ? argv[1] : "我是中国人");
    Q_FOREACH (QString word, words)
        std::cout << word.toStdString() << std::endl;
    std::cout << interface->topinyin(argv[1] ? argv[1] : "我是中国人").toStdString() << std::endl;
    return 0;
}
