#ifndef INFORMATIONSERVICE_H
#define INFORMATIONSERVICE_H

#include "promise.h"
#include "types.h"

class InformationService {
    std::array<EventTypeID, 3> dep_type_id = {-1, -1, -1};

private:
    InformationService() = default;

public:
    static InformationService& getInstance() {
        static InformationService singleton;
        return singleton;
    }

    void load_EditInfo(bool isEditMode);
    void load_DepartmentInfo();
    void load_SubscribedDepartmentInfo();

    EventoPromise<EventTypeID> getByDep(int dep);
};

#endif // INFORMATIONSERVICE_H
