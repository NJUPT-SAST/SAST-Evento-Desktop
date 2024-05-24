#pragma once
#include "inner.h"
#include "resolver.h"
#include <cassert>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <stdexcept>
#include <type_traits>
#include <variant>

template <typename R>
class EventoPromise;

template <typename T>
struct EventoPromiseGetResultType {
    using type = T;
};

template <typename R>
struct EventoPromiseGetResultType<EventoPromise<R>> {
    using type = R;
};

template <typename F, typename R>
struct MapResultType {
    using type = std::invoke_result_t<F, R>;
};

template <typename F>
struct MapResultType<F, void> {
    using type = std::invoke_result_t<F>;
};

template <typename T>
constexpr bool is_evento_promise_v = false;

template <typename R>
constexpr bool is_evento_promise_v<EventoPromise<R>> = true;

template <typename R>
class EventoPromise {
    std::shared_ptr<EventoPromiseInner<R>> inner;

public:
    EventoPromise() : inner(nullptr) {}

    static std::tuple<EventoPromise<R>, EventoPromiseResolver<R>> deferred() {
        EventoPromise<R> promise;
        EventoPromiseResolver<R> resolver;
        resolver.inner = promise.inner = std::make_shared<EventoPromiseInner<R>>();
        return {promise, resolver};
    }

    template <typename... T>
    static EventoPromise<R> resolve(T&&... args) {
        auto [promise, resolver] = deferred();
        resolver.resolve(std::forward<T>(args)...);
        return promise;
    }

    template <typename InputIt>
    static EventoPromise<std::vector<R>> all(InputIt first, InputIt last) {
        auto [promise, resolver] = EventoPromise<std::vector<R>>::deferred();
        auto count = std::distance(first, last);
        auto remaining = std::make_shared<size_t>(count);
        auto mtx = std::make_shared<std::mutex>();
        if constexpr (std::is_void_v<R>) {
            if (count == 0) {
                resolver.resolve();
            } else {
                for (auto it = first; it != last; ++it) {
                    (*it).then([remaining, resolver, mtx]() {
                        std::unique_lock<std::mutex> lock(*mtx);
                        if (--*remaining == 0) {
                            lock.unlock();
                            resolver.resolve();
                        }
                    });
                }
            }
        } else {
            size_t index = 0;
            auto result = std::make_shared<std::vector<R>>();
            if (count == 0) {
                resolver.resolve(std::move(*result));
            } else {
                result->resize(count);
                for (auto it = first; it != last; ++it) {
                    (*it).then([result, resolver, remaining, mtx, index](R value) {
                        std::unique_lock<std::mutex> lock(*mtx);
                        (*result)[index] = std::move(value);
                        if (--*remaining == 0) {
                            lock.unlock();
                            resolver.resolve(std::move(*result));
                        }
                    });
                    index++;
                }
            }
        }
        return promise;
    }

    template <typename FResolve>
    void consume(FResolve on_resolve) {
        auto inner = std::move(this->inner);
        std::lock_guard<std::mutex> lock(inner->mtx);
        if (inner->is_completed()) {
            if constexpr (std::is_void_v<R>) {
                inner->consume();
                on_resolve();
            } else {
                on_resolve(inner->consume());
            }
        } else {
            inner->on_resolve = on_resolve;
        }
    }

    void forward_to(EventoPromiseResolver<R> resolver) {
        if constexpr (std::is_void_v<R>) {
            this->consume([resolver]() { resolver.resolve(); });
        } else {
            this->consume([resolver](R result) { resolver.resolve(std::move(result)); });
        }
    }

    template <typename F>
    auto then(F on_resolve)
        -> EventoPromise<
            typename EventoPromiseGetResultType<typename MapResultType<F, R>::type>::type> {
        auto inner = std::move(this->inner);
        std::lock_guard<std::mutex> lock(inner->mtx);
        using U = typename EventoPromiseGetResultType<typename MapResultType<F, R>::type>::type;
        if constexpr (is_evento_promise_v<typename MapResultType<F, R>::type>) {
            if (inner->is_completed()) {
                if constexpr (std::is_void_v<R>) {
                    inner->consume();
                    return on_resolve();
                } else {
                    return on_resolve(inner->consume());
                }
            } else {
                auto [promise, resolver] = EventoPromise<U>::deferred();
                if constexpr (std::is_void_v<R>) {
                    inner->on_resolve = [on_resolve = std::move(on_resolve), resolver]() {
                        on_resolve().forward_to(resolver);
                    };
                } else {
                    inner->on_resolve = [on_resolve = std::move(on_resolve), resolver](R result) {
                        on_resolve(std::move(result)).forward_to(resolver);
                    };
                }
                return promise;
            }
        } else {
            if (inner->is_completed()) {
                if constexpr (std::is_void_v<R> && std::is_void_v<U>) {
                    inner->consume();
                    on_resolve();
                    return EventoPromise<U>::resolve();
                } else if constexpr (std::is_void_v<R>) {
                    inner->consume();
                    return EventoPromise<U>::resolve(on_resolve());
                } else if constexpr (std::is_void_v<U>) {
                    on_resolve(inner->consume());
                    return EventoPromise<U>::resolve();
                } else {
                    return EventoPromise<U>::resolve(on_resolve(inner->consume()));
                }
            } else {
                auto [promise, resolver] = EventoPromise<U>::deferred();
                if constexpr (std::is_void_v<R>) {
                    inner->on_resolve = [on_resolve = std::move(on_resolve), resolver]() {
                        if constexpr (std::is_void_v<U>) {
                            on_resolve();
                            resolver.resolve();
                        } else {
                            resolver.resolve(on_resolve());
                        }
                    };
                } else {
                    inner->on_resolve = [on_resolve = std::move(on_resolve), resolver](R result) {
                        if constexpr (std::is_void_v<U>) {
                            on_resolve(std::move(result));
                            resolver.resolve();
                        } else {
                            resolver.resolve(on_resolve(std::move(result)));
                        }
                    };
                }
                return promise;
            }
        }
    }
};
