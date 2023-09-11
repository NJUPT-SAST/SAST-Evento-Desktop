#include "EventoNetworkClient.h"
#include <json_deserialise.hpp>

static const QUrl API_GATEWAY("https://sast-evento.example.com/");
constexpr const char *USER_AGENT = "SAST-Evento-Desktop/1";
constexpr const char *MIME_FORM_URL_ENCODED = "application/x-www-form-urlencoded";
constexpr const char *MIME_JSON = "application/json";

EventoNetworkClient::EventoNetworkClient()
{
}

static QFuture<EventoResult<QJsonValue>> handleNetworkReply(QNetworkReply *reply)
{
    QFuture<void> onFinishedFuture = QtFuture::connect(reply, &QNetworkReply::finished);
    return onFinishedFuture.then([reply]() -> EventoResult<QJsonValue> {
        auto networkError = reply->error();
        if (networkError != QNetworkReply::NoError) {
            return EventoException(EventoExceptionCode::NetworkError, "network error");
        }
        QJsonParseError jsonError;
        auto result = QJsonDocument::fromJson(reply->readAll(), &jsonError);
        if (jsonError.error != QJsonParseError::NoError) {
            return EventoException(EventoExceptionCode::JsonError,
                                   QStringLiteral("json error: %1 (offest = %2)").arg(jsonError.errorString(), jsonError.offset));
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
                return static_cast<QJsonValue>(dataItem.value());
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
    });
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
    return handleNetworkReply(reply);
}

QUrl EventoNetworkClient::endpoint(const QString &endpoint)
{
    return API_GATEWAY.resolved(QUrl(endpoint));
}

QUrl EventoNetworkClient::endpoint(const QString &endpoint, const QUrlQuery &params)
{
    auto r = API_GATEWAY.resolved(QUrl(endpoint));
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
    return handleNetworkReply(reply);
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
    return handleNetworkReply(reply);
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
    return handleNetworkReply(reply);
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
    return handleNetworkReply(reply);
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
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            return asStringList(*rootValue);
        } else {
            return std::get<EventoException>(result);
        }
    });
}

QFuture<EventoResult<QStringList>> EventoNetworkClient::getManagerPermission(const EventoID &eventoId)
{
    auto url = endpoint(QStringLiteral("/permission/event/manager/self"));
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<QStringList> {
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            return asStringList(*rootValue);
        } else {
            return std::get<EventoException>(result);
        }
    });
}

