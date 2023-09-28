#ifndef CONVERTOR_H
#define CONVERTOR_H

#include <QDateTime>
#include <QString>

#include "types.h"

inline QString periodConvertor(const QString& startTime, const QString& endTime) {
    auto start = QDateTime::fromString(startTime, "yyyy-MM-dd hh:mm:ss");
    auto end = QDateTime::fromString(endTime, "yyyy-MM-dd hh:mm:ss");
    if (!start.isValid() || !end.isValid())
        return {};
    if (start.date() == end.date())
        return start.toString("MM.dd hh:mm") + "-" + end.toString("hh:mm");
    else if (start.date().year() == end.date().year())
        return start.toString("MM.dd hh:mm") + " - " + end.toString("MM.dd hh:mm");
    return start.toString("yyyy.MM.dd hh:mm") + " - " + end.toString("yyyy.MM.dd hh:mm");
}

inline QString departmentConvertor(const std::vector<Department>& departments) {
    QString result;
    auto iter = departments.cbegin();
    if (iter != departments.cend()) {
        result += iter->name;
        ++iter;
    }
    while (iter != departments.cend()) {
        result += "，";
        result += iter->name;
        ++iter;
    }
    return result;
}

inline QString timeConvertor(const QString& time) {
    return QDateTime::fromString(time, "yyyy-M-d h:m").toString("yyyy-MM-dd hh:mm:ss");
}

#endif // CONVERTOR_H
