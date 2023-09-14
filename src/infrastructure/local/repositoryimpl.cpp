#include "repositoryimpl.h"

QStringList repositoryImpl::getAdminPermission(EventoException &err)
{
    QByteArray file_str = admin_user_data;

    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(file_str, &jsonError));
    if(jsonError.error == QJsonParseError::NoError && jsonDoc.isArray()){
        QJsonArray jsonArr = jsonDoc.array();
        for(int i = 0; i<jsonArr.count(); i++){
            if(!jsonArr.at(i).toString().compare("B22041234")){
                return adminPerission;
            }
        }
        return QStringList();
    }
    err = EventoException(EventoExceptionCode::UnexpectedError, "get_admin_permission json error");
    return QStringList();
}

QStringList repositoryImpl::getManagerPermission(const EventoID &eventoId, EventoException &err)
{
    for(int i = 0; i<manager_user_data_list.size(); i++){
        if(!manager_user_data_list.at(i).event_id.compare(QString::number(eventoId)) &&
            manager_user_data_list.at(i).manager_id.split(" ").contains("B22041234")){
            return managerPerission;
        }
    }
    err = EventoException(EventoExceptionCode::UnexpectedError, "get_manager_permission json error");
    return QStringList();
}

QStringList repositoryImpl::getPermittedEvent(EventoException &err)
{
    QStringList res;
    for(int i = 0; i<permission_data_list.size(); i++){
        if(!permission_data_list.at(i).user_id.compare("B22041234")){
            res.append(permission_data_list.at(i).event_id.split(" "));
        }
    }
    return res;
}

DTO_Permission repositoryImpl::getEventPermission(EventoID event, EventoException &err)
{
    for(int i = 0; i<permission_data_list.size(); i++){
        if(!permission_data_list.at(i).user_id.compare("B22041234") &&
            !permission_data_list.at(i).event_id.compare(QString::number(event))){
            permission_data unit = permission_data_list.at(i);
            return DTO_Permission {
                unit.all_method_name.split(" "),
                unit.event_id.toInt(),
            };
        }
    }
    err = EventoException(EventoExceptionCode::UnexpectedError, "get_event_permission json error");
    return DTO_Permission();
}

DTO_User repositoryImpl::getUserInfo(const UserID &id, EventoException &err)
{
    for(int i = 0; i<user_data_list.size(); i++){
        if(!user_data_list.at(i).id.compare("B22041234")){
            std::vector<Department> departmentList;
            QStringList departmentList_str = user_data_list.at(i).department.split(" ");
            for(int j = 0; j<departmentList_str.count(); j++){
                departmentList.push_back(readDepartment(departmentList_str.at(j)));
            }

            return DTO_User{
                id,
                user_data_list.at(i).name,
                user_data_list.at(i).avatar,
                user_data_list.at(i).email,
                user_data_list.at(i).description,
                readPermission(id),
                departmentList
            };
        }
    }
    err = EventoException(EventoExceptionCode::UnexpectedError, "get_user_info json error");
    return DTO_User();
}

std::vector<DTO_Slide> repositoryImpl::getHomeSlideList(const int &size, EventoException &err)
{
    std::vector<DTO_Slide> res;

    int countNum;
    if(size>slide_data_list.size()){
        countNum = slide_data_list.size();
    }
    else{
        countNum = size;
    }
    for(int i = 0; i < countNum; i++){
        slide_data unit = slide_data_list.at(i);
        res.push_back(DTO_Slide{
            unit.id.toInt(),
            unit.event_id.toInt(),
            unit.title,
            unit.link,
            unit.url
        });
    }
    return res;
}

ParticipationStatus repositoryImpl::getUserParticipate(const EventoID &eventoId, EventoException& err)
{
    for(int i = 0; i<participate_data_list.size(); i++){
        participate_data unit = participate_data_list.at(i);
        if(!unit.event_id.compare(QString::number(eventoId)) &&
            !unit.user_id.compare("B22041234")){
            return ParticipationStatus{
                unit.is_registration.compare("false")?true:false,
                unit.is_participate.compare("false")?true:false,
                unit.is_subscribe.compare("false")?true:false,
            };
        }
    }
    err = EventoException(EventoExceptionCode::UnexpectedError, "get_user_participate json error");
    return ParticipationStatus();
}

