#ifndef INFORMATIONSERVICE_H
#define INFORMATIONSERVICE_H

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

    void load_EditInfo();
    void load_DepartmentInfo();
    void load_SubscribedDepartmentInfo();

    EventTypeID getByDep(int dep);
};

#endif // INFORMATIONSERVICE_H
