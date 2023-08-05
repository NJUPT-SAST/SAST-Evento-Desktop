#ifndef EVENTOEDIT_H
#define EVENTOEDIT_H

#include <QObject>

class EventoEdit
{
    Q_OBJECT

public:
    using EventoID = QString;
    enum EditMode{
        Edit = 0,
        Create = 1
    };

    static EventoEdit* getInstance();

public slots:
    void onCreate();
    void onSave();
    void onRemove();
    void onGenerateQR(QString);
private:
    EventoEdit(){};
    ~EventoEdit(){};
    EventoEdit(const EventoEdit&);
    EventoEdit &operator=(const EventoEdit&);

};

#endif // EVENTOEDIT_H
