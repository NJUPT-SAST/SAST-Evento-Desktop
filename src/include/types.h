#ifndef EVENTO_TYPES_H
#define EVENTO_TYPES_H

#include <QDateTime>
#include <QString>

using UserID = QString;
using EventoID = int;
using EventTypeID = int;
using LocationID = int;
using Image = QString;
using Tag = QString;

struct ParticipationStatus {
    bool isRegistrated;
    bool isParticipated;
    bool isSubscribed;
};

enum class EventState : int {
    Uninitialised = 0,
    Before,
    Registration,
    Ongoing,
    Cancelled,
    Over,
};

struct EventType {
    EventTypeID id;
    QString name;
    bool allowConflict;
};

struct Department {
    int id;
    QString name;
    bool subscribed = false;
};

struct FeedbackNum {
    EventoID eventId;
    QString title;
    int feedbackCount;
};

#endif // EVENTO_TYPES_H
