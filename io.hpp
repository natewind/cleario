#include "impl.hpp"
#include "traits.hpp"
#include <iterator>
#include <type_traits>

namespace clear
{
	void write(bool b)
	{
		impl::fputs(b ? "True" : "False", impl::stdout);
	}

	void write(char c) { impl::fputc(c, impl::stdout); }

	// TODO: Replace with custom non-zero-terminated string class
	template <impl::size_t Size>
	void write(char const (&str)[Size])
	{
		impl::fwrite(str, sizeof(char), Size - 1, impl::stdout);
	}

	template <class T, IsIntegral<T> = true>
	void write(T value)
	{
		using Int = IntTraits<10, T>;

		// TODO: replace by std::array?
		char buff[Int::maxlen];
		auto const str = Int::to_string(value, buff);
		auto const count = std::distance(str, std::end(buff));

		impl::fwrite(str, sizeof(char), std::size_t(count), impl::stdout);
	}

	template <class T, IsClass<T> = true>
	void write(T const&);

	void print() { write('\n'); }

	template <class T, class... Args>
	void print(T const &value, Args const... args)
	{
		write(value);

		if constexpr (sizeof...(Args) > 0)
			write(' ');

		print(args...);
	}
}
