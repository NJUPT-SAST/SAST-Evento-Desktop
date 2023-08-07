#ifndef BASESERVICE_H
#define BASESERVICE_H

#include <QObject>

class BaseService : public QObject
{
    Q_OBJECT
public:
    explicit BaseService(QObject* parent = nullptr);
};

#endif  // BASESERVICE_H
