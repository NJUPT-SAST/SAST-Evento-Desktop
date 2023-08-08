#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>

#include "domain/entity/department.h"
#include "domain/entity/evento.h"
#include "domain/entity/eventoblock.h"
#include "domain/entity/eventobrief.h"
#include "domain/entity/feedback.h"
#include "domain/entity/latestevento.h"
#include "domain/entity/permissionentry.h"
#include "domain/entity/schedule.h"
#include "domain/entity/slide.h"
#include "domain/entity/undertakingevento.h"
#include "domain/entity/userbrief.h"
#include "domain/entity/image.h"

class Repository : public QObject
{
    Q_OBJECT

public:
    explicit Repository(QObject* parent = nullptr);

    QString api(const QString& path){
        return "https://" + path;
    }

    QString html(const QString& path){
        return "https://" + path;
    }

    virtual QString accessToken(const QString& id, const QString& psw) = 0;

    virtual PermissionEntry permissionEntry();

    virtual Evento evento(int eventId) = 0;

    virtual Image image(int eventId) = 0;

    virtual std::vector<Department> departmentModel() = 0;

    virtual std::vector<LatestEvento> latestEventoModel() = 0;

    virtual std::vector<UndertakingEvento> undertakingEventoModel() = 0;

    virtual std::vector<Slide> slideModel() = 0;

    virtual std::vector<Image> imageModel(int eventId) = 0;

    virtual std::vector<EventoBrief> historyEventoModel(const QString& userId) = 0;

    virtual std::vector<EventoBrief> departmentEventoModel(int departmentId) = 0;

    virtual std::vector<Schedule> scheduleModel(const QString& userId) = 0;

    virtual std::vector<EventoBlock> eventoBlockModel() = 0;

    virtual std::vector<Feedback> feedbackModel(int eventId) = 0;

    virtual std::vector<PermissionEntry> permissionModel() = 0;

    virtual std::vector<UserBrief> userbriefModel(const QString& userId) = 0;
};

#endif  // REPOSITORY_H
