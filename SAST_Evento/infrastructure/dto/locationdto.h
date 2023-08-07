#ifndef LOCATIONDTO_H
#define LOCATIONDTO_H

#include <QString>

struct LocationDTO
{
    int id;
    QString locationName;
    int parentId;
};

#endif // LOCATIONDTO_H
