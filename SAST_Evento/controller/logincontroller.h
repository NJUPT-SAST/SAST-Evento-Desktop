#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QObject>
#include <QHttpServer>
#include <QtQml/qqml.h>
#include "stdafx.h"
#include "application/service/userservice.h"
#include "controller/basecontroller.h"

using namespace QInjection;

class LoginController : public BaseController
{
    Q_OBJECT
    Q_PROPERTY_AUTO(int,loginStatus)
    // 1: 初始页面 2：加载中 3：登录成功 4：登录失败
    QML_NAMED_ELEMENT(LoginController)

public:
    enum class Status {
        Start = 1,
        Loading,
        Success,
        Failed
    };

    explicit LoginController(QObject* parent = nullptr);
    Q_INVOKABLE void login(const QString& username, const QString& password);

private:
    UserService* m_userService() { return QInjection::Inject; }
};

#endif // LOGINCONTROLLER_H
