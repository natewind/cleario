#ifndef CLEARIO_WRITE_HPP
#define CLEARIO_WRITE_HPP

#include <algorithm>   // for_each
#include <array>       // array
#include <charconv>    // to_chars
#include <concepts>    // integral
#include <cstdint>     // uintptr_t
#include <cstdio>      // EOF, FILE, fputc, fputs, fwrite
#include <iterator>    // begin, end
#include <iterator>    // next
#include <optional>    // optional
#include <ranges>      // ranges::input_range
#include <string_view> // string_view
#include <utility>     // pair

#include "../nameof/include/nameof.hpp"
#include "traits.hpp"

namespace clear::impl
{
	using file = std::FILE*;
	using std::ranges::input_range;

	inline auto write(file dest, bool b) -> bool
	{
		return std::fputs(b ? "True" : "False", dest) != EOF;
	}

	inline auto write(file dest, char c) -> bool
	{
		return std::fputc(c, dest) == c;
	}

	inline auto write(file dest, String auto const &str) -> bool
	{
		auto const view = std::string_view(str);
		return std::fwrite(view.data(), view.size(), 1, dest) != 0;
	}

	template <int Base, std::integral T>
	auto write_base(file dest, T x) -> bool
	{
		auto buff = std::array<char, maxlen<T>(Base)>();
		auto const begin = buff.data();
		auto const end = begin + buff.size();

		auto const size = std::to_chars(begin, end, x, Base).ptr - begin;
		return std::fwrite(begin, size, 1, dest) != 0;
	}

	auto write(file dest, std::integral auto x) -> bool
	{
		return write_base<10>(dest, x);
	}

	auto write_type(file, void const*) -> bool { return true; }

	template <class T>
	auto write_type(file dest, T const*) -> bool
	{
		constexpr auto type = nameof::nameof_short_type<T>();
		return write(dest, type)
		    && write(dest, ' ');
	}

	auto write(file dest, Pointer auto const &ptr) -> bool
	{
		return write(dest, '<')
		    && write_type(dest, ptr)
		    && write(dest, "object at 0x")
		    && write_base<16>(dest, reinterpret_cast<std::uintptr_t>(ptr))
		    && write(dest, '>');
	}

	auto write(file dest, SmartPtr auto const &ptr) -> bool
	{
		return write(dest, ptr.get());
	}

	auto write(file dest, std::optional<auto> const &x) -> bool
	{
		return x
		     ? write(dest, "Some(") && write(dest, *x) && write(dest, ')')
		     : write(dest, "None");
	}

	template <bool IsMapEntry>
	auto write_item(file dest, auto const &x) -> bool
	{
		if constexpr (IsMapEntry)
			return write(dest, x.first)
			    && write(dest, ": ")
			    && write(dest, x.second);

		else return write(dest, x);
	}

	template <bool IsMap = false>
	auto write_sequence(file dest, input_range auto const &xs) -> bool
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

	auto write(file dest, Sequence auto const &xs) -> bool
	{
		return write(dest, '[')
		    && write_sequence(dest, xs)
		    && write(dest, ']');
	}

	template <Associative T>
	auto write(file dest, T const &xs) -> bool
	{
		return write(dest, '{')
		    && write_sequence<Map<T>>(dest, xs)
		    && write(dest, '}');
	}
}

#endif
