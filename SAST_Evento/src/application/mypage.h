#ifndef MYPAGE_H
#define MYPAGE_H

#include <QObject>

class EventoHistory;

class MyPage
{

    Q_OBJECT

public:
    using EventoID = QString;

    enum class EventoState {
        Before,
        Registration,
        Undertaking,
        Cancelled,
        Over
    };

    enum class CheckState {
        Disabled,
        Checked,
        Expired,
        Unchecked,
        Scene
    };

    static MyPage* getInstance();

public slots:
    void onHistory();
    void onClickSouvenirs();
    void onClickProfile();
private:
    MyPage(){};
    ~MyPage(){};
    MyPage(const MyPage&);
    MyPage &operator=(const MyPage&);

    EventoHistory* m_eventoHistory;

};

#endif // MYPAGE_H
