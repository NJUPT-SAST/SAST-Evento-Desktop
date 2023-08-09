#ifndef BIZEXCEPTION_H
#define BIZEXCEPTION_H

#include <QObject>
#include <QException>

class BizException  : public QException
{
public:
    void raise() const override { throw *this; }
    BizException *clone() const override { return new BizException(*this); }

    BizException(const QString& message = "业务异常", int code = -1) : code(code), message(message)
    {
    }
    BizException(int code = -1, const QString& message = "业务异常") : code(code), message(message)
    {
    }
    int code;
    QString message;
};



#endif  // BIZEXCEPTION_H
