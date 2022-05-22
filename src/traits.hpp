#ifndef CLEARIO_TRAITS_HPP
#define CLEARIO_TRAITS_HPP

#include <algorithm>     // max
#include <array>         // array
#include <concepts>      // integral
#include <cstddef>       // size_t
#include <deque>         // deque
#include <forward_list>  // forward_list
#include <limits>        // numeric_limits
#include <list>          // list
#include <map>           // map, multimap
#include <set>           // multiset, set
#include <type_traits>   // false_type, is_class_v, is_pointer_v, true_type
#include <unordered_map> // unordered_map, unordered_multimap
#include <unordered_set> // unordered_multiset, unordered_set
#include <vector>        // vector

namespace clear::impl
{
	template <class T>
	concept Pointer = std::is_pointer_v<T>;

	template <class T>
	concept Class = std::is_class_v<T>;

	template <class, template <class...> class>
	struct is_specialization : std::false_type {};

	template <template <class...> class Generic, class... Ts>
	struct is_specialization<Generic<Ts...>, Generic> : std::true_type {};

	template <class Specific, template <class...> class Generic>
	concept Specialization = is_specialization<Specific, Generic>::value;

	template <class>
	struct is_array : std::false_type {};

	template <class T, std::size_t Size>
	struct is_array<std::array<T, Size>> : std::true_type {};

	template <class T, std::size_t Size>
	struct is_array<T[Size]> : std::true_type {};

	template <class T>
	concept Array = is_array<T>::value;

	template <class T>
	concept SmartPtr = Specialization<T, std::unique_ptr>
	                || Specialization<T, std::shared_ptr>;

	template <class T>
	concept Sequence = Array<T>
	                || Specialization<T, std::vector>
	                || Specialization<T, std::deque>
	                || Specialization<T, std::forward_list>
	                || Specialization<T, std::list>;

	template <class T>
	concept Associative = Specialization<T, std::set>
	                   || Specialization<T, std::multiset>
	                   || Specialization<T, std::unordered_set>
	                   || Specialization<T, std::unordered_multiset>
	                   || Specialization<T, std::map>
	                   || Specialization<T, std::multimap>
	                   || Specialization<T, std::unordered_map>
	                   || Specialization<T, std::unordered_multimap>;

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
