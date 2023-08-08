#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include <QObject>
#include "domain/exception/biz_exception.h"

class BaseController : public QObject
{
    Q_OBJECT
public:
    explicit BaseController(QObject *parent = nullptr);
    void handleError(std::exception_ptr eptr, std::function<void(BizException)> func = NULL);
};

#endif // BASECONTROLLER_H
