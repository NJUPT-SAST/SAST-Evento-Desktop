#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>

#include "domain/entity/evento.h"
#include "domain/entity/permissionentry.h"

#include "domain/model/slidemodel.h"
#include "domain/model/eventobriefmodel.h"
#include "domain/model/eventoblockmodel.h"
#include "domain/model/undertakingeventomodel.h"
#include "domain/model/latesteventomodel.h"
#include "domain/model/schedulemodel.h"
#include "domain/model/feedbackmodel.h"
#include "domain/model/imagemodel.h"
#include "domain/model/userbriefmodel.h"

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

    virtual Evento evento(const QString& id) = 0;

    virtual Slide slide() = 0;

    virtual LatestEventoModel latestEventoModel() = 0;

    virtual UndertakingEventoModel undertakingEventoModel() = 0;

    virtual SlideModel slideModel() = 0;

    virtual ImageModel imageModel(int eventId) = 0;

    virtual EventoBriefModel historyEventoModel(const QString& userId) = 0;

    virtual EventoBriefModel departmentEventoModel(int departmentId) = 0;

    virtual ScheduleModel scheduleModel(const QString& userId) = 0;

    virtual EventoBlockModel eventoBlockModel() = 0;

    virtual FeedbackModel feedbackModel(int eventId) = 0;

    virtual UserBriefModel userbriefModel(const QString& userId) = 0;
};

#endif  // REPOSITORY_H
