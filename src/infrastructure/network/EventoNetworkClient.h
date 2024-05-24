#ifndef EVENTO_NETWORK_CLIENT_H
#define EVENTO_NETWORK_CLIENT_H

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QUrlQuery>

#include <dto/evento.h>
#include <dto/feedback.h>
#include <dto/feedback_summary.h>
#include <dto/location.h>
#include <dto/permission.h>
#include <dto/slide.h>
#include <dto/user.h>
#include <dto/user_brief.h>

#include "promise.h"
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

    EventoPromise<EventoResult<QJsonValue>> get(const QUrl& url);

    EventoPromise<EventoResult<QJsonValue>> post(const QUrl& url, const QString& contentType,
                                                 const QByteArray& requestData);
    EventoPromise<EventoResult<QJsonValue>> post(const QUrl& url, const QUrlQuery& requestData);
    EventoPromise<EventoResult<QJsonValue>> post(const QUrl& url, const QJsonDocument& requestData);

    EventoPromise<EventoResult<QJsonValue>> put(const QUrl& url, const QString& contentType,
                                                const QByteArray& requestData);
    EventoPromise<EventoResult<QJsonValue>> put(const QUrl& url, const QUrlQuery& requestData);
    EventoPromise<EventoResult<QJsonValue>> put(const QUrl& url, const QJsonDocument& requestData);

    EventoPromise<EventoResult<QJsonValue>> patch(const QUrl& url, const QString& contentType,
                                                  const QByteArray& requestData);
    EventoPromise<EventoResult<QJsonValue>> patch(const QUrl& url, const QUrlQuery& requestData);
    EventoPromise<EventoResult<QJsonValue>> patch(const QUrl& url,
                                                  const QJsonDocument& requestData);

    EventoPromise<EventoResult<QJsonValue>> deleteResource(const QUrl& url);

public:
    // userFetch
    EventoPromise<EventoResult<DTO_User>> loginViaSastLink(const QString& code);
    EventoPromise<EventoResult<QStringList>> getAdminPermission();
    EventoPromise<EventoResult<QStringList>> getManagerPermission(EventoID event);
    EventoPromise<EventoResult<QStringList>> getPermittedEvent();
    [[maybe_unused]] EventoPromise<EventoResult<DTO_Permission>> getEventPermission(EventoID event);
    EventoPromise<EventoResult<DTO_User>> getUserInfo(const UserID& id);
    EventoPromise<EventoResult<ParticipationStatus>> getUserParticipate(EventoID event);

    // eventFetch
    EventoPromise<EventoResult<std::vector<DTO_Evento>>> getUndertakingList();
    EventoPromise<EventoResult<std::vector<DTO_Evento>>> getLatestList();
    EventoPromise<EventoResult<std::vector<DTO_Evento>>> getRegisteredList();
    EventoPromise<EventoResult<std::vector<DTO_Evento>>> getSubscribedList();
    EventoPromise<EventoResult<std::vector<DTO_Evento>>> getHistoryList();
    EventoPromise<EventoResult<std::vector<DTO_Evento>>> getEventListInPage(int page, int size);
    EventoPromise<EventoResult<std::vector<DTO_Evento>>> getDepartmentEventList(int departmentId);
    EventoPromise<EventoResult<std::vector<DTO_Evento>>> getEventListAfterTime(QDate time);
    EventoPromise<EventoResult<DTO_Evento>> getEventById(EventoID event);

    // othersFetch
    EventoPromise<EventoResult<std::vector<DTO_Slide>>> getSlideList();
    EventoPromise<EventoResult<std::vector<DTO_Slide>>> getEventSlideList(EventoID id);
    EventoPromise<EventoResult<std::vector<DTO_Slide>>> getHomeSlideList(int size);
    EventoPromise<EventoResult<std::vector<EventType>>> getTypeList();
    EventoPromise<EventoResult<std::vector<DTO_Location>>> getLocationList();
    EventoPromise<EventoResult<std::vector<Department>>> getDepartmentList();
    EventoPromise<EventoResult<std::vector<Department>>> getDepartmentListWithSubscriptionInfo();
    EventoPromise<EventoResult<QString>> getQRCode(EventoID eventId);

    // eventUpload
    EventoPromise<EventoResult<bool>> checkIn(EventoID event, const QString& code);
    EventoPromise<EventoResult<bool>> subscribeEvent(EventoID event, bool selection);
    EventoPromise<EventoResult<bool>> registerEvent(EventoID event, bool selection);
    EventoPromise<EventoResult<bool>> cancelEvent(EventoID event);
    EventoPromise<EventoResult<bool>> deleteEvent(EventoID event);
    EventoPromise<EventoResult<bool>>
        createEvent(const QString& title, const QString& description, const QString& eventStart,
                    const QString& eventEnd, const QString& registerStart,
                    const QString& registerEnd, int typeId, int locationId,
                    const QVariantList& departmentIds, const QString& tag);
    EventoPromise<EventoResult<bool>>
        editEvent(EventoID event, const QString& title, const QString& description,
                  const QString& eventStart, const QString& eventEnd, const QString& registerStart,
                  const QString& registerEnd, int typeId, int locationId,
                  const QVariantList& departmentIds, const QString& tag);
    EventoPromise<EventoResult<bool>> subscribeDepartment(int departmentId, bool unsubscribe);

    // feedback
    EventoPromise<EventoResult<std::vector<DTO_Feedback>>> getFeedbackList(EventoID eventoId);
    EventoPromise<EventoResult<DTO_FeedbackSummary>> getFeedbackSummary(EventoID eventoId);
    EventoPromise<EventoResult<std::pair<int, std::vector<FeedbackNum>>>>
        getFeedbackSummaryListInPage(int page);
    EventoPromise<EventoResult<bool>> hasFeedbacked(EventoID event);
    EventoPromise<EventoResult<bool>> feedbackEvent(const DTO_Feedback& feedback);
    EventoPromise<EventoResult<DTO_Feedback>> getFeedbackInfo(EventoID event);

    // adminFetch
    EventoPromise<EventoResult<std::vector<DTO_UserBrief>>> getEventManagerList(EventoID eventoId);
    EventoPromise<EventoResult<std::vector<DTO_UserBrief>>> getAdminUserList();
    EventoPromise<EventoResult<QString>> getAdminPermissionTreeData();
    EventoPromise<EventoResult<QString>> getManagerPermissionTreeData();
    EventoPromise<EventoResult<std::set<EventoID>>> getPermittedEvents(const QString& userId);

    EventoPromise<EventoResult<std::pair<QString, QString>>> checkUpdate();

private:
    EventoNetworkClient() = default;

public:
    static EventoNetworkClient* getInstance() {
        static EventoNetworkClient singleton;
        return &singleton;
    }
};
#endif // EVENTO_NETWORK_CLIENT_H
