#include "repositoryimpl.h"

QStringList repositoryImpl::get_admin_permission(EventoException &err)
{
    QString permission = readFile(R"(localdata\permission.json)", "all_method_name", std::pair<QString,QString>("user_id", "B22041234"));
    if(permission.isEmpty()){

        return QStringList();
    }
    QStringList res = permission.split(" ");
    return res;
}

QStringList repositoryImpl::get_permitted_event(EventoException &err)
{
    QString permission = readFile(R"(localdata\permission.json)", "event_id", std::pair<QString,QString>("user_id", "B22041234"));
    if(permission.isEmpty()){

        return QStringList();
    }
    QStringList res = permission.split(" ");
    return res;
}

DTO_Permission repositoryImpl::get_event_permission(EventoID event, EventoException &err)
{
    QFile file("localdata/permission.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<< "Can't open the file!";
        return DTO_Permission();
    }
    QByteArray file_str = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(file_str, &jsonError));
    if(jsonError.error == QJsonParseError::NoError && jsonDoc.isArray()){
        QJsonArray jsonArr = jsonDoc.array();
        for(int i = 0; i<jsonArr.count(); i++){
            if(!jsonArr.at(i).toObject().value("user_id").toString().compare("B22041234") &&
                !jsonArr.at(i).toObject().value("event_id").toString().compare(QString::number(event))){
                QJsonObject unit = jsonArr.at(i).toObject();
                return DTO_Permission{
                    unit.value("id").toString().toInt(),
                    unit.value("all_method_name").toString().split(" "),
                    unit.value("user_id").toString(),
                    unit.value("event_id").toString().toInt(),
                    QDateTime::fromString(unit.value("gmt_update").toString(), "yyyy-MM-dd hh:mm:ss")
                };
            }
        }
    }
    return DTO_Permission();
}

std::vector<DTO_Evento> repositoryImpl::get_undertaking_list(EventoException &err)
{
    return readEvento(std::pair<QString, QString>("state", "3"));
}

std::vector<DTO_Evento> repositoryImpl::get_latest_list(EventoException &err)
{
    return readEvento(std::pair<QString, QString>("state", "1"));
}

std::vector<DTO_Evento> repositoryImpl::get_subscribed_list(EventoException &err)
{
    QStringList subscribedEventIds = readFile("localdata/participate.json", "event_id", std::pair<QString,QString>("user_id", "B22041234")).split(" ");
    std::vector<DTO_Evento> res;
    for(QList<QString>::Iterator it = subscribedEventIds.begin(); it!=subscribedEventIds.end();it++){
        std::vector<DTO_Evento> tempVector = readEvento(std::pair("id", *it));
        res.insert(res.end(), tempVector.begin(), tempVector.end());
    }
    return res;
}

DTO_Evento repositoryImpl::get_event(EventoID event, EventoException &err)
{
    std::vector<DTO_Evento> eventTemp = readEvento(std::pair<QString, QString>("id", QString::number(event)));
    return eventTemp.at(0);
}

std::vector<DTO_Feedback> repositoryImpl::get_feedback_list(EventoException &err)
{
    QFile file("localdata/feedback.json");
    std::vector<DTO_Feedback> res;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<< "Can't open the file!";
        return res;
    }
    QByteArray file_str = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(file_str, &jsonError));
    if(jsonError.error == QJsonParseError::NoError && jsonDoc.isArray()){
        QJsonArray jsonArr = jsonDoc.array();
        for(int i = 0; i<jsonArr.count(); i++){
            QJsonObject unit = jsonArr.at(i).toObject();
            QString participateId = unit.value("participate_id").toString();
            std::vector<Participation> participationList = readParticipation(std::pair<QString, QString>("id", participateId));
            res.push_back(DTO_Feedback{
                participationList.at(0).event_id,
                participationList.at(0).user_id,
                unit.value("score").toString().toInt(),
                unit.value("content").toString(),
                participationList.at(0).participationStatus
            });
        }
    }
    return res;
}

std::vector<DTO_Slide> repositoryImpl::get_slide_list(EventoException &err)
{
    std::vector<DTO_Slide> res;
    QFile file("localdata/slide.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<< "Can't open the file!";
        return res;
    }
    QByteArray file_str = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(file_str, &jsonError));
    if(jsonError.error == QJsonParseError::NoError && jsonDoc.isArray()){
        QJsonArray jsonArr = jsonDoc.array();
        for(int i = 0; i<jsonArr.count(); i++){
            QJsonObject unit = jsonArr.at(i).toObject();
            res.push_back(DTO_Slide{
                unit.value("id").toString().toInt(),
                unit.value("title").toString(),
                unit.value("link").toString(),
                unit.value("url").toString()
            });
        }
    }
    return res;
}

