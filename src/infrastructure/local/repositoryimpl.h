#ifndef REPOSITORYIMPL_H
#define REPOSITORYIMPL_H

#include <repository.h>

#include <QtConcurrent>
#include <QMutex>

#include "json_deserialise.hpp"

class department_data{
public:
    QString id;
    QString department_name;
};
register_object_member(department_data, "id", id);
register_object_member(department_data, "department_name", department_name);
declare_object(department_data,
               object_member(department_data, id),
               object_member(department_data, department_name)
               );

class event_data{
public:
    QString id;
    QString title;
    QString description;
    QString gmt_event_start;
    QString gmt_event_end;
    QString gmt_registration_start;
    QString gmt_registration_end;
    QString type_id;
    QString location_id;
    QString tag;
    QString state;
};
register_object_member(event_data, "id", id);
register_object_member(event_data, "title", title);
register_object_member(event_data, "description", description);
register_object_member(event_data, "gmt_event_start", gmt_event_start);
register_object_member(event_data, "gmt_event_end", gmt_event_end);
register_object_member(event_data, "gmt_registration_start", gmt_registration_start);
register_object_member(event_data, "gmt_registration_end", gmt_registration_end);
register_object_member(event_data, "type_id", type_id);
register_object_member(event_data, "location_id", location_id);
register_object_member(event_data, "tag", tag);
register_object_member(event_data, "state", state);
declare_object(event_data,
               object_member(event_data, id),
               object_member(event_data, title),
               object_member(event_data, description),
               object_member(event_data, gmt_event_start),
               object_member(event_data, gmt_event_end),
               object_member(event_data, gmt_registration_start),
               object_member(event_data, gmt_registration_end),
               object_member(event_data, type_id),
               object_member(event_data, location_id),
               object_member(event_data, tag),
               object_member(event_data, state)
               );

class event_department_data{
public:
    QString id;
    QString event_id;
    QString department_id;
};
register_object_member(event_department_data, "id", id);
register_object_member(event_department_data, "event_id", event_id);
register_object_member(event_department_data, "department_id", department_id);
declare_object(event_department_data,
               object_member(event_department_data, id),
               object_member(event_department_data, event_id),
               object_member(event_department_data, department_id)
               );

class feedback_data{
public:
    QString content;
    QString id;
    QString participate_id;
    QString score;
    QString user_id;
};
register_object_member(feedback_data, "content", content);
register_object_member(feedback_data, "id", id);
register_object_member(feedback_data, "participate_id", participate_id);
register_object_member(feedback_data, "score", score);
register_object_member(feedback_data, "user_id", user_id);
declare_object(feedback_data,
               object_member(feedback_data, content),
               object_member(feedback_data, id),
               object_member(feedback_data, participate_id),
               object_member(feedback_data, score),
               object_member(feedback_data, user_id)
               );

class location_data{
public:
    QString id;
    QString location_name;
    QString parent_id;
};
register_object_member(location_data, "id", id);
register_object_member(location_data, "location_name", location_name);
register_object_member(location_data, "parent_id", parent_id);
declare_object(location_data,
               object_member(location_data, id),
               object_member(location_data, location_name),
               object_member(location_data, parent_id)
               );

class manager_user_data{
public:
    QString event_id;
    QString manager_id;
};
register_object_member(manager_user_data, "event_id", event_id);
register_object_member(manager_user_data, "manager_id", manager_id);
declare_object(manager_user_data,
               object_member(manager_user_data, event_id),
               object_member(manager_user_data, manager_id)
               );

class participate_data{
public:
    QString event_id;
    QString id;
    QString is_participate;
    QString is_registration;
    QString is_subscribe;
    QString user_id;
};
register_object_member(participate_data, "event_id", event_id);
register_object_member(participate_data, "id", id);
register_object_member(participate_data, "is_participate", is_participate);
register_object_member(participate_data, "is_registration", is_registration);
register_object_member(participate_data, "is_subscribe", is_subscribe);
register_object_member(participate_data, "user_id", user_id);
declare_object(participate_data,
               object_member(participate_data, event_id),
               object_member(participate_data, id),
               object_member(participate_data, is_participate),
               object_member(participate_data, is_registration),
               object_member(participate_data, is_subscribe),
               object_member(participate_data, user_id)
               );

