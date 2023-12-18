#ifndef MOVABLE_LAMBDA_H
#define MOVABLE_LAMBDA_H

#include <functional>
#include <type_traits>

template <typename T, typename ReturnType = void>
class MovableLambda {
    std::remove_reference_t<T> stored;
    std::function<ReturnType(std::remove_reference_t<T>&&)> func;

public:
    template <typename Fun>
    MovableLambda(T&& arg, Fun&& f) : stored(std::move(arg)), func(f) {}

    ReturnType operator()() {
        return func(std::move(stored));
    }
};

#endif // MOVABLE_LAMBDA_H