DTO_Feedback repositoryImpl::getFeedbackInfo(const EventoID &eventoId, EventoException& err)
{
    for(int i = 0; i<feedback_data_list.size(); i++){
        Participation unit = readParticipation(std::pair("id", feedback_data_list.at(i).participate_id)).at(0);
        if((!feedback_data_list.at(i).user_id.compare("B22041234")) &&
            (unit.event_id == eventoId)){
            feedback_data feedback_unit = feedback_data_list.at(i);
            return DTO_Feedback{
                i,
                eventoId,
                feedback_unit.score.toInt(),
                feedback_unit.content
            };
        }
    }
    err = EventoException(EventoExceptionCode::Ok);
    return DTO_Feedback();
}

QFuture<EventoResult<std::vector<DTO_Evento>>> repositoryImpl::getUndertakingList()
{
    return readEventoByState("3");
}

QFuture<EventoResult<std::vector<DTO_Evento>>> repositoryImpl::getLatestList()
{
    return readEventoByState("1");
}

QFuture<EventoResult<std::vector<DTO_Evento>>> repositoryImpl::getRegisteredList()
{
    return QtConcurrent::run([this]{
        std::vector<DTO_Evento> res;

        for (int i = 0; i < participate_data_list.size(); i++) {
            if (!participate_data_list.at(i).user_id.compare("B22041234") && !participate_data_list.at(i).is_registration.compare("true")) {
                res.push_back(readEvento(participate_data_list.at(i).event_id.toInt()));
            }
        }

        return EventoResult(std::move(res));
    });
}

QFuture<EventoResult<std::vector<DTO_Evento>>> repositoryImpl::getSubscribedList()
{
    return QtConcurrent::run([this]{
        std::vector<DTO_Evento> res;

        for(int i = 0; i<participate_data_list.size(); i++) {
            if(!participate_data_list.at(i).user_id.compare("B22041234")
                && !participate_data_list.at(i).is_subscribe.compare("true")) {
                res.push_back(readEvento(participate_data_list.at(i).event_id.toInt()));
            }
        }

        return EventoResult(std::move(res));
    });
}

QFuture<EventoResult<std::vector<DTO_Evento>>> repositoryImpl::getHistoryList()
{
    return QtConcurrent::run([this]{
        std::vector<DTO_Evento> res;

        for(int i = 0; i<participate_data_list.size(); i++) {
            if(!participate_data_list.at(i).is_participate.compare("true")) {
                res.push_back(readEvento(participate_data_list.at(i).event_id.toInt()));
            }
        }

        return EventoResult(std::move(res));
    });
}

QFuture<EventoResult<std::vector<DTO_Evento>>> repositoryImpl::getEventListInPage(int page, int size)
{
    return QtConcurrent::run([=]{
        std::vector<DTO_Evento> res;
        int beginId = (page - 1) * size +1;
        int endId = beginId + (size - 1);

        if(beginId > event_data_list.size()){
            return EventoResult<std::vector<DTO_Evento>>(EventoExceptionCode::UnexpectedError, "count too big");
        }
        if(endId > event_data_list.size()){
            endId = event_data_list.size();
        }
        for(int i = beginId; i <= endId; i++){
            res.push_back(readEvento(event_data_list.at(i-1).id.toInt()));
        }

        return EventoResult(std::move(res));
    });
}

QFuture<EventoResult<std::vector<DTO_Evento>>> repositoryImpl::getDepartmentEventList(int departmentId)
{
    return QtConcurrent::run([=]{
        std::vector<DTO_Evento> res;

        for(int i = 0; i < event_data_list.size(); i++) {
            if (eventDepartmentMatch(event_data_list.at(i).id.toInt(), departmentId)) {
                res.push_back(readEvento(event_data_list.at(i).id.toInt()));
            }
        }

        return EventoResult(std::move(res));
    });
}

QFuture<EventoResult<DTO_Evento>> repositoryImpl::getEventById(EventoID event)
{
    return QtConcurrent::run([=]{
        return EventoResult(std::move(readEvento(event)));
    });
}

