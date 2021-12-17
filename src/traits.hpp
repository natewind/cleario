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

	// BEGIN TODO: New names to includes & comments
	template <class, template <class...> class>
	struct is_specialization : std::false_type {};

	template <template<class...> class Generic, class... Ts>
	struct is_specialization<Generic<Ts...>, Generic> : std::true_type {};

	template <class Specific, template <class...> class Generic>
	concept Specialization = is_specialization<Specific, Generic>::value;

	template <class T>
	concept Associative = Specialization<T, std::set>
	                   || Specialization<T, std::multiset>
	                   || Specialization<T, std::unordered_set>
	                   || Specialization<T, std::unordered_multiset>
	                   || Specialization<T, std::map>
	                   || Specialization<T, std::multimap>
	                   || Specialization<T, std::unordered_map>
	                   || Specialization<T, std::unordered_multimap>;
	// END TODO

	constexpr auto log(int base, std::integral auto x, int acc = 0) -> int
	{
		return (x == 0) ? acc : log(base, x / base, acc + 1);
	}

	constexpr auto charlen(int base, std::integral auto x)
	{
		auto const minus_sign = int(x < 0);
		return (x == 0) ? 1 : log(base, x, minus_sign);
	}

	template <std::integral T>
	constexpr auto maxlen(int base)
	{
		using limits = std::numeric_limits<T>;
		return std::max(charlen(base, limits::min()),
		                charlen(base, limits::max()));
	}
}

#endif
