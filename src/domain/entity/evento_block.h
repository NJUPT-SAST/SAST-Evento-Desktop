#ifndef EVENTO_BLOCK_H
#define EVENTO_BLOCK_H

#include "types.h"

#include <set>

struct DTO_Evento;

struct IEEE_Float {
    uint32_t m : 23;
    uint32_t e : 8;
    uint32_t sign : 1;

    operator float() {
        return *reinterpret_cast<float*>(this);
    }
};

template <int major_bits = 4>
struct FixedPoint {
    uint8_t fraction : 7 - major_bits;
    uint8_t major : major_bits;
    uint8_t out_of_range : 1;

    operator uint8_t() const {
        return *reinterpret_cast<const uint8_t*>(this);
    }

    template <int other>
    operator FixedPoint<other>() const {
        return *reinterpret_cast<std::enable_if_t<other != major_bits, const FixedPoint<other>>*>(
            this);
    }

    FixedPoint() {
        *(uint8_t*)this = 0;
    }

    static inline float to_float(FixedPoint t) {
        constexpr uint32_t M_OPRAND = 0b100'00000'00000'00000'00000;
        static_assert(QSysInfo::ByteOrder == QSysInfo::LittleEndian, "Big Endian Untested!");
        if (t.out_of_range)
            return t.major ? t.major + 0.5 : -0.5;
        if (!t.major && !t.fraction)
            return 0;
        IEEE_Float result;
        result.e = 127 + 24 - major_bits; // 24 - bitsize of (major)
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

inline QDate getMonday(QDate date) {
    auto day_of_week = date.dayOfWeek() - 1;
    return date.addDays(-day_of_week);
}

struct EventoBlock {
    EventoID id = -1;
    QString title;
    QDateTime gmtEventStart;
    QDateTime gmtEventEnd;
    int8_t column_or_flag = -2;
    FixedPoint<> start;
    FixedPoint<> end;
    bool editable = false;
    int depth = -1;

    EventoBlock() = default;
    EventoBlock(const DTO_Evento& event, const std::set<EventoID>& permitted);

    void fresh(QDate monday) {
        if (column_or_flag >= -1)
            return;
        if (gmtEventStart.date() < monday)
            start.out_of_range = 1;
        else
            start.major = gmtEventStart.date().dayOfWeek() - 1;
        if (gmtEventEnd.date() > monday.addDays(6)) {
            end.out_of_range = 1;
            end.major = 7;
        } else
            end.major = gmtEventEnd.date().dayOfWeek();
    }

private:
    void init() {
        if (gmtEventStart.date() == gmtEventEnd.date()) {
            auto time = gmtEventStart.time();
            if (time.hour() < 8)
                start.out_of_range = 1;
            else
                start.major = time.hour() - 8;
            if (time.hour() != 23)
                start.fraction = (time.minute() * 60 + time.second()) / 450;
            time = gmtEventEnd.time();
            if (time.hour() > 8)
                end.major = time.hour() - 8;
            if (time.hour() == 23 && time != QTime(23, 0))
                end.out_of_range = 1;
            if (time.hour() >= 8)
                end.fraction = (time.minute() * 60 + time.second()) / 450;
            column_or_flag = gmtEventStart.date().dayOfWeek() - 1;
        } else {
            if (getMonday(gmtEventStart.date()) == getMonday(gmtEventEnd.date())) {
                column_or_flag = -1;
                start.major = gmtEventStart.date().dayOfWeek() - 1;
                end.major = gmtEventEnd.date().dayOfWeek();
            }
        }
    }
};

#endif // EVENTOBLOCK_H
