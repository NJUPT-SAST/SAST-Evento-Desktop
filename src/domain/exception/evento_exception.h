#ifndef EVENTO_EXCEPTION_H
#define EVENTO_EXCEPTION_H

#include <QString>

enum class EventoExceptionCode {
    Uninitialised = -1,
    UnexpectedError = -2,
    Ok = 0,
    NetworkError = 1,
    JsonError = 2,
};

template <EventoExceptionCode code = EventoExceptionCode::UnexpectedError>
struct DefaultMessage;

template <>
struct DefaultMessage<EventoExceptionCode::UnexpectedError> {
    static constexpr char msg[] = "Unexpected Error Encountered!";
};

template <>
struct DefaultMessage<EventoExceptionCode::Uninitialised> {
    static constexpr char msg[] = "Uninitialised or Moved!";
};

template <>
struct DefaultMessage<EventoExceptionCode::Ok> {
    static constexpr char msg[] = "No Error!";
};

class alignas(32) EventoException {
private:
    alignas(8) EventoExceptionCode m_code;
    alignas(8) QString m_message;

public:
    EventoException(EventoExceptionCode code = EventoExceptionCode::Ok, const QString& msg = DefaultMessage<EventoExceptionCode::Ok>::msg) : m_code(code), m_message(msg) {}
    EventoException(const EventoException&) = default;

    inline QString message() const {
        return *this ? m_message : QStringLiteral("No Error!");
    }
    inline EventoExceptionCode code() const { return m_code; }

    inline operator bool() const {
        return m_code != EventoExceptionCode::Ok;
    }
};

#endif
