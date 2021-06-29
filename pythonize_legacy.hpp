#ifndef PYTHONIZE_IO
#define PYTHONIZE_IO

#include <ios>         // std::ios_base
#include <string>      // std::string
#include <cctype>      // std::isspace
#include <istream>     // std::istream
#include <fstream>     // std::ifstream
#include <cstddef>     // std::ptrdiff_t, std::nullptr_t
#include <iostream>    // std::cin, std::cout
#include <string_view> // std::string_view
#include <type_traits> // std::is_same

namespace py
{
	bool const __dummy = std::ios_base::sync_with_stdio(false);

	class istream_iterator
	{
		// TODO: Reduce code size (here, in derived and in input())

	protected:
		std::istream &in;

		// TODO: Iterate through chars without reading everything twice!
		inline void skip_ws(char stop = '\n')
		{
			for (char c; (c = in.peek()) != stop && std::isspace(c); in.get());
		}

	public:
		constexpr istream_iterator(std::istream &stream) : in(stream) {}

		template <typename T>
		inline operator T()
		{
			T res;
			in >> res;
			skip_ws();
			return res;
		}

		inline operator char() { return in.get(); }

		using value_type = istream_iterator;
		using difference_type = std::ptrdiff_t;
		using pointer = istream_iterator *;
		using reference = istream_iterator &;
		using iterator_category	= std::input_iterator_tag;

		inline bool operator==(std::nullptr_t) const
		{
			return in.peek() == '\n';
		}

		inline bool operator!=(std::nullptr_t end) const
		{
			return !(*this == end);
		}

		constexpr auto operator++() const { return *this; }
		constexpr auto operator*() const { return *this; }

		// Dummies to satisfy Iterator requirements
		constexpr auto operator++(int) const { return *this; }
		constexpr auto operator->() const { return this; }
	};

	struct ifstream_iterator : public istream_iterator
	{
		using istream_iterator::istream_iterator;

		template <typename T>
		inline operator T()
		{
			T res;
			in >> res;
			skip_ws(EOF);
			return res;
		}

		inline operator char() { return in.get(); }

		using value_type = ifstream_iterator;
		using pointer = ifstream_iterator *;
		using reference = ifstream_iterator &;

		inline bool operator==(std::nullptr_t) const
		{
			return in.peek() == EOF;
		}

		inline bool operator!=(std::nullptr_t end) const
		{
			return !(*this == end);
		}

		constexpr auto operator++() const { return *this; }
		constexpr auto operator*() const { return *this; }

		// Dummies to satisfy Iterator requirements
		constexpr auto operator++(int) const { return *this; }
		constexpr auto operator->() const { return this; }
	};

	struct input
	{
		std::istream &stream;
		inline input(std::string_view prompt = "", std::istream &in = std::cin)
			: stream(in) { std::cout << prompt; }
		constexpr auto begin() { return istream_iterator(stream); }
		constexpr auto end() { return nullptr; }

		template <typename T>
		inline operator T()
		{
			T res;
			stream >> res;
			return res;
		}

		class split; // TODO (lazy)
	};

	class printer
	{
		printer &self = *this;
		std::ostream &out;

	public:
		constexpr printer(std::ostream &stream) : out(stream) {}

		template <typename T = char const*, typename... Args>
		constexpr void operator()(T const &value = "", Args const&... args)
		{
			if constexpr (std::is_same<T, bool>::value)
				out << (value ? "True" : "False");
			else
				out << value;

			if constexpr (sizeof...(Args) > 0)
			{
				out << ' ';
				self(args...);
			}

			else out << '\n';
		}
	};

	inline namespace open_modes
	{
		constexpr auto append   = std::ios_base::app;
		constexpr auto binary   = std::ios_base::binary;
		constexpr auto read     = std::ios_base::in;
		constexpr auto write    = std::ios_base::out;
		constexpr auto truncate = std::ios_base::trunc;
		constexpr auto at_end   = std::ios_base::ate;
	}

	class open
	{
		std::fstream stream;
		using openmode = std::ios_base::openmode;

	public:
		printer print;

		inline open(std::string const &filename, openmode mode = read)
			: print(stream) { stream.open(filename, mode); }

		inline auto input() { return py::input("", stream); }
		constexpr auto begin() { return ifstream_iterator(stream); }
		constexpr auto end() { return nullptr; }

		// TODO: Binary writing/reading
	};

	printer print(std::cout);

	/*template <typename T = char const*, typename... Args>
	inline void print(T const value = "", Args const... args)
	{
		if constexpr (std::is_same<T, bool>::value)
			std::cout << (value ? "True" : "False");
		else
			std::cout << value;

		if constexpr (sizeof...(Args) > 0)
		{
			std::cout << ' ';
			print(args...);
		}

		else std::cout << '\n';
	}*/
}

#endif
