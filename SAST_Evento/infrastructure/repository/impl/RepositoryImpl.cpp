#include "repositoryimpl.h"

#include <infrastructure/nlohmann/json.hpp>
#include "domain/exception/biz_exception.h"
#include "infrastructure/converter/converter.h"
#include "infrastructure/helper/CommonHelper.h"
#include "infrastructure/tool/RxHttp.h"
#include "infrastructure/dto/UserDto.h"
#include "infrastructure/dto/TokenDto.h"

using namespace AeaQt;
using namespace nlohmann;

RepositoryImpl::RepositoryImpl(QObject* parent) : Repository{ parent }
{

}

template <typename T>
void RepositoryImpl::handleResult(QString result, T& data,QString type)
{
    try{
        CommonHelper::getInstance()->jsonNonNull(result);
        const QJsonObject& obj = CommonHelper::getInstance()->json2Object(result);
        json j = json::parse(result.toStdString());
        if(!type.isEmpty()){
            j = j["data"][type.toStdString()];
        }
        data = j.get<T>();
    }
    catch (std::exception e)
    {
        throw BizException(-1, "Json解析异常");
    }
}

//QString RepositoryImpl::accessToken(const QString &id,const QString &secret,const QString &code){
//    const QVariantMap& data = {
//        {"client_id",id},
//        {"client_secret",secret},
//        {"code",code}
//    };
//    TokenDto dto;
//    handleResult(RxHttp::get(html("/login/oauth/access_token"),data),dto);
//    return QString::fromStdString(dto.access_token);
//}

//User RepositoryImpl::user(){
//    UserDto dto;
//    QString query = R"(query {
//  viewer {
//    login
//    bio
//    name
//    location
//    websiteUrl
//    avatarUrl
//    company
//    followers {
//      totalCount
//    }
//    following {
//      totalCount
//    }
//    status {
//      emojiHTML
//      message
//    }
//  }
//})";
//    const QVariantMap& data = {
//                               {"query",query},
//                               };
//    handleResult(RxHttp::postJson("https://api.github.com/graphql",data),dto,"viewer");
//    return Converter::dto2User(dto);
//}
