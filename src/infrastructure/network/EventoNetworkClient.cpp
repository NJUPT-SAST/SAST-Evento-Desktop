#include "EventoNetworkClient.h"

#include <json_deserialise.hpp>

#include <QtConcurrent>

static auto API_GATEWAY = QStringLiteral("https://evento.sast.fun/api");
constexpr const char *USER_AGENT = "SAST-Evento-Desktop/1";
constexpr const char *MIME_FORM_URL_ENCODED = "application/x-www-form-urlencoded";
constexpr const char *MIME_JSON = "application/json";

static EventoResult<QJsonValue> handleNetworkReply(QNetworkReply* reply)
{
    auto networkError = reply->error();
    if (networkError != QNetworkReply::NoError) {
        return EventoException(EventoExceptionCode::NetworkError, "network error");
    }
    QJsonParseError jsonError;
    auto result = QJsonDocument::fromJson(reply->readAll(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        return EventoException(EventoExceptionCode::JsonError, QString("json error: %1 (offest = %2)").arg(jsonError.errorString(), jsonError.offset));
    }
    reply->deleteLater();
    if (!result.isObject()) {
        return EventoException(EventoExceptionCode::JsonError, QStringLiteral("expect object but got other"));
    }
    QJsonObject jsonObject = result.object();
    auto successItem = jsonObject.constFind("success");
    if (successItem != jsonObject.constEnd() && successItem.value().toBool()) {
        // successful
        auto dataItem = jsonObject.constFind("data");
        if (dataItem != jsonObject.constEnd()) {
            return QJsonValue(dataItem.value());
        }
        return QJsonValue{};
    } else {
        // error
        auto errCodeItem = jsonObject.constFind("errCode");
        auto errMsgItem = jsonObject.constFind("errMsg");
        EventoExceptionCode errCode = EventoExceptionCode::UnexpectedError;
        QString errMsg = QStringLiteral("no error message");
        if (errCodeItem != jsonObject.constEnd()) {
            errCode = static_cast<EventoExceptionCode>(errCodeItem.value().toInt(
                static_cast<int>(EventoExceptionCode::UnexpectedError)));
        }
        if (errMsgItem != jsonObject.constEnd()) {
            errMsg = errMsgItem.value().toString(errMsg);
        }
        return EventoException(errCode, errMsg);
    }
}

QFuture<EventoResult<QJsonValue>> EventoNetworkClient::get(const QUrl &url)
{
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);
    request.setRawHeader("Accept", MIME_JSON);
    if (!this->tokenBytes.isEmpty()) {
        request.setRawHeader("TOKEN", this->tokenBytes);
    }
    auto reply = manager.get(request);
    return QtConcurrent::run([=]() {
        QtFuture::connect(reply, &QNetworkReply::finished).waitForFinished();
        return handleNetworkReply(reply);
    });
}

QUrl EventoNetworkClient::endpoint(const QString &endpoint)
{
    return QUrl(API_GATEWAY + endpoint);
}

QUrl EventoNetworkClient::endpoint(const QString &endpoint, const QUrlQuery &params)
{
    auto r = QUrl(API_GATEWAY + endpoint);
    r.setQuery(params);
    return r;
}

QFuture<EventoResult<QJsonValue>> EventoNetworkClient::post(const QUrl &url, const QString &contentType, const QByteArray &requestData)
{
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);
    request.setHeader(QNetworkRequest::ContentTypeHeader, contentType);
    request.setRawHeader("Accept", MIME_JSON);
    if (!this->tokenBytes.isEmpty()) {
        request.setRawHeader("TOKEN", this->tokenBytes);
    }
    auto reply = manager.post(request, requestData);
    return QtFuture::connect(reply, &QNetworkReply::finished).then(std::bind(handleNetworkReply, reply));
}

QFuture<EventoResult<QJsonValue>> EventoNetworkClient::post(const QUrl &url, const QUrlQuery &requestData)
{
    return this->post(url, MIME_FORM_URL_ENCODED, requestData.toString().toUtf8());
}

