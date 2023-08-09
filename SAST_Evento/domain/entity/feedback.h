#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <QString>

struct Feedback
{
    int id;
    int score;
    QString content;
    int participateId;
    QString userId;
};

#endif // FEEDBACK_H
