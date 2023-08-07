#ifndef FEEDBACKDTO_H
#define FEEDBACKDTO_H

#include <QString>

struct FeedbackDTO
{
    int id;
    int score;
    QString content;
    int participateId;
    QString userId;
};

#endif // FEEDBACKDTO_H
