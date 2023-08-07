#pragma once

#include <QDateTime>
#include <QJsonDocument>
#include <QObject>
#include <QTimeZone>
#include "domain/entity/slide.h"
#include "infrastructure/dto/slidedto.h"

class Converter {
public:
    static Slide dto2User(const SlideDTO& val);
};
