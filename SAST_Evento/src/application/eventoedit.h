#ifndef EVENTOEDIT_H
#define EVENTOEDIT_H

#include <QObject>

class EventoEdit
{
    Q_OBJECT

public:
    enum EditMode{
        Edit = 0,
        Create = 1
    };

    static EventoEdit* getInstance();

public slots:
    void onCreate();
    void onSave();
    void onRemove();
private:
<<<<<<< HEAD
    static std::mutex m_mutex;

    EventoEdit(){};
    ~EventoEdit(){};
    EventoEdit(const EventoEdit&);
    EventoEdit &operator=(const EventoEdit&);
=======
    EventoEdit();
>>>>>>> 3bfb64fcdf3908b652e3f7c0bba0156365ab0447
};

#endif // EVENTOEDIT_H
