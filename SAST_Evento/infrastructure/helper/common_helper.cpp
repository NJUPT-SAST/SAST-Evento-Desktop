#include "common_helper.h"
#include <QGuiApplication>
#include <QTimer>

QRegularExpression Reg_JsonNonNull("/(?:,\"\\w+\":(?:null|""))|(?:\"\\w+\":(?:null|""),)|(?:\"\\w+\":(?:null|""))/g");

CommonHelper* CommonHelper::m_instance = nullptr;

CommonHelper *CommonHelper::getInstance()
{
    if(CommonHelper::m_instance == nullptr){
        CommonHelper::m_instance = new CommonHelper;
    }
    return CommonHelper::m_instance;
}

CommonHelper::CommonHelper(QObject *parent) : QObject(parent)
{

}

QString CommonHelper::maxString(QString text,int max){
    if(text.length()>max){
        return text.mid(0,max)+"...";
    }
    return text;
}

bool CommonHelper::isJson(QString val)
{
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8(), &err);
    if (doc.isNull() || err.error != QJsonParseError::NoError)
    {
        return false;
    }
    return true;
}

QString CommonHelper::toBase64(QString text)
{
    return text.toUtf8().toBase64();
}

QString CommonHelper::fromBase64(QString text)
{
    return QByteArray::fromBase64(text.toUtf8());
}

QString CommonHelper::md5(QString text)
{
    return QCryptographicHash::hash(text.toUtf8(), QCryptographicHash::Md5).toHex();
}

QString CommonHelper::sha1(QString text)
{
    return QCryptographicHash::hash(text.toUtf8(), QCryptographicHash::Sha1).toHex();
}

QString CommonHelper::sha224(QString text)
{
    return QCryptographicHash::hash(text.toUtf8(), QCryptographicHash::Sha224).toHex();
}

QString CommonHelper::sha256(QString text)
{
    return QCryptographicHash::hash(text.toUtf8(), QCryptographicHash::Sha256).toHex();
}

QString CommonHelper::sha384(QString text)
{
    return QCryptographicHash::hash(text.toUtf8(), QCryptographicHash::Sha384).toHex();
}

QString CommonHelper::sha512(QString text)
{
    return QCryptographicHash::hash(text.toUtf8(), QCryptographicHash::Sha512).toHex();
}

qint64 CommonHelper::currentTimeMillis()
{
    return QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
}

QJsonObject CommonHelper::json2Object(QString val){
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(val.toUtf8(), &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        return doucment.object();
    }
    return {};
}

QString CommonHelper::object2Json(QJsonObject val){
    QJsonDocument doc(val);
    return QString(doc.toJson(QJsonDocument::Indented));
}

void CommonHelper::jsonNonNull(QString val){
    val.replace(Reg_JsonNonNull,"");
}

void CommonHelper::restart(){
    qApp->exit(931);
}
