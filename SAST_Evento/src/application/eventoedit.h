#ifndef EVENTOEDIT_H
#define EVENTOEDIT_H

#include <QObject>

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
    EventoEdit();
};

#endif // EVENTOEDIT_H
