#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMap>

#include <infrastructure/nlohmann/json.hpp>

class HttpClient : public QNetworkAccessManager
{
public:
    static HttpClient* getInstance(){
        static HttpClient instance;
        return &instance;
    }
    HttpClient* header(const QString &key, const QVariant &value);
    HttpClient* timeout(const int &time);

    HttpClient* setHeaders(QNetworkRequest &request);

    QNetworkReply* exec(const QNetworkRequest &request, const QVariant &data, const QNetworkReply &response, const bool &isJson);

private:
    HttpClient(QObject* parent = nullptr);

    QMap<QString, QVariant> headers;
    int timeoutSecond = 60;
};

class HttpRequest : public QObject{
    Q_OBJECT
public:
    HttpRequest(HttpClient *client);

    HttpRequest* data(const QVariant &data){
        this->m_data = data;
        return this;
    }

    HttpRequest* data(const nlohmann::json &data){
        this->j_data = data;
        return this;
    }

    HttpRequest* url(const QString &url){
        this->m_request.setUrl(QUrl(url));
        return this;
    }

    HttpRequest* header(const QString &key, const QVariant &value){
        this->m_request.setRawHeader(QByteArray(key.toStdString().data()), QByteArray(value.toString().toStdString().data()));
        return this;
    }

    HttpRequest* contentType(QVariant contentType){
        m_request.setHeader(QNetworkRequest::ContentTypeHeader, contentType);
    }

    HttpRequest* isJson(bool isJson){
        m_isJson = isJson;
    }

    QNetworkReply& post();

signals:
    void finish();

private:
    QNetworkRequest m_request;
    QNetworkReply *reply = nullptr;
    HttpClient* m_httpClient = nullptr;
    QVariant m_data;
    nlohmann::json j_data;
    bool m_isJson = true;
};

#endif // HTTPCLIENT_H
