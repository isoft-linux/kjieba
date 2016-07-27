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

#include "kjiebarunner.h"

#include <QMimeData>
#include <QIcon>
#include <QDebug>
#include <QUrl>

#include <KLocalizedString>
#include <KActivities/ResourceInstance>
#include <KRun>
#include <KService>
#include <KServiceTypeTrader>

KJiebaRunner::KJiebaRunner(QObject *parent, const QVariantList &args)
    : Plasma::AbstractRunner(parent, args)
{
    Q_UNUSED(args)

    kjieba = new KJiebaInterface;

    setObjectName(QLatin1String("KJieba"));
    setPriority(AbstractRunner::HighestPriority);

    addSyntax(Plasma::RunnerSyntax(":q:", i18n("Find App matches :q:")));
}

KJiebaRunner::~KJiebaRunner()
{
    if (kjieba) {
        delete kjieba;
        kjieba = nullptr;
    }
}

QStringList KJiebaRunner::categories() const
{
    QStringList cat;
    cat << i18n("KJieba");

    return cat;
}

QIcon KJiebaRunner::categoryIcon(const QString& category) const
{
    if (category == i18n("KJieba"))
        return QIcon::fromTheme("applications-internet");

    return Plasma::AbstractRunner::categoryIcon(category);
}


void KJiebaRunner::match(Plasma::RunnerContext &context)
{
    const QString term = context.query();
    QList<Plasma::QueryMatch> matches;
    QSet<QString> seen;

    if (term.length() > 1) {
#if DEBUG
        qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << term;
#endif
        KService::List services = KServiceTypeTrader::self()->query("Application");
        KService::List::iterator it = services.begin();
        while (it != services.end()) {
            if ((*it)->exec().isEmpty() ||
                (!kjieba->query((*it)->genericName()).contains(term)            &&
                 !kjieba->topinyin((*it)->genericName()).contains(term)         &&
                 !kjieba->topinyin((*it)->genericName(), false).contains(term)  &&
                 !kjieba->query((*it)->name()).contains(term)                   &&
                 !kjieba->topinyin((*it)->name()).contains(term)                &&
                 !kjieba->topinyin((*it)->name(), false).contains(term))) {
                it = services.erase(it);
            } else {
                ++it;
            }
        }

		if (!services.isEmpty()) {
            Q_FOREACH (const KService::Ptr &service, services) {
                if (!service->noDisplay() && service->property(QStringLiteral("NotShowIn"), QVariant::String) != "KDE") {
                    Plasma::QueryMatch match(this);
                    match.setType(Plasma::QueryMatch::ExactMatch);

					const QString name = service->name();
#if DEBUG
                    qDebug() << "DEBUG:" << name;
#endif
                    match.setText(name);
                    match.setData(service->storageId());

                    if (!service->genericName().isEmpty() && service->genericName() != name)
                        match.setSubtext(service->genericName());
                    else if (!service->comment().isEmpty())
                        match.setSubtext(service->comment());
                   
                    if (!service->icon().isEmpty())
                        match.setIcon(QIcon::fromTheme(service->icon()));

                    match.setRelevance(1);
                    matches << match;
                    seen.insert(service->storageId());
                    seen.insert(service->exec());
                }
            }
        }
    }

    if (context.isValid())
        context.addMatches(matches);
}

void KJiebaRunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context);
	if (match.type() == Plasma::QueryMatch::HelperMatch) { // Jump List Action
         KRun::run(match.data().toString(), {}, nullptr);
         return;
    }

    KService::Ptr service = KService::serviceByStorageId(match.data().toString());
    if (service) {
        KActivities::ResourceInstance::notifyAccessed(
            QUrl(QStringLiteral("applications:") + service->storageId()),
            QStringLiteral("org.kde.krunner")
        );

        KRun::runService(*service, {}, nullptr, true);
    }
}

QMimeData *KJiebaRunner::mimeDataForMatch(const Plasma::QueryMatch &match) 
{
    QMimeData *result = new QMimeData();
    QList<QUrl> urls;
    urls << QUrl("kjieba://" + match.data().toString());
    result->setUrls(urls);
    return result;
}

K_EXPORT_PLASMA_RUNNER(kjieba, KJiebaRunner)

#include "kjiebarunner.moc"

