#include "repositoryimpl.h"

#include <infrastructure/nlohmann/json.hpp>
#include "domain/exception/biz_exception.h"
#include "infrastructure/converter/converter.h"
#include "infrastructure/helper/common_helper.h"
#include "infrastructure/dto/loginkeydto.h"

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

QString RepositoryImpl::accessToken(const QString& id, const QString& psw){
    const QVariantMap& data = {
        {"uid",id},
        {"password",psw},
    };
    LoginKeyDTO dto;
    // Query
    // Cache
    return QString::fromStdString(dto.token);
}

PermissionEntry RepositoryImpl::permissionEntry()
{

}

Evento RepositoryImpl::evento(const QString &eventId)
{
    EventDTO eventDto;
    SlideDTO slideDto;
    // Query
    return Converter::dto2Evento(eventDto, slideDto);
}

Slide RepositoryImpl::slide()
{
    SlideDTO dto;
    // Query
    return Converter::dto2Slide(dto);
}

LatestEventoModel RepositoryImpl::latestEventoModel()
{

}

UndertakingEventoModel RepositoryImpl::undertakingEventoModel()
{

}

SlideModel RepositoryImpl::slideModel()
{

}

ImageModel RepositoryImpl::imageModel(int eventId)
{

}

EventoBriefModel RepositoryImpl::historyEventoModel(const QString &userId)
{

}

EventoBriefModel RepositoryImpl::departmentEventoModel(int departmentId)
{

}

ScheduleModel RepositoryImpl::scheduleModel(const QString &userId)
{

}

EventoBlockModel RepositoryImpl::eventoBlockModel()
{

}

FeedbackModel RepositoryImpl::feedbackModel(int eventId)
{

}

UserBriefModel RepositoryImpl::userbriefModel(const QString &userId)
{

}



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
