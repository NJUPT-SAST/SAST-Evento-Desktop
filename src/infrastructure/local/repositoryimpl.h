#ifndef REPOSITORYIMPL_H
#define REPOSITORYIMPL_H

#include <repository.h>

#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>

class repositoryImpl : public Repository
{
public:
    //user-fetch
    QStringList get_admin_permission(EventoException& err) override; // Test completed
    QStringList get_permitted_event(EventoException& err) override; // Test completed
    DTO_Permission get_event_permission(EventoID event, EventoException& err) override; // Test completed
    DTO_User get_user_info(const UserID &id, EventoException& err) override; // Test completed
    std::vector<DTO_Slide> get_home_slide_list(const int &size, EventoException& err) override; // Test completed

    //event-fetch
    std::vector<DTO_Evento> get_undertaking_list(EventoException& err) override; // Test completed
    std::vector<DTO_Evento> get_latest_list(EventoException& err) override; // Test completed
    std::vector<DTO_Evento> get_subscribed_list(EventoException& err) override; // Test completed
    std::vector<DTO_Evento> get_history_list(EventoException& err) override; // Test completed
    std::vector<DTO_Evento> get_event_list(const int &page, const int &size, EventoException& err) override; // Test completed
    DTO_Evento get_event(EventoID event, EventoException& err) override; // Test completed
    std::vector<DTO_Feedback> get_feedback_list(EventoException& err) override; // Test completed
    std::vector<DTO_Slide> get_slide_list(EventoException& err) override; // Test completed
    std::vector<DTO_Slide> get_event_slide_list(EventoID id, EventoException& err) override; // Test completed
    std::vector<EventType> get_type_list(const int &page, const int &size, EventoException& err) override;
    std::vector<Location> get_location_list(EventoException& err) override; // Test completed
    QString get_qrcode(const int &eventId, EventoException& err) override; // Test completed

    //event-upload
    bool event_checkin(EventoID event, const QString& code, EventoException& err) override; // Test completed
    bool event_feedback(const DTO_Feedback& code, EventoException& err) override; // Test completed
    bool event_subscribe(EventoID event, EventoException& err) override; // Test completed

    //admin-fetch
    std::vector<DTO_Evento> get_qualified_event(int type, const std::vector<int> &dep, const QDate &day, EventoException& err) override; // Test completed
    QStringList get_action_state_list(EventoException& err) override;
    QStringList get_action_list(EventoException& err) override;
public:
    void test(){
        EventoException error(EventoExceptionCode::UnexpectedError, "null");
        qDebug()<<get_qrcode(1, error);
    };
    repositoryImpl();

private:
    struct Participation{
        int id;
        ParticipationStatus participationStatus;
        EventoID event_id;
        UserID user_id;
    };

