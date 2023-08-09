#ifndef FEEDBACKDTO_H
#define FEEDBACKDTO_H

#include <infrastructure/nlohmann/json.hpp>

struct FeedbackDTO
{
    int id;
    int score;
    std::string content;
    int participateId;
    std::string userId;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(FeedbackDTO, id, score, content, participateId, userId)

#endif // FEEDBACKDTO_H
