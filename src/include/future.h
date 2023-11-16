#ifndef FUTURE_H
#define FUTURE_H

#include <QFuture>

#include "evento_exception.h"

struct EventoFutureBase {
    bool valid;
    EventoFutureBase* base;

    EventoFutureBase(bool valid = false, EventoFutureBase* base = nullptr)
        : valid(valid), base(base) {}
    virtual ~EventoFutureBase() {
        delete base;
    }

    virtual EventoFutureBase* clone() const = 0;
};

template <typename QFuture>
struct GetQFutureType;

template <typename T>
struct GetQFutureType<QFuture<T>> {
    using Type = T;
};

template <typename T>
class EventoFuture : public EventoFutureBase {
protected:
    QFuture<T> future;

public:
    EventoFuture() = default;
    EventoFuture(const EventoFuture<T>& other)
        : EventoFutureBase(other.valid, other.base ? other.base->clone() : nullptr),
          future(other.future) {}
    EventoFuture(EventoFuture<T>&& other)
        : EventoFutureBase(other.valid, other.base), future(other.future) {
        other.reset();
    }
    EventoFuture(const QFuture<T>& future) : EventoFutureBase(future.isValid()), future(future) {}

    template <typename U>
    EventoFuture(const EventoFuture<U>& parent, const QFuture<T>& future)
        : EventoFutureBase(parent.valid, parent.clone()), future(future) {}

public:
    void reset() {
        future = QFuture<T>();
        base = nullptr;
    }
    EventoFutureBase* clone() const override {
        if (future.isFinished() || future.isCanceled())
            return nullptr;
        return new EventoFuture<T>(*this);
    }

public:
    template <typename U, typename Type = typename GetQFutureType<
                              decltype(std::declval<QFuture<T>>().then(std::declval<U>()))>::Type>
    inline EventoFuture<Type> then(U&& function) {
        return EventoFuture<Type>(*this, future.then(QtFuture::Launch::Async, function));
    }

    template <typename U = T>
    typename std::enable_if_t<!std::is_same_v<void, U>, U> takeResult() {
        if (!valid || future.isCanceled() ||
            !future.isValid() && future.isFinished() && !future.isRunning())
            throw EventoException(EventoExceptionCode::FutureError,
                                  DefaultMessage<EventoExceptionCode::FutureError>::msg);
        return future.takeResult();
    }

    void waitForFinished() {
        if (!valid || !base && !future.isValid())
            throw EventoException(EventoExceptionCode::FutureError,
                                  DefaultMessage<EventoExceptionCode::FutureError>::msg);
        return future.waitForFinished();
    }

    operator const QFuture<T>&() {
        return future;
    }
};

#endif // FUTURE_H
