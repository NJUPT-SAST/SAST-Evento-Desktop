#ifndef INFORMATIONSERVICE_H
#define INFORMATIONSERVICE_H

#include <QString>
#include <shared_mutex>

class InformationService
{
    std::shared_mutex mutex;

    QString departmentJson;
    QString typeJson;
    QString locationJson;
    QString subscribedDepartmentJson;

private:
    InformationService() = default;
public:
    static InformationService& getInstance() {
        static InformationService singleton;
        return singleton;
    }

    void load_EditInfo();
    void load_DepartmentInfo();
    void load_SubscribedDepartmentInfo();
};

#endif // INFORMATIONSERVICE_H