QFuture<EventoResult<QJsonValue>> EventoNetworkClient::post(const QUrl &url, const QJsonDocument &requestData)
{
    return this->post(url, MIME_JSON, requestData.toJson(QJsonDocument::Compact));
}

QFuture<EventoResult<QJsonValue>> EventoNetworkClient::put(const QUrl &url, const QString &contentType, const QByteArray &requestData)
{
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);
    request.setHeader(QNetworkRequest::ContentTypeHeader, contentType);
    request.setRawHeader("Accept", MIME_JSON);
    if (!this->tokenBytes.isEmpty()) {
        request.setRawHeader("TOKEN", this->tokenBytes);
    }
    auto reply = manager.put(request, requestData);
    return QtFuture::connect(reply, &QNetworkReply::finished).then(std::bind(handleNetworkReply, reply));
}

QFuture<EventoResult<QJsonValue>> EventoNetworkClient::put(const QUrl &url, const QUrlQuery &requestData)
{
    return this->put(url, MIME_FORM_URL_ENCODED, requestData.toString().toUtf8());
}

QFuture<EventoResult<QJsonValue>> EventoNetworkClient::put(const QUrl &url, const QJsonDocument &requestData)
{
    return this->put(url, MIME_JSON, requestData.toJson(QJsonDocument::Compact));
}

QFuture<EventoResult<QJsonValue>> EventoNetworkClient::patch(const QUrl &url, const QString &contentType, const QByteArray &requestData)
{
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);
    request.setHeader(QNetworkRequest::ContentTypeHeader, contentType);
    request.setRawHeader("Accept", MIME_JSON);
    if (!this->tokenBytes.isEmpty()) {
        request.setRawHeader("TOKEN", this->tokenBytes);
    }
    auto reply = manager.sendCustomRequest(request, "PATCH", requestData);
    return QtFuture::connect(reply, &QNetworkReply::finished).then(std::bind(handleNetworkReply, reply));
}

QFuture<EventoResult<QJsonValue>> EventoNetworkClient::patch(const QUrl &url, const QUrlQuery &requestData)
{
    return this->patch(url, MIME_FORM_URL_ENCODED, requestData.toString().toUtf8());
}

QFuture<EventoResult<QJsonValue>> EventoNetworkClient::patch(const QUrl &url, const QJsonDocument &requestData)
{
    return this->patch(url, MIME_JSON, requestData.toJson(QJsonDocument::Compact));
}

QFuture<EventoResult<QJsonValue>> EventoNetworkClient::deleteResource(const QUrl &url)
{
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);
    request.setRawHeader("Accept", MIME_JSON);
    if (!this->tokenBytes.isEmpty()) {
        request.setRawHeader("TOKEN", this->tokenBytes);
    }
    auto reply = manager.deleteResource(request);
    return QtFuture::connect(reply, &QNetworkReply::finished).then(std::bind(handleNetworkReply, reply));
}

static QStringList asStringList(const QJsonValue &value)
{
    auto array = value.toArray();
    QStringList result;
    result.reserve(array.size());
    for (auto v : array) {
        result.push_back(v.toString());
    }
    return result;
}

// userFetch
QFuture<EventoResult<QStringList>> EventoNetworkClient::getAdminPermission()
{
    auto url = endpoint(QStringLiteral("/permission/admin/self"));
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<QStringList> {
        if (result) {
            return asStringList(result.take());
        } else {
            return {result.code(), result.message()};
        }
    });
}

QFuture<EventoResult<QStringList>> EventoNetworkClient::getManagerPermission(const EventoID &eventoId)
{
    auto url = endpoint(QStringLiteral("/permission/event/manager/self"));
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<QStringList> {
        if (result) {
            return asStringList(result.take());
        } else {
            return {result.code(), result.message()};
        }
    });
}

