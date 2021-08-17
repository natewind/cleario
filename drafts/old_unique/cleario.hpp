#include "traits.hpp"

#include <cstdio>
#include <iterator>
#include <type_traits>

namespace clear
{
	template <std::size_t Size>
	void write(char const (&str)[Size])
	{
		std::fwrite(str, sizeof(char), Size - 1, stdout);
	}

	template <class T, IsIntegral<T> = true>
	void write(T value)
	{
		using Int = IntTraits<10, T>;

		// TODO: replace by std::array?
		char buff[Int::maxlen];
		auto const str = Int::to_string(value, buff);
		auto const count = std::distance(str, std::end(buff));

		std::fwrite(str, sizeof(char), std::size_t(count), stdout);
	}

	template <class T, IsClass<T> = true>
	void write(T const&);
}
