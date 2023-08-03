#include "AppInfo.h"

#include <QDebug>
#include <QQmlContext>

#include "src/lang/En.h"
#include "src/lang/Zh.h"

#define STR(x) #x
#define VER_JOIN(a, b, c, d) STR(a.b.c.d)
#define VER_JOIN_(x) VER_JOIN x
#define VER_STR VER_JOIN_((VERSION))

AppInfo::AppInfo(QObject *parent) : QObject{parent} {
    version(VER_STR);
    lang(new Zh());
}

void AppInfo::init(QQmlApplicationEngine *engine) {
    QQmlContext *context = engine->rootContext();
    Lang *lang = this->lang();
    context->setContextProperty("lang", lang);
    QObject::connect(this, &AppInfo::langChanged, this, [=] {
        context->setContextProperty("lang", this->lang());
    });
    context->setContextProperty("appInfo", this);
}

void AppInfo::changeLang(const QString &locale) {
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
