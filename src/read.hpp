#ifndef CLEARIO_READ_HPP
#define CLEARIO_READ_HPP

#include <cstdio> // fgetc
#include "types.hpp"

namespace clear::impl
{
	template <class T>
	auto read(cfile src) -> T;

	template <>
	auto read<char>(cfile src) -> char { return std::fgetc(src); }
}

#endif
