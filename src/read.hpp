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

	template <int Base, std::integral T>
	auto read_base(cfile src) -> std::optional<T>
	{
		auto buff = digit_buffer<T, Base>();
		auto it = buff.begin();

		skip_ws(src);

		if (std::is_signed_v<T> && expect(src, '-'))
			*it++ = '-';

		auto const any_zero = skip_zeros(src);

		while (true)
		{
			auto const next = std::fgetc(src);

			if (!is_digit<Base>(next))
			{
				std::ungetc(next, src);

				auto x = T(0);
				std::from_chars(buff.data(), it, x, Base);

				return x != 0 || any_zero
				     ? std::make_optional<T>(x)
				     : std::nullopt;
			}

			if (it == buff.end())
			{
				std::ungetc(next, src);
				return {};
			}

			*it++ = next;
		}
	}

	template <IntBased T>
	auto read(cfile src) -> std::optional<T>
	{
		if constexpr (T::base != 10)
		{
			if (!expect(src, '0') || !expect(src, T::prefix))
				return {};
		}

		auto const x = read_base<T::base, typename T::type>(src);
		return x ? std::make_optional<T>(*x) : std::nullopt;
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
