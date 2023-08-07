#ifndef SLIDE_H
#define SLIDE_H

#include <QString>

struct Slide
{
    int id;
    QString title;
    std::optional<QString> link;
    QString url;
};

#endif // SLIDE_H
