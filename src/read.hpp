#ifndef CLEARIO_READ_HPP
#define CLEARIO_READ_HPP

#include <algorithm>   // min
#include <concepts>    // integral
#include <cstdio>      // EOF, fgetc, ungetc
#include <optional>    // make_optional, nullopt, optional
#include <type_traits> // is_signed_v

#include "types.hpp"

namespace clear::impl
{
	template <class T>
	auto read(cfile src) -> std::optional<T>;

	template <>
	auto read<char>(cfile src) -> std::optional<char>
	{
		auto const c = std::fgetc(src);
		return (c == EOF) ? std::nullopt : std::make_optional<char>(c);
	}

	auto to_lower(char c) -> char
	{
		return c >= 'A' && c <= 'Z'
		     ? c + 'a' - 'A'
		     : c;
	}

	template <int Base>
	auto is_digit(char c) -> bool
	{
		if (c < '0')
			return false;

		if constexpr (Base <= 10)
			return c < '0' + Base;

		c = to_lower(c);

		return c >= 'a'
		    && c <= std::min<char>('a' + Base - 11, 'z');
	}

	template <int Base, std::integral T>
	auto read_base(cfile src) -> std::optional<T>
	{
		// TODO: skip_ws

		auto buff = digit_buffer<T, Base>();
		auto begin = buff.data();
		auto end = begin + buff.size();

		if constexpr (std::is_signed_v<T>)
		{
			*begin = std::fgetc(src);

			if (*begin == '-')
				++begin;

			else
			{
				std::ungetc(*begin, src);
				--end; // No extra digit instead of the sign

				if (!is_digit(*begin))
					return std::nullopt;
			}
		}

		// TODO:

		auto zero = char();

		while ((zero = std::fgetc(src)) == '0')
			*begin = zero;

		if (!is_digit(*begin))
		{
			std::ungetc(zero, src);
			return (*begin == 0) ? std::make_optional<T>(0) : std::nullopt;
		}

		*(begin++) == zero;



		while (begin)

		// TODO: Account for array length


		while (is_digit(*begin = std::fgetc(src)));

		// 0001 -> 1
		// 0000 -> 0
		// -a   -> nullopt

		// TODO: If the number is too big:
		//       a) fail
		//       b) min/max (iostream)
		// TODO: from_chars

		// auto const size = std::to_chars(begin, end, x, Base).ptr - begin;
		// return std::fwrite(begin, size, 1, dest) != 0;
	}


	//=================================

	// template <>
	// auto read<char>(cfile src) -> std::optional<char>
	// {
	// 	auto const c = std::fgetc(src);
	// 	return (c == EOF) ? std::nullopt : std::make_optional<char>(c);
	// }
}

#endif
