#ifndef LOGINKEYDTO_H
#define LOGINKEYDTO_H

#include <QString>

struct LoginKeyDTO
{
    QString uid;
    QByteArray token;
};

#endif // LOGINKEYDTO_H
