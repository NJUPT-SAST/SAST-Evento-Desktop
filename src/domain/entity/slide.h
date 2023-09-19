#ifndef SLIDE_H
#define SLIDE_H

#include <QString>

struct DTO_Slide;

struct Slide
{
    int id;
    QString title;
    QString link;
    QString url;

    Slide() = default;
    Slide(const DTO_Slide&);
};

#endif // SLIDE_H