std::vector<DTO_Feedback> repositoryImpl::getFeedbackList(EventoID eventoId, EventoException &err)
{
    std::vector<DTO_Feedback> res;

    for(int i = 0; i<feedback_data_list.size(); i++) {
        feedback_data unit = feedback_data_list.at(i);
        QString participateId = unit.participate_id;
        std::vector<Participation> participationList = readParticipation(std::pair<QString, QString>("id", participateId));
        if(participationList.at(0).event_id == eventoId){
            res.push_back(DTO_Feedback{
                i,
                participationList.at(0).event_id,
                unit.score.toInt(),
                unit.content
            });
        }
    }
    return res;
}

std::vector<DTO_Slide> repositoryImpl::getSlideList(EventoException &err)
{
    std::vector<DTO_Slide> res;

    for(int i = 0; i<slide_data_list.size(); i++) {
        slide_data unit = slide_data_list.at(i);
        res.push_back(DTO_Slide {
            unit.id.toInt(),
            unit.event_id.toInt(),
            unit.title,
            unit.link,
            unit.url
        });
    }
    return res;
}

std::vector<DTO_Slide> repositoryImpl::getEventSlideList(EventoID id, EventoException &err)
{
    std::vector<DTO_Slide> res;

    for(int i = 0; i<slide_data_list.size(); i++) {
        slide_data unit = slide_data_list.at(i);
        if(!unit.event_id.compare(QString::number(id))){
            res.push_back(DTO_Slide{
                unit.id.toInt(),
                unit.event_id.toInt(),
                unit.title,
                unit.link,
                unit.url
            });
        }
    }
    return res;
}

QString repositoryImpl::getTypeList(EventoException &err)
{
    QJsonArray res;
    for(int i = 0; i<type_data_list.size(); i++) {
        type_data unit = type_data_list.at(i);
        QJsonObject item;
        item.insert("id", unit.id.toInt());
        item.insert("name", unit.type_name);
        res.push_back(item);
    }
    return QString(QJsonDocument(res).toJson(QJsonDocument::Compact).toStdString().c_str());
}

QString repositoryImpl::getLocationList(EventoException &err)
{
    QJsonArray res;

    for(int i = 0; i<location_data_list.size(); i++) {
        if(!location_data_list.at(i).parent_id.compare("0")){
            res.push_back(formatToTree(location_data_list,
                                       location_data_list.at(i).id,
                                       location_data_list.at(i).location_name));
        }
    }
    return QString(QJsonDocument(res).toJson(QJsonDocument::Compact).toStdString().c_str());
}

QString repositoryImpl::getDepartmentList(EventoException &err)
{
    QJsonArray res;

    for(int i = 0; i<department_data_list.size(); i++){
        department_data unit = department_data_list.at(i);
        QJsonObject item;
        item.insert("id", unit.id.toInt());
        item.insert("name", unit.department_name);
        res.push_back(item);
    }
    return QString(QJsonDocument(res).toJson(QJsonDocument::Compact).toStdString().c_str());
}

QString repositoryImpl::getQRCode(const int &eventId, EventoException &err)
{
    return "qrcodeLink";
}

QFuture<EventoResult<bool>> repositoryImpl::checkIn(EventoID event, const QString &code)
{
    return QtConcurrent::run([=]{
        std::vector<Participation> participationList = readParticipation(std::pair<QString, QString>("event_id", QString::number(event)));

        for(int i = 0; i<participationList.size(); i++) {
            if(participationList.at(i).user_id.compare("B22041234"))
                break;
            if (participationList.at(i).participationStatus.isParticipated) {
                return EventoResult<bool>(EventoExceptionCode::UnexpectedError, "has checkin");
            }
            else {
                if (writeParticipation("is_participate", "true", event)) {
                    return EventoResult();
                }
            }

        }
        return EventoResult<bool>(EventoExceptionCode::UnexpectedError, "not participation");
    });
}

bool repositoryImpl::feedbackEvent(const DTO_Feedback &code, EventoException &err)
{
    QString participationId;
    for(int i = 0; i < participate_data_list.size(); i++){
        if(!participate_data_list.at(i).event_id.compare(QString::number(code.eventId)) &&
            !participate_data_list.at(i).user_id.compare("B22041234")) {
            participationId = participate_data_list.at(i).id;
            break;
        }
    }

    for(int i = 0; i < feedback_data_list.size(); i++){
        if(!feedback_data_list.at(i).participate_id.compare(participationId)){
            err = EventoException(EventoExceptionCode::UnexpectedError, "has feedback");
            return false;
        }
    }
    feedback_data_list.push_back(feedback_data{
        code.content,
        QString::number(feedback_data_list.size() + 1),
        participationId,
        QString::number(code.score),
        "B22041234"
    });
    return true;
}

