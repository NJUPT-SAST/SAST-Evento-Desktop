#ifndef EVENTO_EXCEPTION_H
#define EVENTO_EXCEPTION_H

#include <QString>

enum class EventoExceptionCode {
	UnexpectedError = -1,
};

template<EventoExceptionCode code = EventoExceptionCode::UnexpectedError>
struct DefaultMessage {
    static constexpr char msg[] = "Unexpected Error Encountered!";
};

class EventoException {
private:
	EventoExceptionCode code;
	QString message;

    EventoException(EventoExceptionCode code, const QString& msg) : code(code), message(msg) {};
};

#endif
