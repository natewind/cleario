#include "impl.hpp"
#include "traits.hpp"
#include <iterator>
#include <type_traits>

namespace clear
{
	inline auto write(bool b)
	{
		impl::fputs(b ? "True" : "False", impl::stdout);
	}

	inline auto write(char c) { impl::fputc(c, impl::stdout); }

	// TODO: Replace with custom non-zero-terinated string class
	template <impl::size_t Size>
	inline auto write(const char (&str)[Size])
	{
		impl::fwrite(str, sizeof(char), Size - 1, impl::stdout);
	}

	template <class T, IsIntegral<T> = true>
	inline auto write(T value)
	{
		using Int = IntTraits<10, T>;

		char buff[Int::maxlen];
		const auto str = Int::to_string(value, buff);
		const auto count = std::distance(str, std::end(buff));

		impl::fwrite(str, sizeof(char), count, impl::stdout);
	}

	inline void print() { write('\n'); }

	template <class T, class... Args>
	inline void print(const T &value, const Args... args)
	{
		write(value);

		if constexpr (sizeof...(Args) > 0)
			write(' ');

		print(args...);
	}
}
