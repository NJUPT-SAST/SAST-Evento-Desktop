#include "userservice.h"

#include "infrastructure/helper/user_helper.h"

void UserService::login(const QString& code){
    const QString& token =  _repository->accessToken("ebf59d49ca54dae4bda5","308363e4ab2d5687894d05d3d7f0e63aa22a020b",code);
    UserHelper::getInstance()->login(token);
    Q_EMIT loginSuccess();
}

User UserService::loadUser(){
    return _repository->user();
}
