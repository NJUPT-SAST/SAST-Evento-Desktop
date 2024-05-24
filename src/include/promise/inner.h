#pragma once
#include <cassert>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <stdexcept>
#include <variant>

template <typename R>
struct EventoPromiseInner {
    std::mutex mtx;
    std::optional<R> stored_result;
    std::function<void(R)> on_resolve;
    bool is_consumed = false;

    bool is_completed() const {
        return stored_result.has_value();
    }

    R&& consume() {
        if (is_consumed) {
            throw std::runtime_error("Promise already consumed");
        }
        assert(is_completed());
        is_consumed = true;
        return std::move(*stored_result);
    }

    template <typename... T>
    void resolve(T&&... result) {
        std::lock_guard<std::mutex> lock(mtx);
        if (is_completed()) {
            throw std::runtime_error("Promise already completed");
        }
        stored_result.emplace(std::forward<T>(result)...);
        if (on_resolve) {
            on_resolve(consume());
        }
    }
};

template <>
struct EventoPromiseInner<void> {
    std::mutex mtx;
    bool stored_result = false;
    std::function<void()> on_resolve;
    bool is_consumed = false;

    bool is_completed() const {
        return stored_result;
    }

    void consume() {
        if (is_consumed) {
            throw std::runtime_error("Promise already consumed");
        }
        assert(is_completed());
        is_consumed = true;
    }

    void resolve() {
        std::lock_guard<std::mutex> lock(mtx);
        if (is_completed()) {
            throw std::runtime_error("Promise already completed");
        }
        stored_result = true;
        if (on_resolve) {
            on_resolve();
        }
    }
};