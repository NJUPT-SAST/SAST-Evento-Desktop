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
    QByteArray file_str = readString("localdata/permission.json");
    if(file_str.isEmpty()){
        return DTO_Permission();
    }

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

DTO_User repositoryImpl::get_user_info(const UserID &id, EventoException &err)
{
    QByteArray file_str = readString("localdata/user.json");
    if(file_str.isEmpty()){
        return DTO_User();
    }

    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(file_str, &jsonError));
    if(jsonError.error == QJsonParseError::NoError && jsonDoc.isArray()){
        QJsonArray jsonArr = jsonDoc.array();
        for(int i = 0; i<jsonArr.count(); i++){
            if(!jsonArr.at(i).toObject().value("id").toString().compare("B22041234")){
                std::vector<Department> departmentList;
                QStringList departmentList_str = jsonArr.at(i).toObject().value("department").toString().split(" ");
                for(int j = 0; j<departmentList_str.count(); j++){
                    departmentList.push_back(readDepartment(departmentList_str.at(j)));
                }

                return DTO_User{
                    id,
                    jsonArr.at(i).toObject().value("name").toString(),
                    jsonArr.at(i).toObject().value("avatar").toString(),
                    jsonArr.at(i).toObject().value("email").toString(),
                    jsonArr.at(i).toObject().value("description").toString(),
                    readPermission(id),
                    departmentList
                };
            }
        }
    }
    return DTO_User();
}

std::vector<DTO_Slide> repositoryImpl::get_home_slide_list(const int &size, EventoException &err)
{
    std::vector<DTO_Slide> res;
    QByteArray file_str = readString("localdata/slide.json");
    if(file_str.isEmpty()){
        return res;
    }

    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(file_str, &jsonError));
    if(jsonError.error == QJsonParseError::NoError && jsonDoc.isArray()){
        QJsonArray jsonArr = jsonDoc.array();
        int countNum;
        if(size>jsonArr.count()){
            countNum = jsonArr.count();
        }
        else{
            countNum = size;
        }
        for(int i = 0; i<countNum; i++){
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

std::vector<DTO_Evento> repositoryImpl::get_history_list(EventoException &err)
{
    std::vector<DTO_Evento> res;
    QByteArray file_str = readString("localdata/participate.json");
    if(file_str.isEmpty()){
        return res;
    }

    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(file_str, &jsonError));
    if(jsonError.error == QJsonParseError::NoError && jsonDoc.isArray()){
        QJsonArray jsonArr = jsonDoc.array();
        for(int i = 0; i<jsonArr.count(); i++){
            if(!jsonArr.at(i).toObject().value("is_participate").toString().compare("true")){
                std::vector<DTO_Evento> temp = readEvento(std::pair<QString, QString>("id", jsonArr.at(i).toObject().value("event_id").toString()));
                res.insert(res.end(), temp.begin(), temp.end());
            }
        }
    }
    return res;
}

std::vector<DTO_Evento> repositoryImpl::get_event_list(const int &page, const int &size, EventoException &err)
{
    std::vector<DTO_Evento> res;
    int beginId = (page-1) * size +1;
    int endId = beginId + (size-1);

    QByteArray file_str = readString("localdata/event.json");
    if(file_str.isEmpty()){
        return res;
    }

    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(file_str, &jsonError));
    if(jsonError.error == QJsonParseError::NoError && jsonDoc.isArray()){
        QJsonArray jsonArr = jsonDoc.array();
        if(beginId>jsonArr.count()){
            return res;
        }
        if(endId > jsonArr.count()){
            endId = jsonArr.count();
        }
        for(int i = beginId; i <= endId; i++){
            std::vector<DTO_Evento> temp = readEvento(std::pair("id", jsonArr.at(i-1).toObject().value("id").toString()));
            res.insert(res.end(), temp.begin(), temp.end());
        }
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
    std::vector<DTO_Feedback> res;
    QByteArray file_str = readString("localdata/feedback.json");
    if(file_str.isEmpty()){
        return res;
    }

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
    QByteArray file_str = readString("localdata/slide.json");
    if(file_str.isEmpty()){
        return std::vector<DTO_Slide>();
    }

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

std::vector<DTO_Slide> repositoryImpl::get_event_slide_list(EventoID id, EventoException &err)
{
    std::vector<DTO_Slide> res;
    QByteArray file_str = readString("localdata/slide.json");
    if(file_str.isEmpty()){
        return std::vector<DTO_Slide>();
    }

    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(file_str, &jsonError));
    if(jsonError.error == QJsonParseError::NoError && jsonDoc.isArray()){
        QJsonArray jsonArr = jsonDoc.array();
        for(int i = 0; i<jsonArr.count(); i++){
            QJsonObject unit = jsonArr.at(i).toObject();
            if(!unit.value("event_id").toString().compare(QString::number(id))){
                res.push_back(DTO_Slide{
                    unit.value("id").toString().toInt(),
                    unit.value("title").toString(),
                    unit.value("link").toString(),
                    unit.value("url").toString()
                });
            }
        }
    }
    return res;
}

std::vector<EventType> repositoryImpl::get_type_list(const int &page, const int &size, EventoException &err)
{
    // FIXME: implement
    return std::vector<EventType>();
}

std::vector<Location> repositoryImpl::get_location_list(EventoException &err)
{
    std::vector<Location> res;
    QByteArray file_str = readString("localdata/location.json");

    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(file_str, &jsonError));
    if(jsonError.error == QJsonParseError::NoError && jsonDoc.isArray()){
        QJsonArray jsonArr = jsonDoc.array();
        for(int i = 0; i<jsonArr.count(); i++){
            QJsonObject unit = jsonArr.at(i).toObject();
            res.push_back(Location{
                unit.value("id").toString().toInt(),
                unit.value("location_name").toString(),
                unit.value("parent_id").toString().toInt()
            });
        }
    }
    return res;
}

QString repositoryImpl::get_qrcode(const int &eventId, EventoException &err)
{
    return "qrcodeLink";
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
    QByteArray participationFile_str = readString("localdata/participate.json");
    if(participationFile_str.isEmpty()){
        return false;
    }

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

    QByteArray feedbackFile_str = readString("localdata/feedback.json");
    if(feedbackFile_str.isEmpty()){
        return false;
    }

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

std::vector<DTO_Evento> repositoryImpl::get_qualified_event(int type, const std::vector<int> &dep, const QDate &day, EventoException &err)
{
    std::vector<DTO_Evento> res;
    std::vector<DTO_Evento> eventoList = readEvento(std::pair<QString, QString>("type_id", QString::number(type)));
    for(int i = 0; i < eventoList.size(); i++){
        QString day_str = eventoList.at(i).gmtEventStart.date().toString("yyyy-MM-dd hh:mm:ss").split(" ").at(0);
        QDate day_temp = QDate::fromString(day_str, "yyyy-MM-dd");
        int eventId = eventoList.at(i).id;
        if(day_temp == day){
            for(int j = 0; j < dep.size(); j++){
                if(eventDepartmentMatch(eventId, dep.at(j))){
                    res.push_back(eventoList.at(i));
                }
            }
        }
    }
    return res;
}

QStringList repositoryImpl::get_action_state_list(EventoException &err)
{
    // FIXME: implement
    return QStringList();
}

QStringList repositoryImpl::get_action_list(EventoException &err)
{
    // FIXME: implement
    return QStringList();
}
