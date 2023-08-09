#include "basecontroller.h"
#include <QDebug>

BaseController::BaseController(QObject *parent): QObject{parent}
{

}

void BaseController::handleError(std::exception_ptr eptr, std::function<void(BizException)> func)
{
  try
  {
    if (eptr)
    {
      std::rethrow_exception(eptr);
    }
  }
  catch (const BizException& e)
  {
    if (func)
    {
      func(e);
    }
    qDebug() << (QString::fromStdString("【业务异常】code->%1，msg->%2").arg(e.code).arg(e.message));
  }
  catch (std::exception e)
  {
    if (func)
    {
      func(BizException("未知异常"));
    }
    qDebug() << (QString::fromStdString("【未知异常】message->%1").arg(e.what()));
  }
}
