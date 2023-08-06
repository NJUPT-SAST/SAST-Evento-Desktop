#ifndef MYPAGE_H
#define MYPAGE_H

#include <QObject>

class EventoHistory;

class MyPage
{

    Q_OBJECT

public:
    static MyPage* getInstance();

    ~MyPage() = default;

public slots:
    void onHistory();
    void onClickSouvenirs();
    void onClickProfile();

private:
    MyPage(){};

    EventoHistory* m_eventoHistory;

};

#endif // MYPAGE_H
