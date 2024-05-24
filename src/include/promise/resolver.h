#pragma once
#include "inner.h"
#include <cassert>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <stdexcept>
#include <variant>

template <typename R>
class EventoPromiseResolver {
public:
    std::shared_ptr<EventoPromiseInner<R>> inner;

    template <typename... T>
    void resolve(T&&... args) const {
        inner->resolve(std::forward<T>(args)...);
    }
};