QFuture<EventoResult<QStringList>> EventoNetworkClient::getPermittedEvent()
{
    auto url = endpoint(QStringLiteral("/permission/manager/events"));
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<QStringList> {
        if (result) {
            return asStringList(result.take());
        } else {
            return {result.code(), result.message()};
        }
    });
}

QFuture<EventoResult<DTO_Permission>> EventoNetworkClient::getEventPermission(EventoID event)
{
    // TODO: implement
    return {};
}

QFuture<EventoResult<DTO_User>> EventoNetworkClient::getUserInfo(const UserID &id)
{
    auto url = endpoint(QStringLiteral("/user/info"), [&](QUrlQuery params) {
        params.addQueryItem("userId", id);
    });
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<DTO_User> {
        if (result) {
            // FIXME
            return DTO_User{};
        } else {
            return {result.code(), result.message()};
        }
    });
}

register_object_member(ParticipationStatus, "isRegistration", isRegistrated);
register_object_member(ParticipationStatus, "isParticipate", isParticipated);
register_object_member(ParticipationStatus, "isSubscribe", isSubscribed);
declare_object(ParticipationStatus,
               object_member(ParticipationStatus, isRegistrated),
               object_member(ParticipationStatus, isParticipated),
               object_member(ParticipationStatus, isSubscribed));

QFuture<EventoResult<ParticipationStatus>> EventoNetworkClient::getUserParticipate(const EventoID &eventoId)
{
    auto url = endpoint(QStringLiteral("/user/participate"), [&](QUrlQuery params) {
        params.addQueryItem("eventId", QString::number(eventoId));
    });
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<ParticipationStatus> {
        if (result) {
            auto rootValue = result.take();
            ParticipationStatus result{};
            if (rootValue.isObject()) {
                declare_top_deserialiser(result, deserialiser_holder);
                JsonDeserialise::JsonDeserialiser deserialiser(deserialiser_holder);
                deserialiser.deserialise(rootValue.toObject());
            } else if (rootValue.isNull()) {
                // okey
            } else {
                return EventoException(EventoExceptionCode::JsonError, QStringLiteral("expect object or null but got other"));
            }
            return result;
        } else {
            return {result.code(), result.message()};
        }
    });
}

register_object_member(DTO_Feedback, "id", id);
register_object_member(DTO_Feedback, "content", content);
register_object_member(DTO_Feedback, "score", score);
register_object_member(DTO_Feedback, "eventId", eventId);
declare_object(DTO_Feedback,
               object_member(DTO_Feedback, id),
               object_member(DTO_Feedback, content),
               object_member(DTO_Feedback, score),
               object_member(DTO_Feedback, eventId));

QFuture<EventoResult<DTO_Feedback>> EventoNetworkClient::getFeedbackInfo(const EventoID &eventoId)
{
    auto url = endpoint(QStringLiteral("/feedback/user/info"), [&](QUrlQuery params) {
        params.addQueryItem("eventId", QString::number(eventoId));
    });
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<DTO_Feedback> {
        if (result) {
            auto rootValue = result.take();
            DTO_Feedback result{};
            if (rootValue.isObject()) {
                declare_top_deserialiser(result, deserialiser_holder);
                JsonDeserialise::JsonDeserialiser deserialiser(deserialiser_holder);
                deserialiser.deserialise(rootValue.toObject());
            }
            return result;
        } else {
            return {result.code(), result.message()};
        }
    });
}

register_object_member(EventType, "id", id);
register_object_member(EventType, "typeName", name);
register_object_member(EventType, "allowConflict", allowConflict);
declare_object(EventType,
               object_member(EventType, id),
               object_member(EventType, name));

register_object_member(Department, "id", id);
register_object_member(Department, "departmentName", name);

declare_object(Department,
               object_member(Department, id),
               object_member(Department, name));

