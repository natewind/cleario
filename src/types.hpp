#ifndef CLEARIO_TRAITS_HPP
#define CLEARIO_TRAITS_HPP

#include <algorithm>     // max
#include <array>         // array
#include <concepts>      // convertible_to, floating_point, integral
#include <cstddef>       // size_t
#include <deque>         // deque
#include <forward_list>  // forward_list
#include <limits>        // numeric_limits
#include <list>          // list
#include <map>           // map, multimap
#include <memory>        // shared_ptr, unique_ptr
#include <set>           // multiset, set
#include <type_traits>   // false_type, is_pointer_v, true_type
#include <unordered_map> // unordered_map, unordered_multimap
#include <unordered_set> // unordered_multiset, unordered_set
#include <vector>        // vector

#include <climits>

namespace clear::impl
{
	using cfile = std::FILE*;

	template <class T>
	concept String = std::convertible_to<T, std::string_view>;

	template <class T>
	concept Pointer = std::is_pointer_v<T> && !String<T>;

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
	concept Array = is_array<T>::value && !String<T>;

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
	concept Set = Specialization<T, std::set>
	           || Specialization<T, std::multiset>
	           || Specialization<T, std::unordered_set>
	           || Specialization<T, std::unordered_multiset>;

	template <class T>
	concept Map = Specialization<T, std::map>
	           || Specialization<T, std::multimap>
	           || Specialization<T, std::unordered_map>
	           || Specialization<T, std::unordered_multimap>;

	template <class T>
	concept Associative = Set<T> || Map<T>;

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

	template <std::floating_point T>
	constexpr auto maxlen()
	{
		using limits = std::numeric_limits<T>;
		return 4 + limits::max_digits10
		     + std::max(2, log(10, limits::max_exponent10));
	}

	template <class T>
	concept Numeric = std::integral<T> || std::floating_point<T>;

	template <Numeric T, int... Base>
	using digit_buffer = std::array<char, maxlen<T>(Base...)>;

	template <std::integral T, int B, char P = 0>
	struct int_based
	{
		using type = T;
		static constexpr auto base = B;
		static constexpr auto prefix = P;

		type value;
		constexpr explicit int_based(type x) : value(x) {}
	};

	template <class>
	struct is_int_based : std::false_type {};

	template <class T, int Base, char Prefix>
	struct is_int_based<int_based<T, Base, Prefix>> : std::true_type {};

	template <class T>
	concept IntBased = is_int_based<T>::value;
}

namespace clear
{
	template <std::integral T>
	using bin = impl::int_based<T, 2, 'b'>;

	template <std::integral T>
	using oct = impl::int_based<T, 8, 'o'>;

	template <std::integral T>
	using dec = impl::int_based<T, 10>;

	template <std::integral T>
	using hex = impl::int_based<T, 16, 'x'>;
}

#endif
