#ifndef CLEARIO_FSTREAM_HPP
#define CLEARIO_FSTREAM_HPP

#include <set>           // std::set
#include <array>         // std::array
#include <vector>        // std::vector
#include <cstdint>       // std::uintptr_t
#include <utility>       // std::move, std::swap, std::pair
#include <iterator>      // std::next
#include <charconv>      // std::to_chars
#include <algorithm>     // std::for_each
#include <string_view>   // std::string_view
#include <unordered_map> // std::unordered_map
#include <cstdio>        // Wrappee

#include "traits.hpp"

// TODO: Overloads + references!
// TODO: IsClass -> IsNotFundamental? (IsCustom?)
//       (To allow for user-defined enums and unions)

namespace clear
{
	class fstream
	{
		std::FILE *stream = nullptr;

	public:
		explicit constexpr fstream(std::FILE *f) : stream(f) {}
		constexpr auto unsafe() { return stream; }

		fstream(fstream const&) = delete;
		auto operator=(fstream const&) = delete;

		fstream(fstream &&other) { (*this) = std::move(other); }

		auto operator=(fstream &&other) -> fstream&
		{
			std::swap(stream, other.stream);
			return *this;
		}

		// TODO: Add quotation marks to strings inside containers?

		void write(bool b)        { std::fputs(b ? "True" : "False", stream); }
		void write(char c)        { std::fputc(c, stream); }
		void write(char const *s) { std::fputs(s, stream); }

		void write(std::string_view str)
		{
			std::fwrite(str.data(), str.size(), 1, stream);
		}

		// TODO: Combine with write(string_view) without a linking error
		void write(std::string const &str) { std::fputs(str.c_str(), stream); }

		template <class T, impl::IsIntegral<T> = true>
		void write(T x)
		{
			auto buff = std::array<char, impl::maxlen<T>(10)>();
			auto const begin = buff.data();
			auto const end = begin + buff.size();

			auto const size = std::to_chars(begin, end, x).ptr - begin;
			std::fwrite(begin, size, 1, stream);
		}

		template <class T>
		void write(T *ptr)
		{
			using IntPtr = std::uintptr_t;
			// TODO: Add to the array and write everyting at once?
			write("<object at 0x");

			// TODO: Get rid of the code duplication! (write(int))
			auto buff = std::array<char, impl::maxlen<IntPtr>(16)>();
			auto const begin = buff.data();
			auto const end = begin + buff.size();

			auto const addr = reinterpret_cast<IntPtr>(ptr);
			auto const size = std::to_chars(begin, end, addr, 16).ptr - begin;
			std::fwrite(begin, size, 1, stream);

			write('>');
		}

		template <class T>
		void write_item(T const &x) { write(x); }

		template <class Key, class Value>
		void write_item(std::pair<Key, Value> const &kv)
		{
			write(kv.first);
			write(": ");
			write(kv.second);
		}

		template <class InputIt1, class InputIt2>
		void write_sequence(InputIt1 first, InputIt2 last)
		{
			if (first == last)
				return;

			write_item(*first);

			std::for_each(std::next(first), last, [this](auto const &x)
			{
				write(',');
				write(' ');
				write_item(x);
			});
		}

		template <class InputIt1, class InputIt2>
		void write_list(InputIt1 first, InputIt2 last)
		{
			write('[');
			write_sequence(first, last);
			write(']');
		}

		template <class InputIt1, class InputIt2>
		void write_set(InputIt1 first, InputIt2 last)
		{
			write('{');
			write_sequence(first, last);
			write('}');
		}

		template <class T, std::size_t Size>
		void write(T const (&xs)[Size]) { write_list(xs, xs + Size); }

		template <class T, std::size_t Size>
		void write(std::array<T, Size> const &xs)
		{
			write_list(begin(xs), end(xs));
		}

		template <class T>
		void write(std::vector<T> const &xs)
		{
			write_list(begin(xs), end(xs));
		}

		template <class T>
		void write(std::set<T> const &xs) { write_set(begin(xs), end(xs)); }

		template <class Key, class Value>
		void write(std::unordered_map<Key, Value> const &xs)
		{
			write_set(begin(xs), end(xs));
		}

		template <class T, impl::IsClass<T> = true>
		void write(const T&);

		void print() { write('\n'); }

		template <class T, class... Ts>
		void print(T const &x, Ts const&... xs)
		{
			write(x);

			if constexpr (sizeof...(Ts) > 0)
				write(' ');

			print(xs...);
		}
	};
}

#endif