static QDateTime str2date(const QString& text) {
    return QDateTime::fromString(text, "yyyy-MM-dd HH:mm:ss");
};
static QString date2str(const QDateTime& time) {
    return time.toString("yyyy-MM-dd HH:mm:ss");
};
declare_global_extension(QDateTime, QString, str2date, date2str);

static const char* strings[] = {
    "ERROR",
    "NOT_STARTED",
    "CHECKING_IN",
    "IN_PROGRESS",
    "CANCELED",
    "ENDED"
};
static EventState str2eventstate(const QString& str) {
    for (int i = 0; i < 6; i++)
        if (str == strings[i])
            return static_cast<EventState>(i);
    return EventState::Uninitialised;
}
static auto eventstate2str(EventState state) {
    return strings[int(state)];
}
declare_global_extension(EventState, QString, str2eventstate, eventstate2str);

register_object_member(DTO_Evento, "id", id);
register_object_member(DTO_Evento, "title", title);
register_object_member(DTO_Evento, "description", description);
register_object_member(DTO_Evento, "gmt_event_start", gmtEventStart);
register_object_member(DTO_Evento, "gmt_event_end", gmtEventEnd);
register_object_member(DTO_Evento, "gmt_registration_start", gmtRegistrationStart);
register_object_member(DTO_Evento, "gmt_registration_end", gmtRegistrationEnd);
register_object_member(DTO_Evento, "eventType", type);
register_object_member(DTO_Evento, "location", location);
register_object_member(DTO_Evento, "tag", tag);
register_object_member(DTO_Evento, "state", state);
register_object_member(DTO_Evento, "departments", departments);
declare_object(DTO_Evento,
               object_member(DTO_Evento, id),
               object_member(DTO_Evento, title),
               object_member(DTO_Evento, description),
               object_member(DTO_Evento, gmtEventStart),
               object_member(DTO_Evento, gmtEventEnd),
               object_member(DTO_Evento, gmtRegistrationStart),
               object_member(DTO_Evento, gmtRegistrationEnd),
               object_member(DTO_Evento, type),
               object_member(DTO_Evento, location),
               object_member(DTO_Evento, tag),
               object_member(DTO_Evento, state),
               object_member(DTO_Evento, departments));

std::vector<DTO_Evento> asEventoDTOArray(const QJsonValue &rootValue)
{
    std::vector<DTO_Evento> result;

    if (rootValue.isArray()) {
        declare_top_deserialiser(result, deserialiser);
        deserialiser.assign(rootValue);
    }
    return result;
}

// eventFetch
QFuture<EventoResult<std::vector<DTO_Evento>>> EventoNetworkClient::getUndertakingList()
{
    auto url = endpoint(QStringLiteral("/event/conducting"));
    auto future = this->get(url);
    return QtConcurrent::run([=]() -> EventoResult<std::vector<DTO_Evento>> {
        auto f(future);
        auto result = f.takeResult();
        if (result) {
            return asEventoDTOArray(result.take());
        }
        else {
            return { result.code(), result.message() };
        }
    });
}

QFuture<EventoResult<std::vector<DTO_Evento>>> EventoNetworkClient::getLatestList()
{
    auto url = endpoint(QStringLiteral("/event/newest"));
    auto future = this->get(url);
    return QtConcurrent::run([=]() -> EventoResult<std::vector<DTO_Evento>> {
        auto f(future);
        auto result = f.takeResult();
        if (result) {
            return asEventoDTOArray(result.take());
        }
        else {
            return { result.code(), result.message() };
        }
    });
}

QFuture<EventoResult<std::vector<DTO_Evento>>> EventoNetworkClient::getRegisteredList()
{
    auto url = endpoint(QStringLiteral("/user/registered"));
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<std::vector<DTO_Evento>> {
        if (result) {
            return asEventoDTOArray(result.take());
        } else {
            return {result.code(), result.message()};
        }
    });
}

