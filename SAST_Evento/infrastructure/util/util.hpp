#ifndef UTIL_HPP
#define UTIL_HPP

#include <type_traits>

template <typename E>
constexpr auto
toUType(E enumerator) noexcept
{
    return static_cast<std::underlying_type_t<E>>(enumerator);
}

#endif // UTIL_HPP