bool repositoryImpl::event_checkin(EventoID event, const QString &code, EventoException &err)
{
    std::vector<Participation> participationList = readParticipation(std::pair<QString, QString>("event_id", QString::number(event)));
    for(int i = 0; i<participationList.size(); i++){
        if(!participationList.at(i).user_id.compare("B22041234")){
            if(participationList.at(i).participationStatus.isParticipated){
                qDebug()<<"ab";
                return false;
            }
            else{
                qDebug()<<"a";
                if(writeParticipation("is_participate", "true", event)){
                    return true;
                }
            }
        }
    }
    qDebug()<<participationList.size();
    return false;
}

bool repositoryImpl::event_feedback(const DTO_Feedback &code, EventoException &err)
{
    QFile participationFile("localdata/participate.json");
    if(!participationFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<< "Can't open the file!";
        return false;
    }
    QByteArray participationFile_str = participationFile.readAll();
    participationFile.close();

    QString participationId;
    QJsonParseError jsonError;
    QJsonDocument participationJsonDoc(QJsonDocument::fromJson(participationFile_str, &jsonError));
    QJsonArray participationJsonArr;
    if(jsonError.error == QJsonParseError::NoError){
        participationJsonArr = participationJsonDoc.array();
        for(int i = 0; i < participationJsonArr.count(); i++){
            if(!participationJsonArr.at(i).toObject().value("event_id").toString().compare(QString::number(code.event)) &&
                !participationJsonArr.at(i).toObject().value("user_id").toString().compare("B22041234")){
                participationId = participationJsonArr.at(i).toObject().value("id").toString();
                break;
            }
        }
    }

    QFile feedbackFile("localdata/feedback.json");
    if(!feedbackFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<< "Can't open the file(localdata/feedback.json)!";
        return false;
    }
    QByteArray feedbackFile_str = feedbackFile.readAll();
    feedbackFile.close();

    QJsonDocument feedbackJsonDoc(QJsonDocument::fromJson(feedbackFile_str, &jsonError));
    QJsonArray feedbackJsonArr;
    if(jsonError.error == QJsonParseError::NoError){
        feedbackJsonArr = feedbackJsonDoc.array();
        for(int i = 0; i < feedbackJsonArr.count(); i++){
            if(!feedbackJsonArr.at(i).toObject().value("participate_id").toString().compare(participationId)){
                QJsonObject feedbackObj_temp;
                feedbackObj_temp.insert("id", QString::number(feedbackJsonArr.count() + 1));
                feedbackObj_temp.insert("score", QString::number(code.score));
                feedbackObj_temp.insert("content", code.content);
                feedbackObj_temp.insert("participate_id", participationId);
                feedbackObj_temp.insert("user_id", "B22041234");
                feedbackJsonArr.append(feedbackObj_temp);

                QFile wFile("localdata/feedback.json");
                if(!wFile.open(QIODevice::WriteOnly | QIODevice::Text)){
                    qDebug()<< "Can't open the file(localdata/feedback.json)!";
                    return false;
                }
                feedbackJsonDoc.setArray(feedbackJsonArr);
                wFile.seek(0);
                wFile.write(feedbackJsonDoc.toJson());
                wFile.flush();
                wFile.close();
                return true;
            }
        }
    }
    return false;
}

bool repositoryImpl::event_subscribe(EventoID event, EventoException &err)
{
    std::vector<Participation> participationList = readParticipation(std::pair<QString, QString>("event_id", QString::number(event)));
    for(int i = 0; i<participationList.size(); i++){
        if(!participationList.at(i).user_id.compare("B22041234")){
            if(participationList.at(i).participationStatus.isSubscribed){
                return false;
            }
            else{
                if(writeParticipation("is_subscribe", "true", event)){
                    return true;
                }
            }
        }
    }
    return false;
}

std::vector<DTO_Evento> repositoryImpl::get_qualified_event(int type, std::vector<int> dep, QDate day, EventoException &err)
{
    std::vector<DTO_Evento> res;
    std::vector<DTO_Evento> eventoList = readEvento(std::pair<QString, QString>("type_id", QString::number(type)));
    for(int i = 0; i < eventoList.size(); i++){
        QString day_str = eventoList.at(i).gmtEventStart.date().toString("yyyy-MM-dd hh:mm:ss").split(" ").at(0);
        QDate day_temp = QDate::fromString(day_str, "yyyy-MM-dd");
        int eventId = eventoList.at(i).id;
        if(day_temp == day){
            for(std::vector<int>::iterator it = dep.begin(); it != dep.end(); it++){
                if(eventDepartmentMatch(eventId, *it)){
                    res.push_back(eventoList.at(i));
                }
            }
        }
    }
    return res;
}

repositoryImpl::repositoryImpl()
{

}
