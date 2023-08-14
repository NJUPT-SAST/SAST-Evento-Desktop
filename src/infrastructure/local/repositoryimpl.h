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

    //event-fetch
    std::vector<DTO_Evento> get_undertaking_list(EventoException& err) override; // Test completed
    std::vector<DTO_Evento> get_latest_list(EventoException& err) override; // Test completed
    std::vector<DTO_Evento> get_subscribed_list(EventoException& err) override; // Test completed
    DTO_Evento get_event(EventoID event, EventoException& err) override; // Test completed
    std::vector<DTO_Feedback> get_feedback_list(EventoException& err) override; // Test completed
    std::vector<DTO_Slide> get_slide_list(EventoException& err) override; // Test completed

    //event-upload
    bool event_checkin(EventoID event, const QString& code, EventoException& err) override; // Test completed
    bool event_feedback(const DTO_Feedback& code, EventoException& err) override; // Test completed
    bool event_subscribe(EventoID event, EventoException& err) override; // Test completed

    //admin-fetch
    std::vector<DTO_Evento> get_qualified_event(int type, std::vector<int> dep, QDate day, EventoException& err) override; // Test completed
public:
    void test(){

    };
    repositoryImpl();

private:
    struct Participation{
        int id;
        ParticipationStatus participationStatus;
        EventoID event_id;
        UserID user_id;
    };

    std::pair<QString, QString> nullpair = std::pair<QString, QString>("null", "null");

    QString readFile(QString file_s, QString tag, std::pair<QString, QString> key){
        QFile file(file_s);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<< "Can't open the file(" + file_s +")!";
            return QString();
        }
        QByteArray file_str = file.readAll();
        file.close();

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

    std::vector<DTO_Evento> readEvento(std::pair<QString, QString> key){
        QFile file("localdata/event.json");
        std::vector<DTO_Evento> res;
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug()<< "Can't open the file(localdata/event.json)!";
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
                        unit.contains("location_id")?unit.value("location_id").toString().split(" "):QStringList(),
                        unit.contains("tag")?unit.value("tag").toString().split(" "):QStringList(),
                        static_cast<EventState>(unit.value("state").toString().toInt()),
                        departments
                    });
                }
            }
        }
        return res;
    }

    std::vector<Participation> readParticipation(std::pair<QString, QString> key){
        QFile file("localdata/participate.json");
        std::vector<Participation> res;
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

    bool writeParticipation(QString key, QString value, EventoID eventId){
        QFile file("localdata/participate.json");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug()<< "Can't open the file!";
            return false;
        }
        QByteArray file_str = file.readAll();
        file.close();

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
        QFile file("localdata/event_department.json");
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug()<< "Can't open the file(event_department.json)!";
            return false;
        }
        QByteArray eventDepartment_str = file.readAll();
        file.close();

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
};
#endif // REPOSITORYIMPL_H
