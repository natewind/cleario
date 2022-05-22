#ifndef CLEARIO_WRITE_HPP
#define CLEARIO_WRITE_HPP

#include <algorithm>   // std::for_each
#include <array>       // std::array
#include <charconv>    // std::to_chars
#include <concepts>    // std::integral
#include <cstdint>     // std::uintptr_t
#include <cstdio>      // std::FILE, std::fputc, std::fputs, std::fwrite
#include <iterator>    // std::next
#include <memory>      // std::shared_ptr, std::unique_ptr
#include <optional>    // std::optional
#include <ranges>      // std::ranges::input_range
#include <string_view> // std::string_view
#include <utility>     // std::pair

#include "../nameof/include/nameof.hpp"

#include "traits.hpp"

// TODO: Overloads + references!
// TODO: IsClass -> IsNotFundamental? (IsCustom?)
//       (To allow for user-defined enums and unions)

// TODO: Move some of the write_* functions to the interface?

namespace clear::impl
{
	// TODO: Add quotation marks to strings inside containers?

	void write(std::FILE *dest, bool b)
	{
		std::fputs(b ? "True" : "False", dest);
	}

	void write(std::FILE *dest, char c)        { std::fputc(c, dest); }
	void write(std::FILE *dest, char const *s) { std::fputs(s, dest); }

	void write(std::FILE *dest, std::string_view str)
	{
		std::fwrite(str.data(), str.size(), 1, dest);
	}

	// TODO: Combine with write(string_view) without a linking error
	void write(std::FILE *dest, std::string const &str)
	{
		std::fputs(str.c_str(), dest);
	}

	template <int Base, std::integral T>
	void write_base(std::FILE *dest, T x)
	{
		auto buff = std::array<char, impl::maxlen<T>(Base)>();
		auto const begin = buff.data();
		auto const end = begin + buff.size();

		auto const size = std::to_chars(begin, end, x, Base).ptr - begin;
		std::fwrite(begin, size, 1, dest);
	}

	void write(std::FILE *dest, std::integral auto x)
	{
		write_base<10>(dest, x);
	}

	void write_type(std::FILE*, void const*) {}

	template <class T>
	void write_type(std::FILE *dest, T const*)
	{
		constexpr auto type = nameof::nameof_short_type<T>();
		write(dest, type);
		write(dest, ' ');
	}

	void write(std::FILE *dest, impl::Pointer auto ptr)
	{
		write(dest, '<');
		write_type(dest, ptr);
		write(dest, "object at 0x");
		write_base<16>(dest, reinterpret_cast<std::uintptr_t>(ptr));
		write(dest, '>');
	}

	template <class T>
	void write(std::FILE *dest, std::unique_ptr<T> const &ptr)
	{
		write(dest, ptr.get());
	}

	//====================================

	template <class T>
	void write(std::FILE *dest, std::shared_ptr<T> const &ptr) { write(dest, ptr.get()); }

	template <class T>
	void write(std::FILE *dest, std::optional<T> const &x)
	{
		x ? write(dest, *x) : write(dest, "None");
	}

	void write_item(std::FILE *dest, auto const &x) { write(dest, x); }

	template <class Key, class Value>
	void write_item(std::FILE *dest, std::pair<Key, Value> const &kv)
	{
		write(dest, kv.first);
		write(dest, ": ");
		write(dest, kv.second);
	}

	void write_sequence(std::FILE *dest, std::ranges::input_range auto const &xs)
	{
		auto const first = std::begin(xs);
		auto const last = std::end(xs);

		if (first == last)
			return;

		write_item(dest, *first);

		std::for_each(std::next(first), last, [dest](auto const &x)
		{
			write(dest, ", ");
			write_item(dest, x);
		});
	}

	void write_list(std::FILE *dest, std::ranges::input_range auto const &xs)
	{
		write(dest, '[');
		write_sequence(dest, xs);
		write(dest, ']');
	}

	void write_set(std::FILE *dest, std::ranges::input_range auto const &xs)
	{
		write(dest, '{');
		write_sequence(dest, xs);
		write(dest, '}');
	}

	// TODO: Reorganize write() overloads when GCC fixes its bug
	//
	//       Currently: write(std::integral) collides with write(auto),
	//                  so I added impl::Class instead of the latter,
	//                  and that collides with e. g. impl::Sequence,
	//                  so I moved them inside the impl::Class overload,
	//                  and the array overload stays outside (not a class).
	//
	//       Desired: When GCC fixes the bug, and std::integral is more
	//                specific than auto, move other concepts outside
	//                of the impl::Class overload and replace impl::Class
	//                with auto. Figure out how to add both array overloads
	//                to impl::Sequence.

	template <std::size_t Size>
	void write(std::FILE *dest, auto const (&xs)[Size]) { write_list(dest, xs); }

	template <std::size_t Size>
	void write(std::FILE *dest, std::array<auto, Size> const &xs) { write_list(dest, xs); }

	template <impl::Class T>
	void write(std::FILE *dest, T const &xs)
	{
		if constexpr (impl::Sequence<T>)
			write_list(dest, xs);

		else
		{
			static_assert(impl::Associative<T>,
			              "write() is not implemented for this type");
			write_set(dest, xs);
		}
	}
}

#endif