class permission_data{
public:
    QString id;
    QString all_method_name;
    QString user_id;
    QString event_id;
    QString gmt_update;
};
register_object_member(permission_data, "event_id", event_id);
register_object_member(permission_data, "id", id);
register_object_member(permission_data, "all_method_name", all_method_name);
register_object_member(permission_data, "gmt_update", gmt_update);
register_object_member(permission_data, "user_id", user_id);
declare_object(permission_data,
               object_member(permission_data, event_id),
               object_member(permission_data, id),
               object_member(permission_data, all_method_name),
               object_member(permission_data, gmt_update),
               object_member(permission_data, user_id)
               );

class slide_data{
public:
    QString id;
    QString title;
    QString link;
    QString url;
    QString event_id;
};
register_object_member(slide_data, "event_id", event_id);
register_object_member(slide_data, "id", id);
register_object_member(slide_data, "title", title);
register_object_member(slide_data, "link", link);
register_object_member(slide_data, "url", url);
declare_object(slide_data,
               object_member(slide_data, event_id),
               object_member(slide_data, id),
               object_member(slide_data, title),
               object_member(slide_data, link),
               object_member(slide_data, url)
               );

class type_data{
public:
    QString id;
    QString type_name;
    QString allow_conflict;
};
register_object_member(type_data, "type_name", type_name);
register_object_member(type_data, "id", id);
register_object_member(type_data, "allow_conflict", allow_conflict);
declare_object(type_data,
               object_member(type_data, type_name),
               object_member(type_data, id),
               object_member(type_data, allow_conflict)
               );

class user_data{
public:
    QString id;
    QString name;
    QString avatar;
    QString email;
    QString description;
    QString department;
    QString student_id;
    QString open_id;
};
register_object_member(user_data, "id", id);
register_object_member(user_data, "name", name);
register_object_member(user_data, "avatar", avatar);
register_object_member(user_data, "email", email);
register_object_member(user_data, "description", description);
register_object_member(user_data, "department", department);
register_object_member(user_data, "student_id", student_id);
register_object_member(user_data, "open_id", open_id);
declare_object(user_data,
               object_member(user_data, id),
               object_member(user_data, name),
               object_member(user_data, avatar),
               object_member(user_data, email),
               object_member(user_data, description),
               object_member(user_data, department),
               object_member(user_data, student_id),
               object_member(user_data, open_id)
               );

struct repositoryImpl : public Repository {
public:
    // user-fetch
    virtual QStringList getAdminPermission(EventoException& err) override;
    virtual QStringList getManagerPermission(const EventoID &eventoId, EventoException& err) override;
    virtual QStringList getPermittedEvent(EventoException& err) override;
    virtual DTO_Permission getEventPermission(EventoID event, EventoException& err) override;
    virtual DTO_User getUserInfo(const UserID& id, EventoException& err) override;
    virtual ParticipationStatus getUserParticipate(const EventoID &eventoId, EventoException& err) override;
    virtual DTO_Feedback getFeedbackInfo(const EventoID &eventoId, EventoException& err) override;

    // event-fetch
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getUndertakingList() override;
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getLatestList() override;
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getRegisteredList() override;
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getSubscribedList() override;
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getHistoryList() override;
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getEventListInPage(int page, int size) override;
    virtual QFuture<EventoResult<std::vector<DTO_Evento>>> getDepartmentEventList(int departmentId) override;
    virtual QFuture<EventoResult<DTO_Evento>> getEventById(EventoID event) override;
    virtual std::vector<DTO_Feedback> getFeedbackList(EventoID eventoId, EventoException& err) override;
    virtual std::vector<DTO_Slide> getSlideList(EventoException& err) override;
    virtual std::vector<DTO_Slide> getEventSlideList(EventoID id, EventoException& err) override;
    virtual std::vector<DTO_Slide> getHomeSlideList(const int& size, EventoException& err) override;
    virtual QString getTypeList(EventoException& err) override;
    virtual QString getLocationList(EventoException& err) override;
    virtual QString getDepartmentList(EventoException& err) override;
    virtual QString getQRCode(const int& eventId, EventoException& err) override;