QFuture<EventoResult<QStringList>> EventoNetworkClient::getPermittedEvent()
{
    auto url = endpoint(QStringLiteral("/permission/manager/events"));
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<QStringList> {
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            return asStringList(*rootValue);
        } else {
            return std::get<EventoException>(result);
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
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            // FIXME
            return DTO_User{};
        } else {
            return std::get<EventoException>(result);
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
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            ParticipationStatus result{};
            if (rootValue->isObject()) {
                declare_top_deserialiser(result, deserialiser_holder);
                JsonDeserialise::JsonDeserialiser deserialiser(deserialiser_holder);
                deserialiser.deserialise(rootValue->toObject());
            } else if (rootValue->isNull()) {
                // okey
            } else {
                return EventoException(EventoExceptionCode::JsonError, QStringLiteral("expect object or null but got other"));
            }
            return result;
        } else {
            return std::get<EventoException>(result);
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
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            DTO_Feedback result{};
            result.isFeedback = false;
            if (rootValue->isObject()) {
                result.isFeedback = true;
                declare_top_deserialiser(result, deserialiser_holder);
                JsonDeserialise::JsonDeserialiser deserialiser(deserialiser_holder);
                deserialiser.deserialise(rootValue->toObject());
            }
            return result;
        } else {
            return std::get<EventoException>(result);
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

struct EventoNakedDTO {
    EventoID id;
    QString title;
    QString description;
    QString gmtEventStart;
    QString gmtEventEnd;
    QString gmtRegistrationStart;
    QString gmtRegistrationEnd;
    EventType type;
    QString location;
    Tag tag;
    QString state;
    std::vector<Department> departments;

    operator DTO_Evento()
    {
        DTO_Evento dto;
        dto.id = this->id;
        dto.title = this->title;
        dto.description = this->description;
        dto.gmtEventStart = QDateTime::fromString(this->gmtEventStart, "yyyy-MM-dd HH:mm:ss");
        dto.gmtEventStart.setTimeSpec(Qt::UTC);
        dto.gmtEventEnd = QDateTime::fromString(this->gmtEventEnd, "yyyy-MM-dd HH:mm:ss");
        dto.gmtEventEnd.setTimeSpec(Qt::UTC);
        dto.gmtRegistrationStart = QDateTime::fromString(this->gmtRegistrationStart, "yyyy-MM-dd HH:mm:ss");
        dto.gmtRegistrationStart.setTimeSpec(Qt::UTC);
        dto.gmtRegistrationEnd = QDateTime::fromString(this->gmtRegistrationEnd, "yyyy-MM-dd HH:mm:ss");
        dto.gmtRegistrationStart.setTimeSpec(Qt::UTC);
        dto.type = this->type;
        dto.location = this->location;
        dto.tag = this->tag;
        dto.state = EventState::Registration; // FIXME: enum string is not documented in Apifox
        dto.departments = this->departments;
        return dto;
    }
};

register_object_member(EventoNakedDTO, "id", id);
register_object_member(EventoNakedDTO, "title", title);
register_object_member(EventoNakedDTO, "description", description);
register_object_member(EventoNakedDTO, "gmt_event_start", gmtEventStart);
register_object_member(EventoNakedDTO, "gmt_event_end", gmtEventEnd);
register_object_member(EventoNakedDTO, "gmt_registration_start", gmtRegistrationStart);
register_object_member(EventoNakedDTO, "gmt_registration_end", gmtRegistrationEnd);
register_object_member(EventoNakedDTO, "eventType", type);
register_object_member(EventoNakedDTO, "location", location);
register_object_member(EventoNakedDTO, "tag", tag);
register_object_member(EventoNakedDTO, "state", state);
register_object_member(EventoNakedDTO, "departments", departments);
declare_object(EventoNakedDTO,
               object_member(EventoNakedDTO, id),
               object_member(EventoNakedDTO, title),
               object_member(EventoNakedDTO, description),
               object_member(EventoNakedDTO, gmtEventStart),
               object_member(EventoNakedDTO, gmtEventEnd),
               object_member(EventoNakedDTO, gmtRegistrationStart),
               object_member(EventoNakedDTO, gmtRegistrationEnd),
               object_member(EventoNakedDTO, type),
               object_member(EventoNakedDTO, location),
               object_member(EventoNakedDTO, tag),
               object_member(EventoNakedDTO, state),
               object_member(EventoNakedDTO, departments));

std::vector<DTO_Evento> asEventoDTOArray(const QJsonValue &rootValue)
{
    std::vector<EventoNakedDTO> naked_dtos;
    if (rootValue.isArray()) {
        declare_top_deserialiser(naked_dtos, deserialiser_holder);
        JsonDeserialise::JsonDeserialiser deserialiser(deserialiser_holder);
        deserialiser.deserialise_array(rootValue.toArray());
    }
    std::vector<DTO_Evento> result;
    result.reserve(naked_dtos.size());
    for (auto &naked_dto : naked_dtos) {
        result.emplace_back(naked_dto);
    }
    return result;
}

// eventFetch
QFuture<EventoResult<std::vector<DTO_Evento>>> EventoNetworkClient::getUndertakingList()
{
    auto url = endpoint(QStringLiteral("/event/conducting"));
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<std::vector<DTO_Evento>> {
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            return asEventoDTOArray(*rootValue);
        } else {
            return std::get<EventoException>(result);
        }
    });
}

