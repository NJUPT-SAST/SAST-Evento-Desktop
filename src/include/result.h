#ifndef EVENTO_RESULT_H
#define EVENTO_RESULT_H

#include "evento_exception.h"

template<typename T = bool>
class EventoResult {
    union alignas(32) Member {
        alignas(32) EventoException err;
        struct alignas(32) Data {
            alignas(8) EventoExceptionCode err_code = EventoExceptionCode::Ok;
            T result;

            Data() : err_code(EventoExceptionCode::Uninitialised), result() {}
            Data(T&& other) : result(std::move(other)) {}
            Data(const T& other) : result(other) {}
            ~Data() = default;
        } data;

        Member() : data() {}
        Member(EventoException&& other) : err(std::move(other)) {}
        Member(EventoExceptionCode code, const QString& msg) : err{code, msg} {}
        Member(T&& other) : data(std::move(other)) {}
        Member(Member&& other) : data() {
            if (other.err)
                err = std::move(other.err);
            else
                data = std::move(other.data.result);
            other.reset();
        }
        Member(const Member&) = delete;

        Member& operator=(Member&& other) {
            if (other.err)
                err = std::move(other.err);
            else
                data = std::move(other.data.result);
            other.reset();
            return *this;
        }

        ~Member() {
            if (err)
                err.~EventoException();
            else
                data.~Data();
        }
    private:
        void reset() {
            if (!err)
                data.~Data();
            new (this) Member(EventoExceptionCode::Uninitialised, "Moved!");
        }
    } member;
public:
    EventoResult() = default;
    EventoResult(EventoException&& other) : member(std::move(other)) {}
    EventoResult(EventoExceptionCode code, const QString& msg) : member(code, msg) {}
    EventoResult(T&& other) : member(std::move(other)) {}
    EventoResult(EventoResult&& other) : member(std::move(other.member)) {}
    EventoResult(const EventoResult&) = delete;

    EventoResult& operator=(EventoResult&& other) {
        member = std::move(other.member);
        return *this;
    }

    ~EventoResult() = default;

    inline QString message() {
        return *this ? QStringLiteral("No Error!") : member.err.message();
    }
    inline EventoExceptionCode code() { return member.err.code(); }

    inline operator bool() { return member.err.code() == EventoExceptionCode::Ok; }
    inline operator const EventoException&() {
        return reinterpret_cast<const EventoException&>(*this);
    }
    inline T take() {
        T result = *this ? std::move(member.data.result) : T();
        new (this) EventoResult;
        return result;
    }
};

template<>
struct EventoResult<bool> : public EventoException {
    EventoResult() = default;
    EventoResult(EventoException&& other) : EventoException(std::move(other)) {}
    EventoResult(EventoExceptionCode code, const QString& msg) : EventoException(code, msg) {}
    EventoResult(EventoResult&& other) : EventoException(std::move(other)) {}
    EventoResult(const EventoResult&) = delete;

    inline operator bool() { return !EventoException::operator bool(); }
};

#endif // EVENTO_RESULT_H
