#include "AppInfo.h"

#include "En.h"
#include "Zh.h"
#include <QDebug>
#include <QLocale>
#include <QQmlContext>
#include <QtGlobal>

AppInfo::AppInfo(QObject* parent) : QObject{parent} {
    version("v1.0.1208-beta");
    if (QLocale::system().language() == QLocale::Chinese)
        lang(new Zh());
    else
        lang(new En());
}

void AppInfo::init(QQmlApplicationEngine* engine) {
    QQmlContext* context = engine->rootContext();
    Lang* lang = this->lang();
    context->setContextProperty("lang", lang);
    QObject::connect(this, &AppInfo::langChanged, this,
                     [=] { context->setContextProperty("lang", this->lang()); });
    context->setContextProperty("appInfo", this);
}

void AppInfo::changeLang(const QString& locale) {
    if (_lang) {
        _lang->deleteLater();
    }
    if (locale == "Zh") {
        lang(new Zh());
    } else if (locale == "En") {
        lang(new En());
    } else {
        lang(new En());
    }
}
