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

    Evento evento(int eventId) override;

    Image image(int eventId) override;

    Feedback feedback(int eventId) override;

    User user() override;

    std::vector<Department> departmentModel() override;

    std::vector<LatestEvento> latestEventoModel() override;

    std::vector<UndertakingEvento> undertakingEventoModel() override;

    std::vector<Slide> slideModel() override;

    std::vector<Image> imageModel(int eventId) override;

    std::vector<EventoBrief> historyEventoModel(const QString& userId) override;

    std::vector<EventoBrief> departmentEventoModel(int departmentId) override;

    std::vector<Schedule> scheduleModel(const QString& userId) override;

    std::vector<EventoBlock> eventoBlockModel() override;

    std::vector<Feedback> feedbackModel(int eventId) override;

    std::vector<PermissionEntry> permissionModel() override;

    std::vector<UserBrief> userbriefModel(const QString& userId) override;

public:
    explicit RepositoryImpl(QObject* parent = nullptr);
};

#endif  // REPOSITORYIMPL_H
