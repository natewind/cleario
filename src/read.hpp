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
	auto expect(cfile src, char expected) -> bool
	{
		auto const c = std::fgetc(src);

		if (c == expected)
			return true;

		std::ungetc(c, src);
		return false;
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
	auto read(cfile src) -> std::optional<T>
	{
		auto buff = digit_buffer<typename T::type, T::base>();
		auto it = buff.begin();

		skip_ws(src);

		if constexpr (std::is_signed_v<typename T::type>)
		{
			if (expect(src, '-'))
				*it++ = '-';
		}

		if constexpr (T::base != 10)
		{
			if (!expect(src, '0') || !expect(src, T::prefix))
				return {};
		}

		auto const any_zero = skip_zeros(src);
		it = read_digits<T::base>(src, it, buff.end());

		if (it == buff.end())
			return {};

		auto x = typename T::type(0);
		std::from_chars(buff.data(), it, x, T::base);

		return x != 0 || any_zero
		     ? std::make_optional<T>(x)
		     : std::nullopt;
	}

	template <std::integral T>
	auto read(cfile src) -> std::optional<T>
	{
		auto const x = read<dec<T>>(src);
		return x ? std::make_optional(x->value) : std::nullopt;
	}

	template <>
	auto read<char>(cfile src) -> std::optional<char>
	{
		auto const c = std::fgetc(src);
		return (c == EOF) ? std::nullopt : std::make_optional<char>(c);
	}
}

#endif
