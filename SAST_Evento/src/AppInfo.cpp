#include "AppInfo.h"

#include <QDebug>
#include <QQmlContext>

#include "lang/En.h"
#include "lang/Zh.h"

#define STR(x) #x
#define VER_JOIN(a, b, c, d) STR(a.b.c.d)
#define VER_JOIN_(x) VER_JOIN x
#define VER_STR VER_JOIN_((VERSION))

AppInfo::AppInfo(QObject *parent) : QObject{parent} {
    version(VER_STR);
    lang(new Zh());
    identity(new Identity("", ""));
}

void AppInfo::init(QQmlApplicationEngine *engine) {
    QQmlContext *context = engine->rootContext();
    Lang *lang = this->lang();
    Identity *identity = this->identity();
    context->setContextProperty("lang", lang);
    context->setContextProperty("identity", identity);
    QObject::connect(this, &AppInfo::langChanged, this, [=] {
        context->setContextProperty("lang", this->lang());
    });
    QObject::connect(this, &AppInfo::identityChanged, this, [=] {
        context->setContextProperty("identity", this->identity());
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

void AppInfo::changeIdentity(const QString &username, const QString &password) {
    if (_identity) {
        _identity->deleteLater();
    }
    identity(new Identity(username, password));
    Q_EMIT this->login();
}
