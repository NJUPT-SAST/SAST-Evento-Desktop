#ifndef EVENTOEDIT_H
#define EVENTOEDIT_H

#include <QObject>

class EventoEdit : public QObject
{
    Q_OBJECT

public:
    enum EditMode{
        Edit = 0,
        Create = 1
    };

    static EventoEdit* getInstance();

    ~EventoEdit() = default;

public slots:
    void onCreate();
    void onSave();
    void onRemove();
    void onGenerateQR(QString);
private:
    EventoEdit(){};

};

#endif // EVENTOEDIT_H
