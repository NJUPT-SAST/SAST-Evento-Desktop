#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QObject>
#include <QHttpServer>
#include <QtQml/qqml.h>
#include "stdafx.h"
#include "application/service/UserService.h"
#include "controller/basecontroller.h"

using namespace QInjection;

class LoginController : public BaseController
{
    Q_OBJECT
    Q_PROPERTY_AUTO(int,loginStatus)
    QML_NAMED_ELEMENT(LoginController)
public:
    explicit LoginController(QObject* parent = nullptr);
private:
    UserService* _userService(){return QInjection::Inject;}
    QHttpServer _server;
    std::string _htmlError = R"(<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>QtHub</title>
</head>
<body>
    <h1>授权</h1>
    <p>网络异常，请刷新页面，重新授权。</p>
</body>
</html>
)";
    std::string _htmlSuccess = R"(<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>QtHub</title>
</head>
<body>
    <h1>授权</h1>
    <p>授权成功，欢迎使用QtHub。</p>
</body>
</html>
)";
};

#endif // LOGINCONTROLLER_H
