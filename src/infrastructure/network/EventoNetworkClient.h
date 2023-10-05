#ifndef EVENTO_NETWORK_CLIENT_H
#define EVENTO_NETWORK_CLIENT_H

#include <QByteArray>
#include <QFuture>
#include <QJsonDocument>
#include <QJsonValue>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QUrlQuery>

#include "dto/evento.h"
#include "dto/feedback.h"
#include "dto/feedback_summary.h"
#include "dto/permission.h"
#include "dto/slide.h"
#include "dto/user.h"
#include "dto/user_brief.h"

#include "result.h"
#include "types.h"

class EventoNetworkClient {
private:
    QByteArray tokenBytes;
    QNetworkAccessManager manager;

protected:
    QUrl endpoint(const QString& endpoint);
    QUrl endpoint(const QString& endpoint, const QUrlQuery& params);

    template <typename TParamsBuilder,
              typename = std::enable_if_t<std::is_invocable_v<TParamsBuilder, QUrlQuery&>>>
    QUrl endpoint(const QString& endpoint, TParamsBuilder paramsBuilder) {
        QUrlQuery query;
        paramsBuilder(query);
        return this->endpoint(endpoint, query);
    }

    QFuture<EventoResult<QJsonValue>> get(const QUrl& url);

    QFuture<EventoResult<QJsonValue>> post(const QUrl& url, const QString& contentType,
                                           const QByteArray& requestData);
    QFuture<EventoResult<QJsonValue>> post(const QUrl& url, const QUrlQuery& requestData);
    QFuture<EventoResult<QJsonValue>> post(const QUrl& url, const QJsonDocument& requestData);

    QFuture<EventoResult<QJsonValue>> put(const QUrl& url, const QString& contentType,
                                          const QByteArray& requestData);
    QFuture<EventoResult<QJsonValue>> put(const QUrl& url, const QUrlQuery& requestData);
    QFuture<EventoResult<QJsonValue>> put(const QUrl& url, const QJsonDocument& requestData);

    QFuture<EventoResult<QJsonValue>> patch(const QUrl& url, const QString& contentType,
                                            const QByteArray& requestData);
    QFuture<EventoResult<QJsonValue>> patch(const QUrl& url, const QUrlQuery& requestData);
    QFuture<EventoResult<QJsonValue>> patch(const QUrl& url, const QJsonDocument& requestData);

    QFuture<EventoResult<QJsonValue>> deleteResource(const QUrl& url);

public:
    // userFetch
    QFuture<EventoResult<DTO_User>> loginViaSastLink(const QString& code);
    QFuture<EventoResult<QStringList>> getAdminPermission();
    QFuture<EventoResult<QStringList>> getManagerPermission(EventoID event);
    QFuture<EventoResult<QStringList>> getPermittedEvent();
    QFuture<EventoResult<DTO_Permission>> getEventPermission(EventoID event);
    QFuture<EventoResult<DTO_User>> getUserInfo(const UserID& id);
    QFuture<EventoResult<ParticipationStatus>> getUserParticipate(EventoID event);

    // eventFetch
    QFuture<EventoResult<std::vector<DTO_Evento>>> getUndertakingList();
    QFuture<EventoResult<std::vector<DTO_Evento>>> getLatestList();
    QFuture<EventoResult<std::vector<DTO_Evento>>> getRegisteredList();
    QFuture<EventoResult<std::vector<DTO_Evento>>> getSubscribedList();
    QFuture<EventoResult<std::vector<DTO_Evento>>> getHistoryList();
    QFuture<EventoResult<std::vector<DTO_Evento>>> getEventListInPage(int page, int size);
    QFuture<EventoResult<std::vector<DTO_Evento>>> getDepartmentEventList(int departmentId);
    QFuture<EventoResult<std::vector<DTO_Evento>>> getEventListByTime(const QString& time);
    QFuture<EventoResult<DTO_Evento>> getEventById(EventoID event);

    QFuture<EventoResult<std::vector<DTO_Slide>>> getSlideList();
    QFuture<EventoResult<std::vector<DTO_Slide>>> getEventSlideList(EventoID id);
    QFuture<EventoResult<std::vector<DTO_Slide>>> getHomeSlideList(int size);
    QFuture<EventoResult<std::vector<EventType>>> getTypeList();
    QFuture<EventoResult<QString>> getLocationList();
    QFuture<EventoResult<QString>> getDepartmentList();
    QFuture<EventoResult<QString>> getSubscribedDepartmentList();
    QFuture<EventoResult<QString>> getQRCode(EventoID eventId);

    // eventUpload
    QFuture<EventoResult<bool>> checkIn(EventoID event, const QString& code);
    QFuture<EventoResult<bool>> subscribeEvent(EventoID event, bool selection);
    QFuture<EventoResult<bool>> registerEvent(EventoID event, bool selection);
    QFuture<EventoResult<bool>> cancelEvent(EventoID event);
    QFuture<EventoResult<bool>> deleteEvent(EventoID event);
    QFuture<EventoResult<bool>> createEvent(const QString& title, const QString& description,
                                            const QString& eventStart, const QString& eventEnd,
                                            const QString& registerStart,
                                            const QString& registerEnd, int typeId, int locationId,
                                            const QVariantList& departmentIds, const QString& tag);
    QFuture<EventoResult<bool>> editEvent(EventoID event, const QString& title,
                                          const QString& description, const QString& eventStart,
                                          const QString& eventEnd, const QString& registerStart,
                                          const QString& registerEnd, int typeId, int locationId,
                                          const QVariantList& departmentIds, const QString& tag);
    QFuture<EventoResult<bool>> subscribeDepartment(int departmentId, bool unsubscribe);

    // feedback
    QFuture<EventoResult<std::vector<DTO_Feedback>>> getFeedbackList(EventoID eventoId);
    QFuture<EventoResult<DTO_FeedbackSummary>> getFeedbackSummary(EventoID eventoId);
    QFuture<EventoResult<std::pair<int, std::vector<FeedbackNum>>>>
        getFeedbackSummaryListInPage(int page);
    QFuture<EventoResult<int>> hasFeedbacked(EventoID event);
    QFuture<EventoResult<bool>> feedbackEvent(const DTO_Feedback& feedback);
    QFuture<EventoResult<DTO_Feedback>> getFeedbackInfo(EventoID event);

    // adminFetch
    QFuture<EventoResult<std::vector<DTO_UserBrief>>> getEventManagerList(EventoID eventoId);
    QFuture<EventoResult<std::vector<DTO_UserBrief>>> getAdminUserList();
    QFuture<EventoResult<QString>> getAdminPermissionTreeData();
    QFuture<EventoResult<QString>> getManagerPermissionTreeData();
    QFuture<EventoResult<QVariantList>> getAdminEvents(const QString& userId);

    QFuture<EventoResult<std::pair<QString, QString>>> checkUpdate();

private:
    EventoNetworkClient() = default;

public:
    static EventoNetworkClient* getInstance() {
        static EventoNetworkClient singleton;
        return &singleton;
    }
};
#endif // EVENTO_NETWORK_CLIENT_H
