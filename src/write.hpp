#ifndef CLEARIO_WRITE_HPP
#define CLEARIO_WRITE_HPP

#include <algorithm>   // all_of
#include <charconv>    // to_chars
#include <concepts>    // floating_point, integral
#include <cstdint>     // uintptr_t
#include <cstdio>      // EOF, FILE, fputc, fputs, fwrite
#include <iterator>    // begin, end
#include <iterator>    // next
#include <optional>    // optional
#include <ranges>      // ranges::input_range
#include <string_view> // string_view
#include <tuple>       // apply, tuple
#include <utility>     // pair

#include "../nameof/include/nameof.hpp"
#include "types.hpp"

namespace clear::impl
{
	using std::ranges::input_range;

	inline auto write(cfile dest, bool b) -> bool
	{
		return std::fputs(b ? "True" : "False", dest) != EOF;
	}

	inline auto write(cfile dest, char c) -> bool
	{
		return std::fputc(c, dest) == c;
	}

	inline auto write(cfile dest, String auto const &str) -> bool
	{
		auto const view = std::string_view(str);

		return view.size() == 0
		    || std::fwrite(view.data(), view.size(), 1, dest) != 0;
	}

	template <IntBased T>
	auto write(cfile dest, T x) -> bool
	{
		if (std::is_signed_v<typename T::type> && x.value < 0)
		{
		 	if (!write(dest, '-'))
				return false;

			x.value = -x.value;
		}

		if (T::base != 10 && !(write(dest, '0') && write(dest, T::prefix)))
			return false;

		auto buff = typename T::buffer();
		auto const begin = buff.data();
		auto const end = begin + buff.size();

		auto const result = std::to_chars(begin, end, x.value, T::base);
		auto const size = result.ptr - begin;

		return std::fwrite(begin, size, 1, dest) != 0;
	}

	auto write(cfile dest, std::integral auto x) -> bool
	{
		return write(dest, dec {x});
	}

	template <std::floating_point T>
	auto write(cfile dest, T x) -> bool
	{
		auto buff = digit_buffer<T>();
		auto const begin = buff.data();
		auto const end = begin + buff.size();

		auto const size = std::to_chars(begin, end, x).ptr - begin;
		return std::fwrite(begin, size, 1, dest) != 0;
	}

	auto write_type(cfile, void const*) -> bool { return true; }

	template <class T>
	auto write_type(cfile dest, T const*) -> bool
	{
		static constexpr auto type = nameof::nameof_short_type<T>();
		return write(dest, type)
		    && write(dest, ' ');
	}

	auto write(cfile dest, Pointer auto const &ptr) -> bool
	{
		return write(dest, '<')
		    && write_type(dest, ptr)
		    && write(dest, "object at ")
		    && write(dest, hex(reinterpret_cast<std::uintptr_t>(ptr)))
		    && write(dest, '>');
	}

	auto write(cfile dest, SmartPtr auto const &ptr) -> bool
	{
		return write(dest, ptr.get());
	}

	auto write(cfile dest, std::optional<auto> const &x) -> bool
	{
		return x
		     ? write(dest, "Some(") && write(dest, *x) && write(dest, ')')
		     : write(dest, "None");
	}

	template <bool IsMapEntry>
	auto write_item(cfile dest, auto const &x) -> bool
	{
		if constexpr (IsMapEntry)
			return write(dest, x.first)
			    && write(dest, ": ")
			    && write(dest, x.second);

		else return write(dest, x);
	}

	template <bool IsMap = false>
	auto write_list(cfile dest, input_range auto const &xs) -> bool
	{
		auto const first = std::begin(xs);
		auto const last = std::end(xs);

		auto const write_next = [dest](auto const &x)
		{
			return write(dest, ", ")
			    && write_item<IsMap>(dest, x);
		};

		return first == last ||
		(
			write_item<IsMap>(dest, *first) &&
			std::all_of(std::next(first), last, write_next)
		);
	}

	auto write(cfile dest, Sequence auto const &xs) -> bool
	{
		return write(dest, '[')
		    && write_list(dest, xs)
		    && write(dest, ']');
	}

	template <Associative T>
	auto write(cfile dest, T const &xs) -> bool
	{
		return write(dest, '{')
		    && write_list<Map<T>>(dest, xs)
		    && write(dest, '}');
	}

	auto write_items(cfile) -> bool { return true; }

	auto write_items(cfile dest, auto const &x) -> bool
	{
		return write(dest, x);
	}

	auto write_items(cfile dest, auto const &x, auto const&... xs) -> bool
	{
		return write(dest, x)
		    && write(dest, ", ")
		    && write_items(dest, xs...);
	}

	template <class... Ts>
	auto write(cfile dest, std::tuple<Ts...> const &tup) -> bool
	{
		auto const writer = [dest](auto const &... xs)
		{
			return write_items(dest, xs...);
		};

		return write(dest, '(')
		    && std::apply(writer, tup)
		    && write(dest, ')');
	}
}

#endif