QFuture<EventoResult<std::vector<DTO_Evento>>> EventoNetworkClient::getSubscribedList()
{
    auto url = endpoint(QStringLiteral("/user/subscribed"));
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<std::vector<DTO_Evento>> {
        if (result) {
            return asEventoDTOArray(result.take());
        } else {
            return {result.code(), result.message()};
        }
    });
}

QFuture<EventoResult<std::vector<DTO_Evento>>> EventoNetworkClient::getHistoryList()
{
    auto url = endpoint(QStringLiteral("/event/history"));
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<std::vector<DTO_Evento>> {
        if (result) {
            return asEventoDTOArray(result.take());
        } else {
            return {result.code(), result.message()};
        }
    });
}

QFuture<EventoResult<std::vector<DTO_Evento>>> EventoNetworkClient::getEventList(int page, int size)
{
    auto url = endpoint(QStringLiteral("/event/list"), [&](QUrlQuery params) {
        params.addQueryItem("page", QString::number(page));
        params.addQueryItem("size", QString::number(size));
    });
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<std::vector<DTO_Evento>> {
        if (result) {
            return asEventoDTOArray(result.take());
        } else {
            return {result.code(), result.message()};
        }
    });
}

QFuture<EventoResult<std::vector<DTO_Evento>>> EventoNetworkClient::getDepartmentEventList(int departmentId)
{
    QUrlQuery params;
    params.addQueryItem("departmentId", QString::number(departmentId));
    auto url = endpoint(QStringLiteral("/event/list"));
    return this->post(url, params).then([](EventoResult<QJsonValue> result) -> EventoResult<std::vector<DTO_Evento>> {
        if (result) {
            return asEventoDTOArray(result.take());
        } else {
            return {result.code(), result.message()};
        }
    });
}

QFuture<EventoResult<DTO_Evento>> EventoNetworkClient::getEvent(EventoID event)
{
    auto url = endpoint(QStringLiteral("/event/info"), [&](QUrlQuery params) {
        params.addQueryItem("eventId", QString::number(event));
    });
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<DTO_Evento> {
        if (result) {
            auto rootValue = result.take();
            if (rootValue.isObject()) {
                DTO_Evento dto;
                declare_top_deserialiser(dto, deserialiser);
                deserialiser.assign(rootValue);
                return dto;
            }
            return EventoException(EventoExceptionCode::JsonError, "Format Error!");
        } else {
            return {result.code(), result.message()};
        }
    });
}

QFuture<EventoResult<std::vector<DTO_Feedback>>> EventoNetworkClient::getFeedbackList(EventoID eventoId)
{
    auto url = endpoint(QStringLiteral("/feedback/list"), [&](QUrlQuery params) {
        params.addQueryItem("eventId", QString::number(eventoId));
    });
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<std::vector<DTO_Feedback>> {
        if (result) {
            auto rootValue = result.take();
            std::vector<DTO_Feedback> result;
            if (rootValue.isArray()) {
                declare_top_deserialiser(result, deserialiser);
                deserialiser.assign(rootValue);
            } else if (rootValue.isNull())
                return result;
            return EventoException(EventoExceptionCode::JsonError, "Format Error!");
        } else {
            return {result.code(), result.message()};
        }
    });
}

register_object_member(DTO_Slide, "id", id);
register_object_member(DTO_Slide, "title", title);
register_object_member(DTO_Slide, "link", link);
register_object_member(DTO_Slide, "url", url);
declare_object(DTO_Slide,
               object_member(DTO_Slide, id),
               object_member(DTO_Slide, title),
               object_member(DTO_Slide, link),
               object_member(DTO_Slide, url));

QFuture<EventoResult<std::vector<DTO_Slide>>> EventoNetworkClient::getSlideList()
{
    // TODO: implement
    return {};
}

