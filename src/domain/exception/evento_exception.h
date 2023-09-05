#ifndef EVENTO_EXCEPTION_H
#define EVENTO_EXCEPTION_H

#include <QString>

enum class EventoExceptionCode {
    NetworkError = -3,
    JsonError = -2,
    UnexpectedError = -1,
    Ok,
};

template <EventoExceptionCode code = EventoExceptionCode::UnexpectedError>
struct DefaultMessage {
    static constexpr char msg[] = "Unexpected Error Encountered!";
};

class EventoException {
   private:
    EventoExceptionCode m_code;
    QString m_message;

   public:
    EventoException(EventoExceptionCode code = EventoExceptionCode::Ok,
                    const QString& msg = "")
        : m_code(code), m_message(msg) {}
    QString message() { return m_message; }
    EventoExceptionCode code() { return m_code; }

    operator bool() { return m_code != EventoExceptionCode::Ok; }
};

#endif
