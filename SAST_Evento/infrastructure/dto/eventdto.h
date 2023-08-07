#ifndef EVENTDTO_H
#define EVENTDTO_H

#include <QString>
#include <QDateTime>

class EventDTO
{
public:
    enum class EventoState {
        Before,
        Registration,
        Undertaking,
        Cancelled,
        Over
    };

    EventDTO(int id,
             QString title,
             QString description,
             QString gmtEventStart,
             QString gmtEventEnd,
             QString gmtRegistrationStart,
             QString gmtRegistrationEnd,
             int typeId,
             int locationId,
             QString tag,
             int state);

    int getEventId() const { return m_id; }

protected:
    int m_id;
    QString m_title;
    QString m_description;
    QDateTime m_gmtEventStart;
    QDateTime m_gmtEventEnd;
    QDateTime m_gmtRegistrationStart;
    QDateTime m_gmtRegistrationEnd;
    int m_typeId;
    int m_locationId;
    QString m_tag;
    EventoState m_state;
};

//`id`                     int          NOT NULL AUTO_INCREMENT COMMENT '活动id',
//`title`                  varchar(50)  NOT NULL COMMENT '活动标题',
//`description`            text         NOT NULL COMMENT '活动简介',
//`gmt_event_start`        datetime     NOT NULL COMMENT '活动开始时间',
//`gmt_event_end`          datetime     NOT NULL COMMENT '活动截至时间',
//`gmt_registration_start` datetime     NOT NULL COMMENT '活动报名开始时间',
//`gmt_registration_end`   datetime     NOT NULL COMMENT '活动报名截至时间',
//`type_id`                int          NOT NULL COMMENT '分类id',
//`location_id`            int          NOT NULL COMMENT '地点id',
//`tag`                    varchar(225) NOT NULL COMMENT '活动标签',
//`state`                  int

#endif // EVENTDTO_H
