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
    PermissionDTO dto;
    // Query
    return Converter::dto2PermissonEntry(dto);
}

Evento RepositoryImpl::evento(int eventId)
{
    EventDTO eventDto;
    // Query
    return Converter::dto2Evento(eventDto);
}

Image RepositoryImpl::image(int eventId)
{
    ImageDTO dto;
    // Query
    return Converter::dto2Image(dto);
}

std::vector<LatestEvento> RepositoryImpl::latestEventoModel()
{
    std::vector<LatestEvento> result;
    EventDTO eventDto;
    ImageDTO imageDto;
    // Query
    // loop
    auto ele = Converter::dto2LatestEvento(eventDto, imageDto);
    result.emplace_back(std::move(ele));
    // loop
    return result;
}

std::vector<UndertakingEvento> RepositoryImpl::undertakingEventoModel()
{
    std::vector<UndertakingEvento> result;
    EventDTO eventDto;
    ImageDTO imageDto;
    // Query
    // loop
    auto ele = Converter::dto2UndertakingEvento(eventDto, imageDto);
    result.emplace_back(std::move(ele));
    // loop
    return result;
}

std::vector<Slide> RepositoryImpl::slideModel()
{
    std::vector<Slide> result;
    SlideDTO dto;
    // Query
    // loop
    auto ele = Converter::dto2Slide(dto);
    result.emplace_back(std::move(ele));
    // loop
    return result;
}

std::vector<Image> RepositoryImpl::imageModel(int eventId)
{
    std::vector<Image> result;
    ImageDTO dto;
    // Query
    // loop
    auto ele = Converter::dto2Image(dto);
    result.emplace_back(std::move(ele));
    // loop
    return result;
}

std::vector<EventoBrief> RepositoryImpl::historyEventoModel(const QString &userId)
{
    std::vector<EventoBrief> result;
    EventDTO eventDto;
    ImageDTO imageDto;
    // Query
    // loop
    auto ele = Converter::dto2EventoBrief(eventDto, imageDto);
    result.emplace_back(std::move(ele));
    // loop
    return result;
}

std::vector<EventoBrief> RepositoryImpl::departmentEventoModel(int departmentId)
{
    std::vector<EventoBrief> result;
    EventDTO eventDto;
    ImageDTO imageDto;
    // Query
    // loop
    auto ele = Converter::dto2EventoBrief(eventDto, imageDto);
    result.emplace_back(std::move(ele));
    // loop
    return result;
}

std::vector<Schedule> RepositoryImpl::scheduleModel(const QString &userId)
{
    std::vector<Schedule> result;
    EventDTO eventDto;
    ImageDTO imageDto;
    // Query
    // loop
    auto ele = Converter::dto2Schedule(eventDto, imageDto);
    result.emplace_back(std::move(ele));
    // loop
    return result;
}

std::vector<EventoBlock> RepositoryImpl::eventoBlockModel()
{
    std::vector<EventoBlock> result;
    EventDTO eventDto;
    // Query
    // loop
    auto ele = Converter::dto2EventoBlock(eventDto);
    result.emplace_back(std::move(ele));
    // loop
    return result;
}

std::vector<Feedback> RepositoryImpl::feedbackModel(int eventId)
{
    std::vector<Feedback> result;
    EventDTO eventDto;
    FeedbackDTO feedbackDto;
    // Query
    // loop
    auto ele = Converter::dto2Feedback(eventDto, feedbackDto);
    result.emplace_back(std::move(ele));
    // loop
    return result;
}

std::vector<PermissionEntry> RepositoryImpl::permissionModel()
{
    std::vector<PermissionEntry> result;
    PermissionDTO dto;
    // Query
    // loop
    auto ele = Converter::dto2PermissonEntry(dto);
    result.emplace_back(std::move(ele));
    // loop
    return result;
}

std::vector<UserBrief> RepositoryImpl::userbriefModel(const QString &userId)
{
    std::vector<UserBrief> result;
    PermissionDTO dto;
    // Query
    // loop
    auto ele = Converter::dto2UserBrief(dto);
    result.emplace_back(std::move(ele));
    // loop
    return result;
}
