#ifndef REPOSITORYIMPL_H
#define REPOSITORYIMPL_H

#include <QObject>
#include "domain/repository/repository.h"

class RepositoryImpl : public Repository
{
    Q_OBJECT

private:
    template <typename T>
    void handleResult(QString result, T& data,QString type = "");

    QString accessToken(const QString& id,const QString& psw) override;

    PermissionEntry permissionEntry() override;

    Evento evento(const QString& eventId) override;

    Slide slide() override;

    LatestEventoModel latestEventoModel() override;

    UndertakingEventoModel undertakingEventoModel() override;

    SlideModel slideModel() override;

    ImageModel imageModel(int eventId) override;

    EventoBriefModel historyEventoModel(const QString& userId) override;

    EventoBriefModel departmentEventoModel(int departmentId) override;

    ScheduleModel scheduleModel(const QString& userId) override;

    EventoBlockModel eventoBlockModel() override;

    FeedbackModel feedbackModel(int eventId) override;

    UserBriefModel userbriefModel(const QString& userId) override;

public:
    explicit RepositoryImpl(QObject* parent = nullptr);
};

#endif  // REPOSITORYIMPL_H
