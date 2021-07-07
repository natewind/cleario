#include "traits.hpp"

// TODO: Hide in a module partition to avoid global namespace pollution
#include <cstdio>
#include <iterator>
#include <type_traits>

// TODO: Optional error-managed IO (try_write, try_read etc.)

namespace clear
{
	inline void write(bool b)
	{
		std::fputs(b ? "True" : "False", stdout);
	}

	inline void write(char c) { std::fputc(c, stdout); }

	// TODO: Replace with custom non-zero-terminated string class
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

	inline void print() { write('\n'); }

	template <class T, class... Args>
	void print(T const &value, Args const... args)
	{
		write(value);

		if constexpr (sizeof...(Args) > 0)
			write(' ');

		print(args...);
	}
}
