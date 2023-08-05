#include "feedback.h"

Feedback::Feedback(EventoBase evento,
                   int score,
                   QString comment)
: EventoBase(std::move(evento)), m_score(score),
  m_comment(std::move(comment)) {}
