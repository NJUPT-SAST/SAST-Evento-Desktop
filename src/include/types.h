#ifndef EVENTO_TYPES_H
#define EVENTO_TYPES_H

#include <QString>
#include <QDateTime>
#include <vector>

using UserID = QString;
using EventoID = QString;
using Image = QString;
using Location = QStringList;
using Tag = QStringList;

class ParticipationStatus {
    bool isRegistrated;
    bool isParticipated;
    bool isSubscribed;
};

enum class EventState {
    Before,
    Registration,
    Undertaking,
    Cancelled,
    Over
};

class EventType {
    int id;
    QString name;
    bool allowConflict;
};

class Department {
    int id;
    QString name;
};

#endif // EVENTO_TYPES_H
