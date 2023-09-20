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
    void loadMyPageErrorEvent(QString message);

private:
    MyPageController() = default;
public:
    void onLoadFinished() {
        emit loadMyPageSuccessEvent();
    }
    void onLoadFailure(const QString& message) {
        emit loadMyPageErrorEvent(message);
    }

    static MyPageController* getInstance();
    static MyPageController* create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
};

#endif // MYPAGECONTROLLER_H
