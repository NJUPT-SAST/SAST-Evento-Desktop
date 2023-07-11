#ifndef APPINFO_H
#define APPINFO_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "tool/IPC.h"
#include "lang/Lang.h"
#include "stdafx.h"
#include "identity/Identity.h"

class AppInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY_AUTO(QString,version)
    Q_PROPERTY_AUTO(Lang*,lang)
    Q_PROPERTY_AUTO(Identity*, identity)
public:
    explicit AppInfo(QObject *parent = nullptr);
    void init(QQmlApplicationEngine *engine);
    bool isOwnerProcess(IPC *ipc);
    Q_INVOKABLE void changeLang(const QString& locale);
    Q_INVOKABLE void changeIdentity(const QString& username, const QString& password);
    Q_SIGNAL void activeWindow();
    Q_SIGNAL void login();
};

#endif // APPINFO_H
