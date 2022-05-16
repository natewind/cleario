#ifndef CLEARIO_IO_HPP
#define CLEARIO_IO_HPP

#include <algorithm>   // std::for_each
#include <array>       // std::array
#include <charconv>    // std::to_chars
#include <concepts>    // std::integral
#include <cstdint>     // std::uintptr_t
#include <iterator>    // std::next
#include <memory>      // std::unique_ptr, std::shared_ptr
#include <optional>    // std::optional
#include <ranges>      // std::ranges::input_range
#include <string_view> // std::string_view
#include <utility>     // std::move, std::swap, std::pair
#include <cstdio>      // Wrappee

#include "../nameof/include/nameof.hpp"

#include "traits.hpp"

// TODO: Overloads + references!
// TODO: IsClass -> IsNotFundamental? (IsCustom?)
//       (To allow for user-defined enums and unions)

namespace clear
{
	class io
	{
		std::FILE *handle = nullptr;

	public:
		explicit constexpr io(std::FILE *f) : handle(f) {}
		constexpr auto unsafe() { return handle; }

		io(io const&) = delete;
		auto operator=(io const&) = delete;

		io(io &&other) { (*this) = std::move(other); }

		auto operator=(io &&other) -> io&
		{
			std::swap(handle, other.handle);
			return *this;
		}

		// TODO: Add quotation marks to strings inside containers?

		void write(bool b)        { std::fputs(b ? "True" : "False", handle); }
		void write(char c)        { std::fputc(c, handle); }
		void write(char const *s) { std::fputs(s, handle); }

		void write(std::string_view str)
		{
			std::fwrite(str.data(), str.size(), 1, handle);
		}

		// TODO: Combine with write(string_view) without a linking error
		void write(std::string const &str) { std::fputs(str.c_str(), handle); }

		template <int Base, std::integral T>
		void write_base(T x)
		{
			auto buff = std::array<char, impl::maxlen<T>(Base)>();
			auto const begin = buff.data();
			auto const end = begin + buff.size();

			auto const size = std::to_chars(begin, end, x, Base).ptr - begin;
			std::fwrite(begin, size, 1, handle);
		}

		void write(std::integral auto x) { write_base<10>(x); }

		void write_type(void const*) {}

		template <class T>
		void write_type(T const*)
		{
			constexpr auto type = nameof::nameof_short_type<T>();
			write(type);
			write(' ');
		}

		void write(impl::Pointer auto ptr)
		{
			write('<');
			write_type(ptr);
			write("object at 0x");
			write_base<16>(reinterpret_cast<std::uintptr_t>(ptr));
			write('>');
		}

		template <class T>
		void write(std::unique_ptr<T> const &ptr) { write(ptr.get()); }

		template <class T>
		void write(std::shared_ptr<T> const &ptr) { write(ptr.get()); }

		template <class T>
		void write(std::optional<T> const &x)
		{
			x ? write(*x) : write("None");
		}

		void write_item(auto const &x) { write(x); }

		template <class Key, class Value>
		void write_item(std::pair<Key, Value> const &kv)
		{
			write(kv.first);
			write(": ");
			write(kv.second);
		}

		void write_sequence(std::ranges::input_range auto const &xs)
		{
			auto const first = std::begin(xs);
			auto const last = std::end(xs);

			if (first == last)
				return;

			write_item(*first);

			std::for_each(std::next(first), last, [this](auto const &x)
			{
				write(", ");
				write_item(x);
			});
		}

		void write_list(std::ranges::input_range auto const &xs)
		{
			write('[');
			write_sequence(xs);
			write(']');
		}

		void write_set(std::ranges::input_range auto const &xs)
		{
			write('{');
			write_sequence(xs);
			write('}');
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
		void write(auto const (&xs)[Size]) { write_list(xs); }

		template <std::size_t Size>
		void write(std::array<auto, Size> const &xs) { write_list(xs); }

		template <impl::Class T>
		void write(T const &xs)
		{
			if constexpr (impl::Sequence<T>)
				write_list(xs);

			else
			{
				static_assert(impl::Associative<T>,
				              "write() is not implemented for this type");
				write_set(xs);
			}
		}

		void print() { write('\n'); }

		void print(auto const &x, auto const&... xs)
		{
			write(x);

			if constexpr (sizeof...(xs) > 0)
				write(' ');

			print(xs...);
		}
	};
}

#endif
