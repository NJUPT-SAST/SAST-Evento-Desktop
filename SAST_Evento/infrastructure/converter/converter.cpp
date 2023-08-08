#include <QDateTime>
#include <QJsonDocument>
#include <QObject>
#include <QTimeZone>

#include "converter.h"

Department Converter::dto2Department(const DepartmentDTO &dep)
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

Image Converter::dto2Image(const SlideDTO &slide)
{
    Image obj;
    obj.id = slide.id;
    obj.title = QString::fromStdString(slide.title);
    obj.url = QString::fromStdString(slide.url);
    return obj;
}

