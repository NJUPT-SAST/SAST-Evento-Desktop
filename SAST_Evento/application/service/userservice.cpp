#include "userservice.h"

#include "domain/exception/biz_exception.h"
#include "infrastructure/helper/user_helper.h"

bool UserService::login(const QString &username, const QString &password)
{
    try {
        const QString& token = m_repository->accessToken(username, password);
        UserHelper::getInstance()->login(token);
    } catch (const BizException& e) {
        return false;
    }
    return true;
}