QFuture<EventoResult<std::vector<DTO_Slide>>> EventoNetworkClient::getEventSlideList(EventoID id)
{
    auto url = endpoint(QStringLiteral("/slide/event/list"), [&](QUrlQuery params) {
        params.addQueryItem("eventId", QString::number(id));
    });
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<std::vector<DTO_Slide>> {
        if (result) {
            auto rootValue = result.take();
            std::vector<DTO_Slide> result;
            if (rootValue.isArray()) {
                declare_top_deserialiser(result, deserialiser);
                deserialiser.assign(rootValue);
            } else if (rootValue.isNull())
                return result;
            return EventoException(EventoExceptionCode::JsonError, "Format Error!");
        } else {
            return {result.code(), result.message()};
        }
    });
}

QFuture<EventoResult<std::vector<DTO_Slide>>> EventoNetworkClient::getHomeSlideList(int size)
{
    auto url = endpoint(QStringLiteral("/slide/home/list"), [&](QUrlQuery params) {
        params.addQueryItem("size", QString::number(size));
    });
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<std::vector<DTO_Slide>> {
        if (result) {
            auto rootValue = result.take();
            std::vector<DTO_Slide> result;
            if (rootValue.isArray()) {
                declare_top_deserialiser(result, deserialiser);
                deserialiser.assign(rootValue);
            } else if (rootValue.isNull())
                return result;
            return EventoException(EventoExceptionCode::JsonError, "Format Error!");
        } else {
            return {result.code(), result.message()};
        }
    });
}

QFuture<EventoResult<std::vector<EventType>>> EventoNetworkClient::getTypeList()
{
    auto url = endpoint(QStringLiteral("/admin/types"));
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<std::vector<EventType>> {
        if (result) {
            auto rootValue = result.take();
            std::vector<EventType> result;
            if (rootValue.isArray()) {
                declare_top_deserialiser(result, deserialiser);
                deserialiser.assign(rootValue);
            } else if (rootValue.isNull())
                return result;
            return EventoException(EventoExceptionCode::JsonError, "Format Error!");
        } else {
            return {result.code(), result.message()};
        }
    });
}

QFuture<EventoResult<QString>> EventoNetworkClient::getLocationList()
{
    // TODO: implement
    return {};
}

QFuture<EventoResult<QString>> EventoNetworkClient::getDepartmentList()
{
    // TODO: implement
    return {};
}

QFuture<EventoResult<QString>> EventoNetworkClient::getQRCode(int eventId)
{
    auto url = endpoint(QStringLiteral("/event/authcode"), [&](QUrlQuery params) {
        params.addQueryItem("eventId", QString::number(eventId));
    });
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<QString> {
        if (result) {
            return result.take().toString();
        } else {
            return {result.code(), result.message()};
        }
    });
}

// eventUpload
QFuture<EventoResult<bool>> EventoNetworkClient::checkInEvent(EventoID event, const QString &code)
{
    auto url = endpoint(QStringLiteral("/event/authcode"), [&](QUrlQuery params) {
        params.addQueryItem("eventId", QString::number(event));
        params.addQueryItem("code", code);
    });
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<bool> {
        if (result) {
            return {};
        } else {
            return {result.code(), result.message()};
        }
    });
}

QFuture<EventoResult<bool>> EventoNetworkClient::feedbackEvent(const DTO_Feedback &feedback)
{
    QUrlQuery params;
    params.addQueryItem("content", feedback.content);
    params.addQueryItem("score", QString::number(feedback.score));
    params.addQueryItem("eventId", QString::number(feedback.eventId));
    auto url = endpoint(QStringLiteral("/feedback/info"));
    return this->post(url, params).then([](EventoResult<QJsonValue> result) -> EventoResult<bool> {
        if (result) {
            return {};
        } else {
            return {result.code(), result.message()};
        }
    });
}

QFuture<EventoResult<bool>> EventoNetworkClient::subscribEvent(EventoID event, bool targetState)
{
    auto url = endpoint(QStringLiteral("/user/subscribe"), [&](QUrlQuery params) {
        params.addQueryItem("eventId", QString::number(event));
        params.addQueryItem("isSubscribe", targetState ? QStringLiteral("true") : QStringLiteral("false"));
    });
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<bool> {
        if (result) {
            return {};
        } else {
            return {result.code(), result.message()};
        }
    });
}

