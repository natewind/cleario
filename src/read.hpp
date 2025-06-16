#ifndef CLEARIO_READ_HPP
#define CLEARIO_READ_HPP

#include <algorithm>   // min, ranges::all_of
#include <cctype>      // isspace, tolower
#include <charconv>    // from_chars
#include <concepts>    // integral
#include <cstdio>      // EOF, fgetc, ungetc
#include <optional>    // make_optional, nullopt, optional
#include <string_view> // string_view

#include "types.hpp"

namespace clear::impl
{
	auto expect(cfile src, char expected) -> bool
	{
		auto const c = std::fgetc(src);

		if (c == expected)
			return true;

		std::ungetc(c, src);
		return false;
	}

	auto expect(cfile src, std::string_view expected) -> bool
	{
		return std::ranges::all_of
		(
			expected,
			[src](char c) { return expect(src, c); }
		);
	}

	void skip_ws(cfile src)
	{
		auto c = char();

		do c = std::fgetc(src);
		while (std::isspace(c));

		std::ungetc(c, src);
	}

	auto skip_zeros(cfile src) -> bool
	{
		auto c = char();
		auto any = false;

		if (c = std::fgetc(src); c == '0')
		{
			any = true;
			do c = std::fgetc(src);
			while (c == '0');
		}

		std::ungetc(c, src);
		return any;
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

	template <int Base, class InputIt>
	auto read_digits(cfile src, InputIt dest, InputIt end) -> InputIt
	{
		auto digit = char();

		while (is_digit<Base>(digit = std::fgetc(src)) && dest != end)
			*dest++ = digit;

		std::ungetc(digit, src);
		return dest;
	}

	template <IntBased T>
	auto read(cfile src) -> std::optional<typename T::type>
	{
		auto buff = T::buffer();
		auto it = buff.begin();

		skip_ws(src);

		if (T::is_signed && expect(src, '-'))
			*it++ = '-';

		if (T::base != 10 && !(expect(src, '0') && expect(src, T::prefix)))
			return {};

		auto const any_zero = skip_zeros(src);
		it = read_digits<T::base>(src, it, buff.end());

		if (it == buff.end())
			return {};

		auto x = typename T::type(0);
		std::from_chars(buff.data(), it, x, T::base);

		return x != 0 || any_zero
		     ? std::make_optional(x)
		     : std::nullopt;
	}

	template <std::integral T>
	auto read(cfile src) -> std::optional<T>
	{
		auto const x = read<dec<T>>(src);
		return x ? std::make_optional(*x) : std::nullopt;
	}

	template <>
	auto read<char>(cfile src) -> std::optional<char>
	{
		auto const c = std::fgetc(src);
		return (c == EOF) ? std::nullopt : std::make_optional(c);
	}

	template <>
	auto read<bool>(cfile src) -> std::optional<bool>
	{
		skip_ws(src);

		if (expect(src, 'F'))
		{
			return expect(src, "alse")
			     ? std::make_optional<bool>(false)
			     : std::nullopt;
		}

		else
		{
			return expect(src, "True")
			     ? std::make_optional<bool>(true)
			     : std::nullopt;
		}
	}
}

#endif
