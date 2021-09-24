#ifndef CLEARIO_TRAITS_HPP
#define CLEARIO_TRAITS_HPP

#include <limits>      // std::numeric_limits
#include <concepts>    // std::integral
#include <algorithm>   // std::max
#include <type_traits> // std::enable_if_t, std::is_pointer_v, std::is_class_v

namespace clear::impl
{
	template <class T>
	concept Pointer = std::is_pointer_v<T>;

	template <class T>
	concept Class = std::is_class_v<T>;

	template <std::integral T>
	constexpr auto log(char base, T x, T acc = 0) -> char
	{
		return (x == 0) ? acc : log(base, x / base, acc + 1);
	}

	template <std::integral T>
	constexpr auto charlen(char base, T x) -> char
	{
		auto const minus_sign = T(x < 0 ? 1 : 0);
		return (x == 0) ? 1 : log(base, x, minus_sign);
	}

	template <std::integral T>
	constexpr auto maxlen(char base)
	{
		using limits = std::numeric_limits<T>;
		return std::max(charlen(base, limits::min()),
		                charlen(base, limits::max()));
	}
}

#endif
