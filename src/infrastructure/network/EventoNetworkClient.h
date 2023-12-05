#ifndef EVENTO_NETWORK_CLIENT_H
#define EVENTO_NETWORK_CLIENT_H

#include <QByteArray>
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

#include "future.h"
#include "result.h"
#include "types.h"

#include <set>

class EventoNetworkClient {
private:
    QByteArray tokenBytes;
    QNetworkAccessManager manager;

protected:
    QUrl endpoint(const QString& endpoint);
    QUrl endpoint(const QString& endpoint, const QUrlQuery& params);

    EventoFuture<EventoResult<QJsonValue>> get(const QUrl& url);

    EventoFuture<EventoResult<QJsonValue>> post(const QUrl& url, const QString& contentType,
                                                const QByteArray& requestData);
    EventoFuture<EventoResult<QJsonValue>> post(const QUrl& url, const QUrlQuery& requestData);
    EventoFuture<EventoResult<QJsonValue>> post(const QUrl& url, const QJsonDocument& requestData);

    EventoFuture<EventoResult<QJsonValue>> put(const QUrl& url, const QString& contentType,
                                               const QByteArray& requestData);
    EventoFuture<EventoResult<QJsonValue>> put(const QUrl& url, const QUrlQuery& requestData);
    EventoFuture<EventoResult<QJsonValue>> put(const QUrl& url, const QJsonDocument& requestData);

    EventoFuture<EventoResult<QJsonValue>> patch(const QUrl& url, const QString& contentType,
                                                 const QByteArray& requestData);
    EventoFuture<EventoResult<QJsonValue>> patch(const QUrl& url, const QUrlQuery& requestData);
    EventoFuture<EventoResult<QJsonValue>> patch(const QUrl& url, const QJsonDocument& requestData);

    EventoFuture<EventoResult<QJsonValue>> deleteResource(const QUrl& url);

public:
    // userFetch
    EventoFuture<EventoResult<DTO_User>> loginViaSastLink(const QString& code);
    EventoFuture<EventoResult<QStringList>> getAdminPermission();
    EventoFuture<EventoResult<QStringList>> getManagerPermission(EventoID event);
    EventoFuture<EventoResult<QStringList>> getPermittedEvent();
    EventoFuture<EventoResult<DTO_Permission>> getEventPermission(EventoID event);
    EventoFuture<EventoResult<DTO_User>> getUserInfo(const UserID& id);
    EventoFuture<EventoResult<ParticipationStatus>> getUserParticipate(EventoID event);

    // eventFetch
    EventoFuture<EventoResult<std::vector<DTO_Evento>>> getUndertakingList();
    EventoFuture<EventoResult<std::vector<DTO_Evento>>> getLatestList();
    EventoFuture<EventoResult<std::vector<DTO_Evento>>> getRegisteredList();
    EventoFuture<EventoResult<std::vector<DTO_Evento>>> getSubscribedList();
    EventoFuture<EventoResult<std::vector<DTO_Evento>>> getHistoryList();
    EventoFuture<EventoResult<std::vector<DTO_Evento>>> getEventListInPage(int page, int size);
    EventoFuture<EventoResult<std::vector<DTO_Evento>>> getDepartmentEventList(int departmentId);
    EventoFuture<EventoResult<std::vector<DTO_Evento>>> getEventListAfterTime(QDate time);
    EventoFuture<EventoResult<DTO_Evento>> getEventById(EventoID event);

    EventoFuture<EventoResult<std::vector<DTO_Slide>>> getSlideList();
    EventoFuture<EventoResult<std::vector<DTO_Slide>>> getEventSlideList(EventoID id);
    EventoFuture<EventoResult<std::vector<DTO_Slide>>> getHomeSlideList(int size);
    EventoFuture<EventoResult<std::vector<EventType>>> getTypeList();
    EventoFuture<EventoResult<QString>> getLocationList();
    EventoFuture<EventoResult<std::vector<Department>>> getDepartmentList();
    EventoFuture<EventoResult<std::vector<Department>>> getDepartmentListWithSubscriptionInfo();
    EventoFuture<EventoResult<QString>> getQRCode(EventoID eventId);

    // eventUpload
    EventoFuture<EventoResult<bool>> checkIn(EventoID event, const QString& code);
    EventoFuture<EventoResult<bool>> subscribeEvent(EventoID event, bool selection);
    EventoFuture<EventoResult<bool>> registerEvent(EventoID event, bool selection);
    EventoFuture<EventoResult<bool>> cancelEvent(EventoID event);
    EventoFuture<EventoResult<bool>> deleteEvent(EventoID event);
    EventoFuture<EventoResult<bool>> createEvent(const QString& title, const QString& description,
                                                 const QString& eventStart, const QString& eventEnd,
                                                 const QString& registerStart,
                                                 const QString& registerEnd, int typeId,
                                                 int locationId, const QVariantList& departmentIds,
                                                 const QString& tag);
    EventoFuture<EventoResult<bool>>
        editEvent(EventoID event, const QString& title, const QString& description,
                  const QString& eventStart, const QString& eventEnd, const QString& registerStart,
                  const QString& registerEnd, int typeId, int locationId,
                  const QVariantList& departmentIds, const QString& tag);
    EventoFuture<EventoResult<bool>> subscribeDepartment(int departmentId, bool unsubscribe);

    // feedback
    EventoFuture<EventoResult<std::vector<DTO_Feedback>>> getFeedbackList(EventoID eventoId);
    EventoFuture<EventoResult<DTO_FeedbackSummary>> getFeedbackSummary(EventoID eventoId);
    EventoFuture<EventoResult<std::pair<int, std::vector<FeedbackNum>>>>
        getFeedbackSummaryListInPage(int page);
    EventoFuture<EventoResult<bool>> hasFeedbacked(EventoID event);
    EventoFuture<EventoResult<bool>> feedbackEvent(const DTO_Feedback& feedback);
    EventoFuture<EventoResult<DTO_Feedback>> getFeedbackInfo(EventoID event);

    // adminFetch
    EventoFuture<EventoResult<std::vector<DTO_UserBrief>>> getEventManagerList(EventoID eventoId);
    EventoFuture<EventoResult<std::vector<DTO_UserBrief>>> getAdminUserList();
    EventoFuture<EventoResult<QString>> getAdminPermissionTreeData();
    EventoFuture<EventoResult<QString>> getManagerPermissionTreeData();
    EventoFuture<EventoResult<std::set<EventoID>>> getPermittedEvents(const QString& userId);

    EventoFuture<EventoResult<std::pair<QString, QString>>> checkUpdate();

private:
    EventoNetworkClient() = default;

public:
    static EventoNetworkClient* getInstance() {
        static EventoNetworkClient singleton;
        return &singleton;
    }
};
#endif // EVENTO_NETWORK_CLIENT_H
