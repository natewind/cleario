#ifndef CLEARIO_READ_HPP
#define CLEARIO_READ_HPP

#include <algorithm>   // min
#include <cctype>      // isspace, tolower
#include <charconv>    // from_chars
#include <concepts>    // integral
#include <cstdio>      // EOF, fgetc, ungetc
#include <optional>    // make_optional, nullopt, optional
#include <type_traits> // is_signed_v

#include "types.hpp"

namespace clear::impl
{
	void skip_ws(cfile src)
	{
		auto c = char();

		do c = std::fgetc(src);
		while (std::isspace(c));

		std::ungetc(c, src);
	}

	template <int Base>
	auto is_digit(char c) -> bool
	{
		if (c < '0')
			return false;

		if (c <= '9')
			return c < '0' + Base;

		c = std::tolower(c);

		return c >= 'a'
		    && c <= std::min<char>('a' + Base - 11, 'z');
	}

	// template <int Base>
	// auto skip_zeros(cfile src) -> char
	// {
	// 	auto any_zero = false;
	// 	auto c = char();

	// 	if ((c = std::fgetc(src)) == '0')
	// 	{
	// 		any_zero = true;
	// 		while ((c = std::fgetc(src)) == '0');
	// 	}

	// 	if (is_digit<Base>(c))
	// 		return c;

	// 	std::ungetc(c, src);
	// 	return any_zero ? '0' : -1;
	// }

	// template <int Base>
	// auto skip_zeros1(cfile src) -> char
	// {
	// 	if ((c = std::fgetc(src)) == '0')


	// 	auto any_zero = false;
	// 	auto c = char();

	// 	if (c = std::fgetc(src); c == '0')
	// 	{
	// 		any_zero = true;
	// 		do c = std::fgetc(src);
	// 		while (c == '0');
	// 	}

	// 	if (is_digit<Base>(c))
	// 		return c;

	// 	std::ungetc(c, src);
	// 	return any_zero ? '0' : -1;
	// }

	template <int Base, std::integral T>
	auto read_base(cfile src) -> std::optional<T>
	{
		skip_ws(src);

		auto buff = digit_buffer<T, Base>();
		auto it = buff.data();
		auto end = it + buff.size();

		if constexpr (std::is_signed_v<T>)
		{
			*it = std::fgetc(src);

			if (*it == '-')
				++it;

			else
			{
				std::ungetc(*it, src);

				if (!is_digit<Base>(*it))
					return {};
			}
		}

		auto any_zero = false;

		if (*it = std::fgetc(src); *it == '0')
		{
			any_zero = true;
			do *it = std::fgetc(src);
			while (*it == '0');
		}

		if (!is_digit<Base>(*it))
		{
			std::ungetc(*it, src);
			return any_zero ? std::make_optional<T>(0) : std::nullopt;
		}

		while (true)
		{
			auto const next = std::fgetc(src);

			if (!is_digit<Base>(next))
			{
				std::ungetc(next, src);

				auto x = T(0);
				std::from_chars(buff.data(), end, x, Base);

				return x == 0 ? std::nullopt : std::make_optional<T>(x);
			}

			if (++it == end)
			{
				std::ungetc(next, src);
				return {};
			}

			*it = next;
		}
	}

	template <std::integral T>
	auto read(cfile src) -> std::optional<T> { return read_base<10, T>(src); }

	template <>
	auto read<char>(cfile src) -> std::optional<char>
	{
		auto const c = std::fgetc(src);
		return (c == EOF) ? std::nullopt : std::make_optional<char>(c);
	}
}

#endif
