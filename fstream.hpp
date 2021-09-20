#ifndef CLEARIO_FSTREAM_HPP
#define CLEARIO_FSTREAM_HPP

#include <array>     // std::array
#include <string>    // std::string
#include <vector>    // std::vector
#include <utility>   // std::move, std::swap
#include <iterator>  // std::next
#include <charconv>  // std::to_chars
#include <algorithm> // std::for_each
#include <cstdio>    // Wrappee

#include "traits.hpp"

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

		void write(bool b)        { std::fputs(b ? "True" : "False", stream); }
		void write(char c)        { std::fputc(c, stream); }
		void write(char const *s) { std::fputs(s, stream); }

		template <class T, IsIntegral<T> = true>
		void write(T x)
		{
			auto buff = std::array<char, maxlen<T>(10)>();
			auto const begin = buff.data();
			auto const end = begin + buff.size();

			auto const size = std::to_chars(begin, end, x).ptr - begin;
			std::fwrite(begin, size, 1, stream);
		}

		template <class InputIt1, class InputIt2>
		void write_sequence(InputIt1 first, InputIt2 last)
		{
			write('[');

			if (first != last)
			{
				write(*first);

				std::for_each(std::next(first), last, [this](auto const &x)
				{
					write(',');
					write(' ');
					write(x);
				});
			}

			write(']');
		}

		template <class T, std::size_t Size>
		void write(T const (&xs)[Size])
		{
			write_sequence(xs, xs + Size);
		}

		template <class T, std::size_t Size>
		void write(std::array<T, Size> const &xs)
		{
			write_sequence(begin(xs), end(xs));
		}

		template <class T>
		void write(std::vector<T> const &xs)
		{
			write_sequence(begin(xs), end(xs));
		}

		template <class T, IsClass<T> = true>
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