QFuture<EventoResult<std::vector<DTO_Evento>>> EventoNetworkClient::getLatestList()
{
    auto url = endpoint(QStringLiteral("/event/newest"));
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<std::vector<DTO_Evento>> {
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            return asEventoDTOArray(*rootValue);
        } else {
            return std::get<EventoException>(result);
        }
    });
}

QFuture<EventoResult<std::vector<DTO_Evento>>> EventoNetworkClient::getSubscribedList()
{
    auto url = endpoint(QStringLiteral("/user/subscribed"));
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<std::vector<DTO_Evento>> {
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            return asEventoDTOArray(*rootValue);
        } else {
            return std::get<EventoException>(result);
        }
    });
}

QFuture<EventoResult<std::vector<DTO_Evento>>> EventoNetworkClient::getHistoryList()
{
    auto url = endpoint(QStringLiteral("/event/history"));
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<std::vector<DTO_Evento>> {
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            return asEventoDTOArray(*rootValue);
        } else {
            return std::get<EventoException>(result);
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
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            return asEventoDTOArray(*rootValue);
        } else {
            return std::get<EventoException>(result);
        }
    });
}

QFuture<EventoResult<std::vector<DTO_Evento>>> EventoNetworkClient::getDepartmentEventList(int departmentId)
{
    QUrlQuery params;
    params.addQueryItem("departmentId", QString::number(departmentId));
    auto url = endpoint(QStringLiteral("/event/list"));
    return this->post(url, params).then([](EventoResult<QJsonValue> result) -> EventoResult<std::vector<DTO_Evento>> {
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            return asEventoDTOArray(*rootValue);
        } else {
            return std::get<EventoException>(result);
        }
    });
}

QFuture<EventoResult<DTO_Evento>> EventoNetworkClient::getEvent(EventoID event)
{
    auto url = endpoint(QStringLiteral("/event/info"), [&](QUrlQuery params) {
        params.addQueryItem("eventId", QString::number(event));
    });
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<DTO_Evento> {
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            if (rootValue->isObject()) {
                EventoNakedDTO naked_dto;
                declare_top_deserialiser(naked_dto, deserialiser_holder);
                JsonDeserialise::JsonDeserialiser deserialiser(deserialiser_holder);
                deserialiser.deserialise(rootValue->toObject());
                return naked_dto;
            }
            return DTO_Evento{};
        } else {
            return std::get<EventoException>(result);
        }
    });
}

QFuture<EventoResult<std::vector<DTO_Feedback>>> EventoNetworkClient::getFeedbackList(EventoID eventoId)
{
    auto url = endpoint(QStringLiteral("/feedback/list"), [&](QUrlQuery params) {
        params.addQueryItem("eventId", QString::number(eventoId));
    });
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<std::vector<DTO_Feedback>> {
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            std::vector<DTO_Feedback> result;
            if (rootValue->isArray()) {
                declare_top_deserialiser(result, deserialiser_holder);
                JsonDeserialise::JsonDeserialiser deserialiser(deserialiser_holder);
                deserialiser.deserialise_array(rootValue->toArray());
            }
            return result;
        } else {
            return std::get<EventoException>(result);
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
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            std::vector<DTO_Slide> result;
            if (rootValue->isArray()) {
                declare_top_deserialiser(result, deserialiser_holder);
                JsonDeserialise::JsonDeserialiser deserialiser(deserialiser_holder);
                deserialiser.deserialise_array(rootValue->toArray());
            }
            return result;
        } else {
            return std::get<EventoException>(result);
        }
    });
}