    QByteArray readString(QString path){
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<< "Can't open the file(" + path +")!";
            return QByteArray();
        }
        QByteArray file_str = file.readAll();
        file.close();
        return file_str;
    }

    std::pair<QString, QString> nullpair = std::pair<QString, QString>("null", "null");

    QString readFile(const QString &file_s, const QString &tag, const std::pair<QString, QString> &key){
        QByteArray file_str = readString(file_s);
        if(file_s.isEmpty()){
            return QString();
        }

        QString res;
        QStringList res_temp;

        QJsonParseError jsonError;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(file_str, &jsonError));
        if(jsonError.error == QJsonParseError::NoError && jsonDoc.isArray()){
            QJsonArray jsonArr = jsonDoc.array();
            for(int i = 0; i<jsonArr.count(); i++){
                QJsonObject unit = jsonArr.at(i).toObject();
                if((!key.first.compare("null") && !key.second.compare("null")) ||
                    (unit.contains(key.first) && !unit.value(key.first).toString().compare(key.second))){
                    if(unit.contains(tag)){
                        res_temp.append(unit.value(tag).toString());
                    }
                }
            }
        }

        for(int i = 0; i<res_temp.count(); i++){
            if(i != res_temp.count()-1){
                res.append(res_temp.at(i) + " ");
            }
            else{
                res.append(res_temp.at(i));
            }
        }
        return res;
    }

    QString readLocations(const QString &locationId){
        QByteArray file_str = readString("localdata/location.json");
        if(file_str.isEmpty()){
            return QString();
        }

        QString res;
        QJsonParseError jsonError;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(file_str, &jsonError));
        if(jsonError.error == QJsonParseError::NoError && jsonDoc.isArray()){
            QJsonArray jsonArr = jsonDoc.array();
            QStringList locationTree;
            std::pair<QString, QString> location_temp;
            do{
                location_temp = locationHelper(jsonArr, locationId);
                locationTree.append(location_temp.first);
            }while(location_temp.second.compare("0"));

            for(int i = locationTree.count()-1; i>=0; i--){
                if(i != 0){
                    res.append(locationTree.at(i) + " ");
                }
                else{
                    res.append(locationTree.at(i));
                }
            }
        }
        return res;
    }

    std::pair<QString, QString> locationHelper(const QJsonArray &locationList, QString id){
        for(int i = 0; i < locationList.count(); i++){
            if(!locationList.at(i).toObject().value("id").toString().compare(id)){
                return std::pair<QString, QString>(locationList.at(i).toObject().value("location_name").toString(),
                                                   locationList.at(i).toObject().value("parent_id").toString());
            }
        }
        return nullpair;
    }

    std::vector<DTO_Evento> readEvento(const std::pair<QString, QString> &key){
        std::vector<DTO_Evento> res;
        QByteArray file_str = readString("localdata/event.json");
        if(file_str.isEmpty()){
            return std::vector<DTO_Evento>();
        }

        QJsonParseError jsonError;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(file_str, &jsonError));
        if(jsonError.error == QJsonParseError::NoError && jsonDoc.isArray()){
            QJsonArray jsonArr = jsonDoc.array();
            for(int i = 0; i<jsonArr.count(); i++){
                QJsonObject unit = jsonArr.at(i).toObject();
                if((!key.first.compare("null") && !key.second.compare("null")) ||
                    (unit.contains(key.first) && !unit.value(key.first).toString().compare(key.second))){

                    std::vector<Department> departments;
                    QString eventoId = unit.contains("id")?unit.value("id").toString():nullptr;
                    QStringList departmentIds = readFile("localdata/event_department.json",
                                                         "department_id",
                                                         std::pair<QString,QString>("event_id", eventoId)).split(" ");
                    for(int i = 0; i<departmentIds.count(); i++){
                        departments.push_back(Department{departmentIds[i].toInt(),
                                                         readFile("localdata/department.json",
                                                                  "department_name",
                                                                  std::pair<QString, QString>("id", departmentIds.at(i)))});
                    }
                    res.push_back(DTO_Evento{
                        eventoId.toInt(),
                        unit.contains("title")?unit.value("title").toString():nullptr,
                        unit.contains("description")?unit.value("id").toString():nullptr,
                        unit.contains("gmt_event_start")?QDateTime::fromString(unit.value("gmt_event_start").toString(), "yyyy-MM-dd hh:mm:ss"):QDateTime(),
                        unit.contains("gmt_event_end")?QDateTime::fromString(unit.value("gmt_event_end").toString(), "yyyy-MM-dd hh:mm:ss"):QDateTime(),
                        unit.contains("gmt_registration_start")?QDateTime::fromString(unit.value("gmt_registration_start").toString(), "yyyy-MM-dd hh:mm:ss"):QDateTime(),
                        unit.contains("gmt_registration_end")?QDateTime::fromString(unit.value("gmt_registration_end").toString(), "yyyy-MM-dd hh:mm:ss"):QDateTime(),
                        EventType{
                            readFile("localdata/type.json", "id", std::pair<QString,QString>("id", unit.value("type_id").toString())).toInt(),
                            readFile("localdata/type.json", "type_name", std::pair<QString,QString>("id", unit.value("type_id").toString())),
                            readFile("localdata/type.json", "allow_conflict", std::pair<QString,QString>("id", unit.value("type_id").toString())).compare("false")?true:false
                        },
                        readLocations(unit.value("location_id").toString()),
                        unit.contains("tag")?unit.value("tag").toString():QString(),
                        static_cast<EventState>(unit.value("state").toString().toInt()),
                        departments
                    });
                }
            }
        }
        return res;
    }

    std::vector<Participation> readParticipation(const std::pair<QString, QString> &key){
        std::vector<Participation> res;
        QByteArray file_str = readString("localdata/participate.json");

        QJsonParseError jsonError;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(file_str, &jsonError));
        if(jsonError.error == QJsonParseError::NoError && jsonDoc.isArray()){
            QJsonArray jsonArr = jsonDoc.array();
            for(int i = 0; i<jsonArr.count(); i++){
                QJsonObject unit = jsonArr.at(i).toObject();
                if((!key.first.compare("null") && !key.second.compare("null")) ||
                    (unit.contains(key.first) && !unit.value(key.first).toString().compare(key.second))){
                    res.push_back(Participation{
                        unit.value("id").toString().toInt(),
                        ParticipationStatus{
                            unit.value("is_registration").toString().compare("false")?true:false,
                            unit.value("is_participate").toString().compare("false")?true:false,
                            unit.value("is_subscribe").toString().compare("false")?true:false
                        },
                        unit.value("event_id").toString().toInt(),
                        unit.value("user_id").toString()
                    });
                }
            }
        }
        return res;
    }

    bool writeParticipation(const QString &key, const QString &value, EventoID eventId){
        QByteArray file_str = readString("localdata/participate.json");
        if(file_str.isEmpty()){
            return false;
        }

        QJsonParseError jsonError;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(file_str, &jsonError));
        QJsonArray jsonArr;
        if(jsonError.error == QJsonParseError::NoError && jsonDoc.isArray()){
            jsonArr = jsonDoc.array();
            for(int i = 0; i < jsonArr.count(); i++){
                if(!jsonArr.at(i).toObject().value("event_id").toString().compare(QString::number(eventId)) &&
                    !jsonArr.at(i).toObject().value("user_id").toString().compare("B22041234")){
                    QJsonObject unit = jsonArr.at(i).toObject();
                    unit[key] = value;
                    jsonArr.replace(i, unit);
                }
            }
        }

        QFile wFile("localdata/participate.json");
        if(wFile.exists() && wFile.open(QIODevice::WriteOnly|QIODevice::Text)){
            jsonDoc.setArray(jsonArr);
            wFile.seek(0);
            wFile.write(jsonDoc.toJson());
            wFile.flush();
            wFile.close();
        }
        else{
            return false;
        }
        return true;
    }

    bool eventDepartmentMatch(int eventId, int departmentId){
        QByteArray eventDepartment_str = readString("localdata/event_department.json");
        if(eventDepartment_str.isEmpty()){
            return false;
        }

        QJsonParseError jsonError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(eventDepartment_str, &jsonError);
        if(jsonError.error == QJsonParseError::NoError && jsonDoc.isArray()){
            QJsonArray jsonArr = jsonDoc.array();
            for(int i = 0; i<jsonArr.count(); i++){
                if(!jsonArr.at(i).toObject().value("event_id").toString().compare(QString::number(eventId)) &&
                    !jsonArr.at(i).toObject().value("department_id").toString().compare(QString::number(departmentId))){
                    return true;
                }
            }
        }
        return false;
    }

    std::vector<DTO_Permission> readPermission(UserID id){
        std::vector<DTO_Permission> res;
        QByteArray file_str = readString("localdata/permission.json");
        if(file_str.isEmpty()){
            return std::vector<DTO_Permission>();
        }

        QJsonParseError jsonError;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(file_str, &jsonError));
        QJsonArray jsonArr;
        if(jsonError.error == QJsonParseError::NoError && jsonDoc.isArray()){
            jsonArr = jsonDoc.array();
            for(int i = 0; i < jsonArr.count(); i++){
                if(!jsonArr.at(i).toObject().value("user_id").toString().compare("B22041234")){
                    res.push_back(DTO_Permission{
                        jsonArr.at(i).toObject().value("user_id").toString().toInt(),
                        jsonArr.at(i).toObject().value("user_id").toString().split(" "),
                        jsonArr.at(i).toObject().value("user_id").toString(),
                        jsonArr.at(i).toObject().value("user_id").toString().toInt(),
                        QDateTime::fromString(jsonArr.at(i).toObject().value("user_id").toString(), "yyyy-MM-dd hh:mm:ss")
                    });
                }
            }
        }
        return res;
    }

    Department readDepartment(const QString &id){
        QByteArray file_str = readString("localdata/department.json");
        if(file_str.isEmpty()){
            return Department();
        }

        QJsonParseError jsonError;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(file_str, &jsonError));
        QJsonArray jsonArr;
        if(jsonError.error == QJsonParseError::NoError && jsonDoc.isArray()){
            jsonArr = jsonDoc.array();
            for(int i = 0; i < jsonArr.count(); i++){
                if(!jsonArr.at(i).toObject().value("id").toString().compare(id)){
                    return Department{
                        jsonArr.at(i).toObject().value("id").toString().toInt(),
                        jsonArr.at(i).toObject().value("department_name").toString()
                    };
                }
            }
        }
        return Department();
    }
};
#endif // REPOSITORYIMPL_H