    // event-upload
    virtual QFuture<EventoResult<bool>> checkIn(EventoID event, const QString& code) override;
    virtual QFuture<EventoResult<bool>> subscribe(EventoID event) override;
    virtual QFuture<EventoResult<bool>> hasFeedbacked(EventoID event) override;
    virtual bool feedbackEvent(const DTO_Feedback& code, EventoException& err) override;

    // admin-fetch
    virtual std::vector<DTO_Evento> getQualifiedEvent(EventoException& err, int type = -1, const std::vector<int> &dep = std::vector<int>(), const QDate &day = QDate()) override;
    virtual QStringList getActionStateList(EventoException& err) override;
    virtual QStringList getActionList(EventoException& err) override;
    virtual std::vector<DTO_UserBrief> getEventManagerList(const EventoID &eventoId, EventoException& err) override;
    virtual std::vector<DTO_UserBrief> getAdminUserList(EventoException& err) override;
    virtual QString getAdminPermissionTreeData(EventoException& err) override;
    virtual QString getManagerPermissionTreeData(EventoException& err) override;

public:
    static repositoryImpl * getInstance(){
        static repositoryImpl instance;
        return &instance;
    }
/*
    void test() {
        EventoException error(EventoExceptionCode::UnexpectedError, "null");
        qDebug().noquote() << getDepartmentEventList(1, error).size();
        qDebug()<<error.message();
    };
*/

    ~repositoryImpl(){
        declare_serialiser("department_data_list", department_data_list, department_data_list_holder);
        JsonDeserialise::JsonSerialiser department_data_list_deserialiser(department_data_list_holder);
        department_data_list_deserialiser.serialise_to_file("localdata/department.json");

        declare_serialiser("event_data_list", event_data_list, event_data_list_holder);
        JsonDeserialise::JsonSerialiser event_data_list_deserialiser(event_data_list_holder);
        event_data_list_deserialiser.serialise_to_file("localdata/event.json");

        declare_serialiser("event_department_data_list", event_department_data_list, event_department_data_list_holder);
        JsonDeserialise::JsonSerialiser event_department_data_list_deserialiser(event_department_data_list_holder);
        event_department_data_list_deserialiser.serialise_to_file("localdata/event_department.json");

        declare_serialiser("feedback_data_list", feedback_data_list, feedback_data_list_holder);
        JsonDeserialise::JsonSerialiser feedback_data_list_deserialiser(feedback_data_list_holder);
        feedback_data_list_deserialiser.serialise_to_file("localdata/feedback.json");

        declare_serialiser("location_data_list", location_data_list, location_data_list_holder);
        JsonDeserialise::JsonSerialiser location_data_list_deserialiser(location_data_list_holder);
        location_data_list_deserialiser.serialise_to_file("localdata/location.json");

        declare_serialiser("manager_user_data_list", manager_user_data_list, manager_user_data_list_holder);
        JsonDeserialise::JsonSerialiser manager_user_data_list_deserialiser(manager_user_data_list_holder);
        manager_user_data_list_deserialiser.serialise_to_file("localdata/manager_user.json");

        declare_serialiser("participate_data_list", participate_data_list, participate_data_list_holder);
        JsonDeserialise::JsonSerialiser participate_data_list_deserialiser(participate_data_list_holder);
        participate_data_list_deserialiser.serialise_to_file("localdata/participate.json");

        declare_serialiser("permission_data_list", permission_data_list, permission_data_list_holder);
        JsonDeserialise::JsonSerialiser permission_data_list_deserialiser(permission_data_list_holder);
        permission_data_list_deserialiser.serialise_to_file("localdata/permission.json");

        declare_serialiser("slide_data_list", slide_data_list, slide_data_list_holder);
        JsonDeserialise::JsonSerialiser slide_data_list_deserialiser(slide_data_list_holder);
        slide_data_list_deserialiser.serialise_to_file("localdata/slide.json");

        declare_serialiser("type_data_list", type_data_list, type_data_list_holder);
        JsonDeserialise::JsonSerialiser type_data_list_deserialiser(type_data_list_holder);
        type_data_list_deserialiser.serialise_to_file("localdata/type.json");

        declare_serialiser("user_data_list", user_data_list, user_data_list_holder);
        JsonDeserialise::JsonSerialiser user_data_list_deserialiser(user_data_list_holder);
        user_data_list_deserialiser.serialise_to_file("localdata/user.json");

        writeFile("localdata/admin_permission.json", admin_permission_data);
        writeFile("localdata/admin_user.json", admin_user_data);
        writeFile("localdata/manager_permission.json", manager_permission_data);
    }
private:
    std::vector<department_data> department_data_list;
    std::vector<event_data> event_data_list;
    std::vector<event_department_data> event_department_data_list;
    std::vector<feedback_data> feedback_data_list;
    std::vector<location_data> location_data_list;
    std::vector<manager_user_data> manager_user_data_list;
    std::vector<participate_data> participate_data_list;
    std::vector<permission_data> permission_data_list;
    std::vector<slide_data> slide_data_list;
    std::vector<type_data> type_data_list;
    std::vector<user_data> user_data_list;

