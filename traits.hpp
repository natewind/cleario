#ifndef CLEARIO_TRAITS_HPP
#define CLEARIO_TRAITS_HPP

#include <limits>      // std::numeric_limits
#include <algorithm>   // std::max
#include <type_traits> // std::enable_if_t, std::is_integral_v, std::is_class_v

namespace clear
{
	template <class T>
	using IsIntegral = std::enable_if_t<std::is_integral_v<T>, bool>;

	// TODO: Uncomment & use or delete
	// template <class T>
	// using IsClass = std::enable_if_t<std::is_class_v<T>, bool>;

	template <class T, IsIntegral<T> = true>
	constexpr auto log(char base, T x, T acc = 0) -> T
	{
		return (x == 0) ? acc : log(base, x / base, acc + 1);
	}

	template <class T, IsIntegral<T> = true>
	constexpr auto charlen(char base, T x) -> T
	{
		auto const minus_sign = T(x < 0 ? 1 : 0);
		return (x == 0) ? 1 : log(base, x, minus_sign);
	}

	template <class T, IsIntegral<T> = true>
	constexpr auto maxlen(char base)
	{
		using limits = std::numeric_limits<T>;
		return std::max(charlen(base, limits::min()),
		                charlen(base, limits::max()));
	}
}

#endif
