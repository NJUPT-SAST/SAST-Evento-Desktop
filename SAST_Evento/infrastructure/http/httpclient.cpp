#include "httpclient.h"

HttpClient *HttpClient::header(const QString &key, const QVariant &value)
{
    headers.insert(key, value);
    return this;
}

HttpClient *HttpClient::timeout(const int &time)
{
    timeoutSecond = time;
    return this;
}

HttpClient *HttpClient::setHeaders(QNetworkRequest &request)
{
    QMap<QString, QVariant>::Iterator it;
    for(it = headers.begin(); it != headers.end(); it++){
        request.setRawHeader(QByteArray(it.key().toStdString().data()), QByteArray(it.value().toString().toStdString().data()));
    }
    return this;
}

HttpClient::HttpClient(QObject* parent) : QNetworkAccessManager(parent)
{

}

HttpRequest::HttpRequest(HttpClient *client){
    this->m_httpClient = client;
}

QNetworkReply& HttpRequest::post()
{
    if(m_isJson){
        reply = m_httpClient->post(m_request, QString::fromStdString(j_data.dump()).toStdString().data());
    }
    else{
        //TODO
    }
    return *reply;
}
