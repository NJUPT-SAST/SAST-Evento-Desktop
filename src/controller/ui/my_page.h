#ifndef MYPAGECONTROLLER_H
#define MYPAGECONTROLLER_H

#include <QtQml>

class MyPageController: public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(MyPageController)
    QML_SINGLETON

public:
    Q_INVOKABLE void loadMyPageInfo();

signals:
    void loadMyPageSuccessEvent();
    void loadMyPageErrorEvent(const QString message);

private:
    MyPageController() = default;
public:
    static MyPageController* getInstance();
    static MyPageController* create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // MYPAGECONTROLLER_H
