#ifndef EVENTO_BLOCK_H
#define EVENTO_BLOCK_H

#include "types.h"

#include <set>

struct DTO_Evento;

struct TimePoint {
    uint8_t fraction : 3;
    uint8_t major : 4;
    uint8_t ahead : 1;

    operator uint8_t() {
        return *reinterpret_cast<uint8_t*>(this);
    }

    TimePoint() {
        *(uint8_t*)this = 0;
    }

    struct IEEE_Float {
        uint32_t m : 23;
        uint32_t e : 8;
        uint32_t sign : 1;

        operator float() {
            return *reinterpret_cast<float*>(this);
        }
    };

    static inline float to_float(TimePoint t) {
        constexpr uint32_t M_OPRAND = 0b100'00000'00000'00000'00000;
        static_assert(QSysInfo::ByteOrder == QSysInfo::LittleEndian, "Big Endian Untested!");
        if (t.ahead)
            return t.major ? t.major + 0.5 : -0.5;
        if (!t.major && !t.fraction)
            return 0;
        t.ahead = 0;
        IEEE_Float result;
        result.e = 127 + 20; // 24 - bitsize of (major)
        result.m = t;
        result.sign = 0;
        while (!(result.m & M_OPRAND)) {
            result.m <<= 1;
            result.e--;
        }
        result.m <<= 1;
        result.e--;
        return result;
    }
};

struct EventoBlock {
    EventoID id = -1;
    QString title;
    QDateTime gmtEventStart;
    QDateTime gmtEventEnd;
    int8_t column_or_flag = -2;
    TimePoint start; // index: 8:00 -> 0
    TimePoint end;   // index: 23:00 -> 15
    bool editable = false;
    int depth = -1;

    EventoBlock() = default;
    EventoBlock(const DTO_Evento& event, const std::set<EventoID>& permitted);

    void fresh(QDate monday) {
        if (column_or_flag >= -1)
            return;
        if (gmtEventStart.date() < monday)
            start.ahead = 1;
        else
            start.major = gmtEventStart.date().dayOfWeek() - 1;
        if (gmtEventEnd.date() > monday.addDays(6)) {
            end.ahead = 1;
            end.major = 7;
        } else
            end.major = gmtEventEnd.date().dayOfWeek();
    }
};

static inline QDate getMonday(QDate date) {
    auto day_of_week = date.dayOfWeek() - 1;
    return date.addDays(-day_of_week);
}

#endif // EVENTOBLOCK_H
