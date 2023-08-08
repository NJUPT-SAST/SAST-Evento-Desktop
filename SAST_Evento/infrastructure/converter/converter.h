#pragma once

#include "domain/entity/department.h"
#include "domain/entity/evento.h"
#include "domain/entity/eventoblock.h"
#include "domain/entity/eventobrief.h"
#include "domain/entity/feedback.h"
#include "domain/entity/latestevento.h"
#include "domain/entity/permissionentry.h"
#include "domain/entity/schedule.h"
#include "domain/entity/slide.h"
#include "domain/entity/undertakingevento.h"
#include "domain/entity/userbrief.h"
#include "domain/entity/image.h"

#include "infrastructure/dto/departmentdto.h"
#include "infrastructure/dto/eventdto.h"
#include "infrastructure/dto/feedbackdto.h"
#include "infrastructure/dto/permissiondto.h"
#include "infrastructure/dto/slidedto.h"
#include "infrastructure/dto/imagedto.h"

class Converter {
public:
    static Department dto2Department(const DepartmentDTO& dep);
    static Evento dto2Evento(const EventDTO& event);
    static EventoBlock dto2EventoBlock(const EventDTO& event);
    static EventoBrief dto2EventoBrief(const EventDTO& event, const ImageDTO& image);
    static Feedback dto2Feedback(const EventDTO& event, const FeedbackDTO& feedback);
    static LatestEvento dto2LatestEvento(const EventDTO& event, const ImageDTO& image);
    static PermissionEntry dto2PermissonEntry(const PermissionDTO& permission);
    static Schedule dto2Schedule(const EventDTO& event, const ImageDTO& image);
    static Slide dto2Slide(const SlideDTO& slide);
    static Image dto2Image(const ImageDTO& image);
    static UndertakingEvento dto2UndertakingEvento(const EventDTO& event, const ImageDTO& image);
    static UserBrief dto2UserBrief(const PermissionDTO& permission);
};
