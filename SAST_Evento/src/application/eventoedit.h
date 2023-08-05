#ifndef EVENTOEDIT_H
#define EVENTOEDIT_H

#include <QObject>
#include <mutex>

class EventoEdit
{
    //Q_OBJECT
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
    static std::mutex m_mutex;

    EventoEdit(){};
    ~EventoEdit(){};
    EventoEdit(const EventoEdit&);
    EventoEdit &operator=(const EventoEdit&);
};

#endif // EVENTOEDIT_H
