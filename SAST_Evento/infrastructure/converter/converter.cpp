#include <QDateTime>
#include <QJsonDocument>
#include <QObject>
#include <QTimeZone>

#include "converter.h"

Department Converter::dto2Department(const DepartmentDTO &dep)
{

}

Evento Converter::dto2Evento(const EventDTO &event)
{

}

EventoBlock Converter::dto2EventoBlock(const EventDTO &event)
{

}

EventoBrief Converter::dto2EventoBrief(const EventDTO &event, const ImageDTO &image)
{

}

Feedback Converter::dto2Feedback(const EventDTO &event, const FeedbackDTO &feedback)
{

}

LatestEvento Converter::dto2LatestEvento(const EventDTO &event, const ImageDTO &image)
{

}

PermissionEntry Converter::dto2PermissonEntry(const PermissionDTO &permission)
{

}

Schedule Converter::dto2Schedule(const EventDTO &event, const ImageDTO &image)
{

}

Slide Converter::dto2Slide(const SlideDTO &slide)
{
    Slide obj;
    obj.id = slide.id;
    obj.title = QString::fromStdString(slide.title);
    obj.link = QString::fromStdString(slide.link);
    obj.url = QString::fromStdString(slide.url);
    return obj;
}

Image Converter::dto2Image(const ImageDTO &image)
{
    Image obj;
    obj.id = image.id;
    obj.title = QString::fromStdString(image.title);
    obj.url = QString::fromStdString(image.url);
    return obj;
}

UndertakingEvento Converter::dto2UndertakingEvento(const EventDTO &event, const ImageDTO &image)
{

}

UserBrief Converter::dto2UserBrief(const PermissionDTO &permission)
{

}

