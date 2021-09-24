#ifndef CLEARIO_FSTREAM_HPP
#define CLEARIO_FSTREAM_HPP

#include <set>           // std::set, std::multiset
#include <map>           // std::map, std::multimap
#include <list>          // std::list
#include <array>         // std::array
#include <deque>         // std::deque
#include <vector>        // std::vector
#include <memory>        // std::unique_ptr, std::shared_ptr
#include <cstdint>       // std::uintptr_t
#include <utility>       // std::move, std::swap, std::pair
#include <concepts>      // std::integral
#include <iterator>      // std::next
#include <optional>      // std::optional
#include <charconv>      // std::to_chars
#include <algorithm>     // std::for_each
#include <string_view>   // std::string_view
#include <forward_list>  // std::forward_list
#include <unordered_set> // std::unordered_set, std::unordered_multiset
#include <unordered_map> // std::unordered_map, std::unordered_multimap
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

		template <char Base, std::integral T>
		void write_base(T x)
		{
			auto buff = std::array<char, impl::maxlen<T>(Base)>();
			auto const begin = buff.data();
			auto const end = begin + buff.size();

			auto const size = std::to_chars(begin, end, x, Base).ptr - begin;
			std::fwrite(begin, size, 1, stream);
		}

		void write(std::integral auto x) { write_base<10>(x); }

		template <class T>
		void write(T *ptr)
		{
			write("<object at 0x");
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
		void write(std::deque<T> const &xs)
		{
			write_list(begin(xs), end(xs));
		}

		template <class T>
		void write(std::forward_list<T> const &xs)
		{
			write_list(begin(xs), end(xs));
		}

		template <class T>
		void write(std::list<T> const &xs)
		{
			write_list(begin(xs), end(xs));
		}

		template <class T>
		void write(std::set<T> const &xs) { write_set(begin(xs), end(xs)); }

		template <class T>
		void write(std::multiset<T> const &xs)
		{
			write_set(begin(xs), end(xs));
		}

		template <class T>
		void write(std::unordered_set<T> const &xs)
		{
			write_set(begin(xs), end(xs));
		}

		template <class T>
		void write(std::unordered_multiset<T> const &xs)
		{
			write_set(begin(xs), end(xs));
		}

		template <class Key, class Value>
		void write(std::map<Key, Value> const &xs)
		{
			write_set(begin(xs), end(xs));
		}

		template <class Key, class Value>
		void write(std::multimap<Key, Value> const &xs)
		{
			write_set(begin(xs), end(xs));
		}

		template <class Key, class Value>
		void write(std::unordered_map<Key, Value> const &xs)
		{
			write_set(begin(xs), end(xs));
		}

		template <class Key, class Value>
		void write(std::unordered_multimap<Key, Value> const &xs)
		{
			write_set(begin(xs), end(xs));
		}

		void write(impl::IsClass auto const &);

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
