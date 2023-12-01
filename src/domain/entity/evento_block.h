#ifndef EVENTO_BLOCK_H
#define EVENTO_BLOCK_H

#include "types.h"

#include <bit>
#include <set>

struct DTO_Evento;

struct TimePoint {
    uint8_t fraction : 3 = 0;
    uint8_t major : 4 = 0;
    uint8_t ahead : 1 = 0;

    struct IEEE_Float {
        uint32_t m : 23;
        uint32_t e : 8;
        uint32_t sign : 1 = 0;
    };

    static constexpr uint32_t M_OPRAND = 0b100'00000'00000'00000'00000;

    static inline float to_float(TimePoint t) {
        static_assert(std::endian::native == std::endian::little, "Big Endian Untested!");
        if (t.ahead)
            return t.major ? std::bit_cast<float>(0b01111111100000000000000000000000)
                           : std::bit_cast<float>(0b11111111100000000000000000000000);
        if (!t.major && !t.fraction)
            return 0;
        t.ahead = 0;
        IEEE_Float result{.m = std::bit_cast<uint8_t>(t), .e = 127 + 20}; // 24 - bitsize of (major)
        while (!(result.m & M_OPRAND)) {
            result.m <<= 1;
            result.e--;
        }
        result.m <<= 1;
        result.e--;
        return std::bit_cast<float>(result);
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
            start.ahead = gmtEventStart.date().dayOfWeek() - 1;
        if (gmtEventEnd.date() > monday) {
            end.ahead = 1;
            end.major = 6;
        } else
            end.major = gmtEventEnd.date().dayOfWeek() - 1;
    }
};

static inline QDate getMonday(QDate date) {
    auto day_of_week = date.dayOfWeek() - 1;
    return date.addDays(-day_of_week);
}

#endif // EVENTOBLOCK_H