QFuture<EventoResult<bool>> repositoryImpl::subscribe(EventoID event)
{
    return QtConcurrent::run([=]{
        std::vector<Participation> participationList = readParticipation(std::pair<QString, QString>("event_id", QString::number(event)));

        for(int i = 0; i<participationList.size(); i++) {
            if (participationList.at(i).user_id.compare("B22041234"))
                break;
            if (participationList.at(i).participationStatus.isSubscribed) {
                return EventoResult<bool>(EventoExceptionCode::UnexpectedError, "has Subscribed");
            }
            else {
                if(writeParticipation("is_subscribe", "true", event)){
                    return EventoResult();
                }
            }

        }

        return EventoResult<bool>(EventoExceptionCode::UnexpectedError, "no user or file error");
    });
}

QFuture<EventoResult<bool>> repositoryImpl::hasFeedbacked(EventoID event)
{
    return QtConcurrent::run([=]{
        EventoException error(EventoExceptionCode::Ok, "null");
        DTO_Feedback feedbackList = getFeedbackInfo(event, error);
        return EventoResult(std::move(error));
    });
}

std::vector<DTO_Evento> repositoryImpl::getQualifiedEvent(EventoException& err, int type, const std::vector<int> &dep, const QDate &day)
{
    std::vector<DTO_Evento> res;
    std::vector<DTO_Evento> eventoList;
    if(type == -1) {
        eventoList = readAllEvento();
    }
    else {
        eventoList = readEventoByType(QString::number(type));
    }

    for(int i = 0; i < eventoList.size(); i++){
        QString day_str = eventoList.at(i).gmtEventStart.date().toString("yyyy-MM-dd hh:mm:ss").split(" ").at(0);
        QDate day_temp = QDate::fromString(day_str, "yyyy-MM-dd");
        int eventId = eventoList.at(i).id;
        if(day.isNull() || day_temp == day){
            if(dep.empty()){
                res.push_back(eventoList.at(i));
            }
            else{
                for(int j = 0; j < dep.size(); j++){
                    if(eventDepartmentMatch(eventId, dep.at(j))){
                        res.push_back(eventoList.at(i));
                    }
                }
            }
        }
    }
    return res;
}

QStringList repositoryImpl::getActionStateList(EventoException &err)
{
    return QStringList{
                       "ADMIN",
                       "MANAGER",
                       "PUBLIC",
                       "LOGIN",
                       "INVISIBLE"
    };
}

QStringList repositoryImpl::getActionList(EventoException &err)
{
    // FIXME: implement
    return QStringList();
}

std::vector<DTO_UserBrief> repositoryImpl::getEventManagerList(const EventoID &eventoId, EventoException& err)
{
    std::vector<DTO_UserBrief> res;

    for(int i = 0; i<manager_user_data_list.size(); i++){
        if(!manager_user_data_list.at(i).event_id.compare(QString::number(eventoId))){
            QStringList ids = manager_user_data_list.at(i).manager_id.split(" ");
            for(int j = 0; j<ids.count(); j++){
                res.push_back(readUserBrief(ids.at(j)));
            }
            return res;
        }
    }
    err = EventoException(EventoExceptionCode::UnexpectedError, "get_event_manager_list json error");
    return res;
}

std::vector<DTO_UserBrief> repositoryImpl::getAdminUserList(EventoException &err)
{
    std::vector<DTO_UserBrief> res;
    QByteArray file_str = admin_user_data;

    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(file_str, &jsonError));
    if(jsonError.error == QJsonParseError::NoError && jsonDoc.isArray()){
        QJsonArray jsonArr = jsonDoc.array();
        for(int i = 0; i < jsonArr.count(); i++){
            res.push_back(readUserBrief(jsonArr.at(i).toString()));
        }
    }
    return res;
}

QString repositoryImpl::getAdminPermissionTreeData(EventoException &err)
{
    return QString(QJsonDocument::fromJson(admin_permission_data).toJson(QJsonDocument::Compact).toStdString().c_str());
}

QString repositoryImpl::getManagerPermissionTreeData(EventoException &err)
{
    return QString(QJsonDocument::fromJson(manager_permission_data).toJson(QJsonDocument::Compact).toStdString().c_str());
}