    QByteArray admin_permission_data;
    QByteArray admin_user_data;
    QByteArray manager_permission_data;

    repositoryImpl(){
        declare_deserialiser("department_data_list", department_data_list, department_data_list_holder);
        JsonDeserialise::JsonDeserialiser department_data_list_deserialiser(department_data_list_holder);
        department_data_list_deserialiser.deserialiseFile("localdata/department.json");

        declare_deserialiser("event_data_list", event_data_list, event_data_list_holder);
        JsonDeserialise::JsonDeserialiser event_data_list_deserialiser(event_data_list_holder);
        event_data_list_deserialiser.deserialiseFile("localdata/event.json");

        declare_deserialiser("event_department_data_list", event_department_data_list, event_department_data_list_holder);
        JsonDeserialise::JsonDeserialiser event_department_data_list_deserialiser(event_department_data_list_holder);
        event_department_data_list_deserialiser.deserialiseFile("localdata/event_department.json");

        declare_deserialiser("feedback_data_list", feedback_data_list, feedback_data_list_holder);
        JsonDeserialise::JsonDeserialiser feedback_data_list_deserialiser(feedback_data_list_holder);
        feedback_data_list_deserialiser.deserialiseFile("localdata/feedback.json");

        declare_deserialiser("location_data_list", location_data_list, location_data_list_holder);
        JsonDeserialise::JsonDeserialiser location_data_list_deserialiser(location_data_list_holder);
        location_data_list_deserialiser.deserialiseFile("localdata/location.json");

        declare_deserialiser("manager_user_data_list", manager_user_data_list, manager_user_data_list_holder);
        JsonDeserialise::JsonDeserialiser manager_user_data_list_deserialiser(manager_user_data_list_holder);
        manager_user_data_list_deserialiser.deserialiseFile("localdata/manager_user.json");

        declare_deserialiser("participate_data_list", participate_data_list, participate_data_list_holder);
        JsonDeserialise::JsonDeserialiser participate_data_list_deserialiser(participate_data_list_holder);
        participate_data_list_deserialiser.deserialiseFile("localdata/participate.json");

        declare_deserialiser("permission_data_list", permission_data_list, permission_data_list_holder);
        JsonDeserialise::JsonDeserialiser permission_data_list_deserialiser(permission_data_list_holder);
        permission_data_list_deserialiser.deserialiseFile("localdata/permission.json");

        declare_deserialiser("slide_data_list", slide_data_list, slide_data_list_holder);
        JsonDeserialise::JsonDeserialiser slide_data_list_deserialiser(slide_data_list_holder);
        slide_data_list_deserialiser.deserialiseFile("localdata/slide.json");

        declare_deserialiser("type_data_list", type_data_list, type_data_list_holder);
        JsonDeserialise::JsonDeserialiser type_data_list_deserialiser(type_data_list_holder);
        type_data_list_deserialiser.deserialiseFile("localdata/type.json");

        declare_deserialiser("user_data_list", user_data_list, user_data_list_holder);
        JsonDeserialise::JsonDeserialiser user_data_list_deserialiser(user_data_list_holder);
        user_data_list_deserialiser.deserialiseFile("localdata/user.json");

        admin_permission_data = readFile("localdata/admin_permission.json");
        admin_user_data = readFile("localdata/admin_user.json");
        manager_permission_data = readFile("localdata/manager_permission.json");
    };

    QMutex mutex;
    struct Participation {
        int id;
        ParticipationStatus participationStatus;
        EventoID event_id;
        UserID user_id;
    };

