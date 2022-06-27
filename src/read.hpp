#ifndef CLEARIO_READ_HPP
#define CLEARIO_READ_HPP

#include <cstdio>   // EOF, fgetc
#include <optional> // make_optional, nullopt, optional

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
}

#endif