QFuture<EventoResult<std::vector<DTO_Slide>>> EventoNetworkClient::getHomeSlideList(int size)
{
    auto url = endpoint(QStringLiteral("/slide/home/list"), [&](QUrlQuery params) {
        params.addQueryItem("size", QString::number(size));
    });
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<std::vector<DTO_Slide>> {
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            std::vector<DTO_Slide> result;
            if (rootValue->isArray()) {
                declare_top_deserialiser(result, deserialiser_holder);
                JsonDeserialise::JsonDeserialiser deserialiser(deserialiser_holder);
                deserialiser.deserialise_array(rootValue->toArray());
            }
            return result;
        } else {
            return std::get<EventoException>(result);
        }
    });
}

QFuture<EventoResult<QString>> EventoNetworkClient::getTypeList()
{
    // TODO: implement
    return {};
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
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            return rootValue->toString();
        } else {
            return std::get<EventoException>(result);
        }
    });
}

// eventUpload
QFuture<EventoResult<bool>> EventoNetworkClient::eventCheckin(EventoID event, const QString &code)
{
    auto url = endpoint(QStringLiteral("/event/authcode"), [&](QUrlQuery params) {
        params.addQueryItem("eventId", QString::number(event));
        params.addQueryItem("code", code);
    });
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<bool> {
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            auto msg = rootValue->toString();
            if (msg.contains(QStringLiteral("成功")))
                return true;
            return EventoException(EventoExceptionCode::UnexpectedError, msg);
        } else {
            return std::get<EventoException>(result);
        }
    });
}

QFuture<EventoResult<bool>> EventoNetworkClient::eventFeedback(const DTO_Feedback &feedback)
{
    QUrlQuery params;
    params.addQueryItem("content", feedback.content);
    params.addQueryItem("score", QString::number(feedback.score));
    params.addQueryItem("eventId", QString::number(feedback.eventId));
    auto url = endpoint(QStringLiteral("/feedback/info"));
    return this->post(url, params).then([](EventoResult<QJsonValue> result) -> EventoResult<bool> {
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            auto msg = rootValue->toString();
            if (msg.contains(QStringLiteral("成功")))
                return true;
            return EventoException(EventoExceptionCode::UnexpectedError, msg);
        } else {
            return std::get<EventoException>(result);
        }
    });
}

QFuture<EventoResult<bool>> EventoNetworkClient::eventSubscribe(EventoID event, bool targetState)
{
    auto url = endpoint(QStringLiteral("/user/subscribe"), [&](QUrlQuery params) {
        params.addQueryItem("eventId", QString::number(event));
        params.addQueryItem("isSubscribe", targetState ? QStringLiteral("true") : QStringLiteral("false"));
    });
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<bool> {
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            auto msg = rootValue->toString();
            if (msg.contains(QStringLiteral("成功")))
                return true;
            return EventoException(EventoExceptionCode::UnexpectedError, msg);
        } else {
            return std::get<EventoException>(result);
        }
    });
}

QFuture<EventoResult<bool>> EventoNetworkClient::isFeedback(EventoID event)
{
    auto url = endpoint(QStringLiteral("/feedback/user/info"), [&](QUrlQuery params) {
        params.addQueryItem("eventId", QString::number(event));
    });
    return this->get(url).then([](EventoResult<QJsonValue> result) -> EventoResult<bool> {
        if (auto rootValue = std::get_if<QJsonValue>(&result)) {
            return !rootValue->isNull();
        } else {
            return std::get<EventoException>(result);
        }
    });
}

// adminFetch
QFuture<EventoResult<std::vector<DTO_Evento>>> EventoNetworkClient::getQualifiedEvent(int type, const std::vector<int> &dep, const QDate &day)
{
    // TODO: implement
    return {};
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

QFuture<EventoResult<std::vector<DTO_UserBrief>>> EventoNetworkClient::getEventManagerList(const EventoID &eventoId)
{
    // TODO: implement
    return {};
}

QFuture<EventoResult<std::vector<DTO_UserBrief>>> EventoNetworkClient::getAdminUserList()
{
    // TODO: implement
    return {};
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
