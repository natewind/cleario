#ifndef CLEARIO_WRITE_HPP
#define CLEARIO_WRITE_HPP

#include <algorithm>   // for_each
#include <array>       // array
#include <charconv>    // to_chars
#include <concepts>    // integral
#include <cstdint>     // uintptr_t
#include <cstdio>      // FILE, fputc, fputs, fwrite
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

	inline void write(file dest, bool b)
	{
		std::fputs(b ? "True" : "False", dest);
	}

	inline void write(file dest, char c) { std::fputc(c, dest); }

	inline void write(file dest, String auto const &str)
	{
		auto const view = std::string_view(str);
		std::fwrite(view.data(), view.size(), 1, dest);
	}

	template <int Base, std::integral T>
	void write_base(file dest, T x)
	{
		auto buff = std::array<char, maxlen<T>(Base)>();
		auto const begin = buff.data();
		auto const end = begin + buff.size();

		auto const size = std::to_chars(begin, end, x, Base).ptr - begin;
		std::fwrite(begin, size, 1, dest);
	}

	void write(file dest, std::integral auto x) { write_base<10>(dest, x); }

	void write_type(file, void const*) {}

	template <class T>
	void write_type(file dest, T const*)
	{
		constexpr auto type = nameof::nameof_short_type<T>();
		write(dest, type);
		write(dest, ' ');
	}

	void write(file dest, Pointer auto const &ptr)
	{
		write(dest, '<');
		write_type(dest, ptr);
		write(dest, "object at 0x");
		write_base<16>(dest, reinterpret_cast<std::uintptr_t>(ptr));
		write(dest, '>');
	}

	void write(file dest, SmartPtr auto const &ptr) { write(dest, ptr.get()); }

	template <class T>
	void write(file dest, std::optional<T> const &x)
	{
		if (x)
		{
			write(dest, "Some(");
			write(dest, *x);
			write(dest, ')');
		}

		else write(dest, "None");
	}

	template <bool IsMapEntry>
	void write_item(file dest, auto const &x)
	{
		if constexpr (IsMapEntry)
		{
			write(dest, x.first);
			write(dest, ": ");
			write(dest, x.second);
		}

		else write(dest, x);
	}

	template <bool IsMap = false>
	void write_sequence(file dest, std::ranges::input_range auto const &xs)
	{
		auto const first = std::begin(xs);
		auto const last = std::end(xs);

		if (first == last)
			return;

		write_item<IsMap>(dest, *first);

		std::for_each(std::next(first), last, [dest](auto const &x)
		{
			write(dest, ", ");
			write_item<IsMap>(dest, x);
		});
	}

	void write(file dest, Sequence auto const &xs)
	{
		write(dest, '[');
		write_sequence(dest, xs);
		write(dest, ']');
	}

	template <Associative T>
	void write(file dest, T const &xs)
	{
		write(dest, '{');
		write_sequence<Map<T>>(dest, xs);
		write(dest, '}');
	}
}

#endif