QFuture<EventoResult<bool>> EventoNetworkClient::isFeedbacked(EventoID event)
{
    auto url = endpoint(QStringLiteral("/feedback/user/info"), [&](QUrlQuery params) {
        params.addQueryItem("eventId", QString::number(event));
    });
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<bool> {
        if (result) {
            return {};
        } else {
            return {result.code(), result.message()};
        }
    });
}

// adminFetch
QFuture<EventoResult<std::vector<DTO_Evento>>> EventoNetworkClient::getQualifiedEvent(int type, const std::vector<int> &dep, const QDate &day)
{
    QUrlQuery params;
    if (type != -1)
        params.addQueryItem("typeId", QString::number(type));
    if (!dep.empty()) {
        QString departmentIds = QString::number(dep[0]);
        for (int i = 1; i < dep.size(); ++i) {
			departmentIds += QStringLiteral(",") + QString::number(dep[i]);
		}
        params.addQueryItem("departmentId", departmentIds);
    }
    if (day.isValid())
        params.addQueryItem("time", day.toString("yyyy-MM-dd"));
    auto url = endpoint(QStringLiteral("/event/list"));
    return this->post(url, params).then([](EventoResult<QJsonValue> result) -> EventoResult<std::vector<DTO_Evento>> {
        if (result) {
            return asEventoDTOArray(result.take());
        } else {
            return {result.code(), result.message()};
        }
    });
}

QFuture<EventoResult<QStringList>> EventoNetworkClient::getActionStateList()
{
    // TODO: implement
    return {};
}

QFuture<EventoResult<QStringList>> EventoNetworkClient::getActionList()
{
    // TODO: implement
    return {};
}

register_object_member(DTO_UserBrief, "userId", userId);
register_object_member(DTO_UserBrief, "email", email);
declare_object(DTO_UserBrief,
               object_member(DTO_UserBrief, userId),
               object_member(DTO_UserBrief, email));

QFuture<EventoResult<std::vector<DTO_UserBrief>>> EventoNetworkClient::getEventManagerList(const EventoID &eventoId)
{
    auto url = endpoint(QStringLiteral("/permission/event/managers"), [&](QUrlQuery params) {
        params.addQueryItem("eventId", QString::number(eventoId));
    });
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<std::vector<DTO_UserBrief>> {
        if (result) {
            auto rootValue = result.take();
            std::vector<DTO_UserBrief> result;
            if (rootValue.isArray()) {
                declare_top_deserialiser(result, deserialiser);
                deserialiser.assign(rootValue);
            } else if (rootValue.isNull())
                return result;
            return EventoException(EventoExceptionCode::JsonError, "Format Error!");
        } else {
            return {result.code(), result.message()};
        }
    });
}

QFuture<EventoResult<std::vector<DTO_UserBrief>>> EventoNetworkClient::getAdminUserList()
{
    auto url = endpoint(QStringLiteral("/permission/admins"));
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<std::vector<DTO_UserBrief>> {
        if (result) {
            auto rootValue = result.take();
            std::vector<DTO_UserBrief> result;
            if (rootValue.isArray()) {
                declare_top_deserialiser(result, deserialiser);
                deserialiser.assign(rootValue);
            } else if (rootValue.isNull())
                return result;
            return EventoException(EventoExceptionCode::JsonError, "Format Error!");
        } else {
            return {result.code(), result.message()};
        }
    });
}

QFuture<EventoResult<QString>> EventoNetworkClient::getAdminPermissionTreeData()
{
    // TODO: implement
    return {};
}

QFuture<EventoResult<QString>> EventoNetworkClient::getManagerPermissionTreeData()
{
    // TODO: implement
    return {};
}