    QStringList adminPerission{
        "addAdmin",
        "deletePicture",
        "addEvent",
        "deleteAdmin",
        "updateAction",
        "deleteHomeSlide",
        "getStates",
        "deleteType",
        "getAdmins",
        "addHomeSlide",
        "getFeedbackEvents",
        "updateLocation",
        "getLocations",
        "addLocation",
        "getFeedbacks",
        "addPicture",
        "patchHomeSlide",
        "putAdmin",
        "deleteLocation",
        "addType",
        "getActionList",
        "eventQrcodeGet",
        "getTypes",
        "updateType"
    };

    QStringList managerPerission{
        "addEventSlide",
        "deleteManager",
        "deleteEventSlide",
        "deleteEvent",
        "patchEvent",
        "addManager",
        "patchEventSlide",
        "putManager",
        "putEvent"
    };

    QByteArray readFile(QString path) {
        QFile file(path);

        mutex.tryLock(1);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Can't open the file(" + path + ")!";
            qDebug() << file.errorString();
            return QByteArray();
        }
        QByteArray file_str = file.readAll();
        file.close();

        mutex.unlock();

        return file_str;
    }

    bool writeFile(QString path, const QByteArray &data){
        QFile file(path);

        mutex.tryLock(1);

        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
            qDebug() << "Can't open the file(" + path + ")!";
            qDebug() << file.errorString();
            return false;
        }

        file.seek(0);
        file.write(data);
        file.flush();
        file.close();

        mutex.unlock();
        return true;
    }

    std::pair<QString, QString> nullpair =
        std::pair<QString, QString>("null", "null");


    QString readLocations(const QString& locationId) {
        QString res;
        QStringList locationTree;
        std::pair<QString, QString> location_temp;
        do {
            location_temp = locationHelper(locationId);
            locationTree.append(location_temp.first);
        } while (location_temp.second.compare("0"));

        for (int i = locationTree.count() - 1; i >= 0; i--) {
            if (i != 0) {
                res.append(locationTree.at(i) + " ");
            } else {
                res.append(locationTree.at(i));
            }
        }
        return res;
    }

    std::pair<QString, QString> locationHelper(QString id) {
        for (int i = 0; i < location_data_list.size(); i++) {
            if (!location_data_list.at(i).id.compare(id)) {
                return std::pair<QString, QString>(location_data_list.at(i).location_name,
                                                   location_data_list.at(i).parent_id);
            }
        }
        return nullpair;
    }

    Department readDepartment(const QString &id){
        for(int i = 0; i<department_data_list.size(); i++){
            if(!department_data_list.at(i).id.compare(id)){
                return Department{
                    id.toInt(),
                    department_data_list.at(i).department_name
                };
            }
        }
        return Department();
    }

    EventType readType(const QString &id){
        for(int i = 0; i<type_data_list.size(); i++){
            if(!type_data_list.at(i).id.compare(id)){
                return EventType{
                    id.toInt(),
                    type_data_list.at(i).type_name,
                    type_data_list.at(i).allow_conflict.compare("false")?true:false
                };
            }
        }
        return EventType();
    }

    DTO_Evento readEvento(const EventoID &eventoId) {
        for (int i = 0; i < event_data_list.size(); i++) {
            if (!event_data_list.at(i).id.compare(QString::number(eventoId))) {
                event_data unit = event_data_list.at(i);
                std::vector<Department> departments;
                QStringList departmentIds;
                for(int i = 0; i<event_department_data_list.size(); i++){
                    if(eventoId == event_department_data_list.at(i).event_id.toInt()){
                        departmentIds = event_department_data_list.at(i).department_id.split(" ");
                    }
                }
                for (int i = 0; i < departmentIds.count(); i++) {
                    departments.push_back(readDepartment(departmentIds.at(i)));
                }
                return DTO_Evento{
                    eventoId,
                        unit.title,
                        unit.description,
                        QDateTime::fromString(unit.gmt_event_start, "yyyy-MM-dd hh:mm:ss"),
                        QDateTime::fromString(unit.gmt_event_end, "yyyy-MM-dd hh:mm:ss"),
                        QDateTime::fromString(unit.gmt_registration_start, "yyyy-MM-dd hh:mm:ss"),
                        QDateTime::fromString(unit.gmt_registration_end, "yyyy-MM-dd hh:mm:ss"),
                        readType(unit.type_id),
                        readLocations(unit.location_id),
                        unit.tag,
                        static_cast<EventState>(unit.state.toInt()),
                    departments};
            }
        }
        return DTO_Evento();
    }

    QFuture<EventoResult<std::vector<DTO_Evento>>> readEventoByState(const QString &state) {
        return QtConcurrent::run([=](){
            std::vector<DTO_Evento> res;

            for (int i = 0; i < event_data_list.size(); i++) {
                if (event_data_list.at(i).state.compare(state))
                    break;
                event_data unit = event_data_list.at(i);
                std::vector<Department> departments;
                QStringList departmentIds;
                for(int i = 0; i<event_department_data_list.size(); i++){
                    if(!unit.id.compare(event_department_data_list.at(i).event_id)){
                        departmentIds = event_department_data_list.at(i).department_id.split(" ");
                    }
                }
                for (int i = 0; i < departmentIds.count(); i++) {
                    departments.push_back(readDepartment(departmentIds.at(i)));
                }
                res.push_back(DTO_Evento{
                                         unit.id.toInt(),
                                         unit.title,
                                         unit.description,
                                         QDateTime::fromString(unit.gmt_event_start, "yyyy-MM-dd hh:mm:ss"),
                                         QDateTime::fromString(unit.gmt_event_end, "yyyy-MM-dd hh:mm:ss"),
                                         QDateTime::fromString(unit.gmt_registration_start, "yyyy-MM-dd hh:mm:ss"),
                                         QDateTime::fromString(unit.gmt_registration_end, "yyyy-MM-dd hh:mm:ss"),
                                         readType(unit.type_id),
                                         readLocations(unit.location_id),
                                         unit.tag,
                                         static_cast<EventState>(unit.state.toInt()),
                                         departments});
            }

            return EventoResult(std::move(res));
        });
    }

    std::vector<DTO_Evento> readEventoByType(const QString &type) {
        std::vector<DTO_Evento> res;

        for (int i = 0; i < event_data_list.size(); i++) {
            if (!event_data_list.at(i).type_id.compare(type)) {
                event_data unit = event_data_list.at(i);
                std::vector<Department> departments;
                QStringList departmentIds;
                for(int i = 0; i<event_department_data_list.size(); i++){
                    if(!unit.id.compare(event_department_data_list.at(i).event_id)){
                        departmentIds = event_department_data_list.at(i).department_id.split(" ");
                    }
                }
                for (int i = 0; i < departmentIds.count(); i++) {
                    departments.push_back(readDepartment(departmentIds.at(i)));
                }
                res.push_back(DTO_Evento{
                                         unit.id.toInt(),
                                         unit.title,
                                         unit.description,
                                         QDateTime::fromString(unit.gmt_event_start, "yyyy-MM-dd hh:mm:ss"),
                                         QDateTime::fromString(unit.gmt_event_end, "yyyy-MM-dd hh:mm:ss"),
                                         QDateTime::fromString(unit.gmt_registration_start, "yyyy-MM-dd hh:mm:ss"),
                                         QDateTime::fromString(unit.gmt_registration_end, "yyyy-MM-dd hh:mm:ss"),
                                         readType(unit.type_id),
                                         readLocations(unit.location_id),
                                         unit.tag,
                                         static_cast<EventState>(unit.state.toInt()),
                                         departments});
            }
        }
        return res;
    }

    std::vector<DTO_Evento> readAllEvento(){
        std::vector<DTO_Evento> res;

        for (int i = 0; i < event_data_list.size(); i++) {
            event_data unit = event_data_list.at(i);
            std::vector<Department> departments;
            QStringList departmentIds;
            for(int i = 0; i<event_department_data_list.size(); i++){
                if(!unit.id.compare(event_department_data_list.at(i).event_id)){
                    departmentIds = event_department_data_list.at(i).department_id.split(" ");
                }
            }
            for (int i = 0; i < departmentIds.count(); i++) {
                departments.push_back(readDepartment(departmentIds.at(i)));
            }
            res.push_back(DTO_Evento{
                                     unit.id.toInt(),
                                     unit.title,
                                     unit.description,
                                     QDateTime::fromString(unit.gmt_event_start, "yyyy-MM-dd hh:mm:ss"),
                                     QDateTime::fromString(unit.gmt_event_end, "yyyy-MM-dd hh:mm:ss"),
                                     QDateTime::fromString(unit.gmt_registration_start, "yyyy-MM-dd hh:mm:ss"),
                                     QDateTime::fromString(unit.gmt_registration_end, "yyyy-MM-dd hh:mm:ss"),
                                     readType(unit.type_id),
                                     readLocations(unit.location_id),
                                     unit.tag,
                                     static_cast<EventState>(unit.state.toInt()),
                                     departments});
        }
        return res;
    }

    std::vector<Participation> readParticipation(const std::pair<QString, QString>& key) {
        std::vector<Participation> res;

        for (int i = 0; i < participate_data_list.size(); i++) {
            participate_data unit = participate_data_list.at(i);
            auto fun = [&](){
                res.push_back(
                    Participation{unit.id.toInt(),
                                  ParticipationStatus{
                                                      unit.is_registration.compare("false")?true:false,
                                                      unit.is_participate.compare("false")?true:false,
                                                      unit.is_subscribe.compare("false")?true:false},
                                  unit.event_id.toInt(),
                                  unit.user_id});
                };
            if (key.first.compare("null") && key.second.compare("null")) {

                if(!key.first.compare("is_registration") && !unit.is_registration.compare(key.second)){
                    fun();
                }
                else if(!key.first.compare("is_participate") && !unit.is_participate.compare(key.second)){
                    fun();
                }
                else if(!key.first.compare("is_subscribe") && !unit.is_subscribe.compare(key.second)){
                    fun();
                }
                else if(!key.first.compare("id") && !unit.id.compare(key.second)){
                    fun();
                }
                else if(!key.first.compare("event_id") && !unit.id.compare(key.second)){
                    fun();
                }
            }
            else{
                fun();
            }
        }
        return res;
    }

    bool writeParticipation(const QString& key, const QString& value,
                            EventoID eventId) {
        for (int i = 0; i < participate_data_list.size(); i++) {
            if (!participate_data_list.at(i).event_id.compare(QString::number(eventId)) &&
                !participate_data_list.at(i).user_id.compare("B22041234")) {
                if(!key.compare("is_registration")){
                    participate_data_list.at(i).is_registration = value;
                    return true;
                }
                else if(!key.compare("is_participate")){
                    participate_data_list.at(i).is_participate = value;
                    return true;
                }
                else if(!key.compare("is_subscribe")){
                    participate_data_list.at(i).is_subscribe = value;
                    return true;
                }
            }
        }
        return false;
    }

    bool eventDepartmentMatch(int eventId, int departmentId) {
        for (int i = 0; i < event_department_data_list.size(); i++) {
            if (!event_department_data_list.at(i).event_id.compare(QString::number(eventId)) &&
                !event_department_data_list.at(i).department_id.compare(QString::number(departmentId))) {
                return true;
            }
        }
        return false;
    }

    std::vector<DTO_Permission> readPermission(UserID id) {
        std::vector<DTO_Permission> res;
        for (int i = 0; i < permission_data_list.size(); i++) {
            if (!permission_data_list.at(i).user_id.compare("B22041234")) {
                res.push_back(DTO_Permission {
                                             permission_data_list.at(i).all_method_name.split(" "),
                                             permission_data_list.at(i).event_id.toInt(),
                });
            }
        }
        return res;
    }

    DTO_UserBrief readUserBrief(const QString &userId){
        for (int i = 0; i < user_data_list.size(); i++) {
            if(!user_data_list.at(i).id.compare(userId)){
                return DTO_UserBrief{
                    userId,
                    user_data_list.at(i).student_id,
                    user_data_list.at(i).open_id
                };
            }
        }
        return DTO_UserBrief();
    }

    QJsonObject formatToTree(const std::vector<location_data> &arr, const QString &parentId, const QString &name){
        QJsonObject item;
        QJsonArray children;
        for(int i = 0; i<arr.size(); i++){
            if(!arr.at(i).parent_id.compare(parentId)){
                children.push_back(formatToTree(arr,
                                                arr.at(i).id,
                                                arr.at(i).location_name));
            }
        }
        item.insert("id", parentId.toInt());
        item.insert("name", name);
        if(!children.isEmpty()){
            item.insert("children", children);
        }
        return item;
    }
};
#endif  // REPOSITORYIMPL_H
