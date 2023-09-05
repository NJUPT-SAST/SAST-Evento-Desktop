#ifndef EVENTO_NETWORK_CLIENT_H
#define EVENTO_NETWORK_CLIENT_H
#include <QByteArray>
#include <QFuture>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QUrlQuery>
#include <evento_exception.h>
#include <dto/user.h>

class EventoNetworkClient
{
private:
    QNetworkAccessManager manager;
    QByteArray tokenBytes;

protected:
    QUrl endpoint(const QString &endpoint);
    QUrl endpoint(const QString &endpoint, const QUrlQuery &params);

    template <typename TParamsBuilder, std::enable_if_t<std::is_invocable_v<TParamsBuilder, QUrlQuery&>, int> = 0>
    QUrl endpoint(const QString &endpoint, TParamsBuilder paramsBuilder)
    {
        QUrlQuery query;
        paramsBuilder(query);
        return this->endpoint(endpoint, query);
    }

    QFuture<std::variant<QJsonValue, EventoException>> get(const QUrl &url);

    QFuture<std::variant<QJsonValue, EventoException>> post(const QUrl &url, const QString &contentType, const QByteArray &requestData);
    QFuture<std::variant<QJsonValue, EventoException>> post(const QUrl &url, const QUrlQuery &requestData);
    QFuture<std::variant<QJsonValue, EventoException>> post(const QUrl &url, const QJsonDocument &requestData);

    QFuture<std::variant<QJsonValue, EventoException>> put(const QUrl &url, const QString &contentType, const QByteArray &requestData);
    QFuture<std::variant<QJsonValue, EventoException>> put(const QUrl &url, const QUrlQuery &requestData);
    QFuture<std::variant<QJsonValue, EventoException>> put(const QUrl &url, const QJsonDocument &requestData);

    QFuture<std::variant<QJsonValue, EventoException>> patch(const QUrl &url, const QString &contentType, const QByteArray &requestData);
    QFuture<std::variant<QJsonValue, EventoException>> patch(const QUrl &url, const QUrlQuery &requestData);
    QFuture<std::variant<QJsonValue, EventoException>> patch(const QUrl &url, const QJsonDocument &requestData);

    QFuture<std::variant<QJsonValue, EventoException>> deleteResource(const QUrl &url);

public:
    QFuture<std::variant<DTO_User, EventoException>> get_user_info(const UserID &id);

    EventoNetworkClient();
};
#endif // EVENTO_NETWORK_CLIENT_H