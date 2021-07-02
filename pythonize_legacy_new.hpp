#ifndef FILE_HPP
#define FILE_HPP

#include <tuple>    // std::tuple, std::tuple_cat
#include <cctype>   // std::isspace
#include <istream>  // std::istream
#include <fstream>  // std::fstream
#include <cstddef>  // std::ptrdiff_t, std::nullptr_t
#include <utility>  // std::move
#include <iterator> // std::input_iterator_tag

template <class T>
constexpr auto read_one(std::istream &src)
{
	T x;
	src >> x;
	return x;
}

template <class T, class... Ts>
constexpr auto read_tuple(std::istream &src)
{
	auto x = std::tuple(read_one<T>(src));

	if constexpr (sizeof...(Ts) == 0)
		return x;
	else
		return std::tuple_cat(std::move(x), read_tuple<Ts...>(src));
}

class istream_iterator
{
protected:
	std::istream &src;

	void skip_ws(char stop = '\n')
	{
		char c;
		while ((c = src.get()) != stop && std::isspace(c));
		src.unget();
	}

public:
	constexpr istream_iterator(std::istream &stream) : src(stream) {}

	template <class T>
	operator T()
	{
		auto res = read_one<T>(src);
		skip_ws();
		return res;
	}

	operator char() { return src.get(); }

	using value_type = istream_iterator;
	using difference_type = std::ptrdiff_t;
	using pointer = istream_iterator *;
	using reference = istream_iterator &;
	using iterator_category	= std::input_iterator_tag;

	bool operator==(std::nullptr_t) const { return src.peek() == '\n'; }

	bool operator!=(std::nullptr_t end) const { return !(*this == end); }

	constexpr auto operator++() const { return *this; }
	constexpr auto operator*() const { return *this; }

	// Dummies to satisfy Iterator requirements
	constexpr auto operator++(int) const { return *this; }
	constexpr auto operator->() const { return this; }
};

struct ifstream_iterator : public istream_iterator
{
	using istream_iterator::istream_iterator;

	template <class T>
	operator T()
	{
		auto res = read_one<T>(src);
		skip_ws(EOF);
		return res;
	}

	operator char() { return src.get(); }

	using value_type = ifstream_iterator;
	using pointer = ifstream_iterator *;
	using reference = ifstream_iterator &;

	bool operator==(std::nullptr_t) const { return src.peek() == EOF; }

	bool operator!=(std::nullptr_t end) const { return !(*this == end); }

	constexpr auto operator++() const { return *this; }
	constexpr auto operator*() const { return *this; }

	// Dummies to satisfy Iterator requirements
	constexpr auto operator++(int) const { return *this; }
	constexpr auto operator->() const { return this; }
};

class open
{
	std::fstream stream;

public:
	open(char const *filename) { stream.open(filename); }

	constexpr auto begin() { return ifstream_iterator(stream); }
	constexpr auto end() { return nullptr; }

	template <class... Ts>
	constexpr auto read()
	{
		if constexpr (sizeof...(Ts) == 1)
			return read_one<Ts...>(stream);
		else
			return read_tuple<Ts...>(stream);
	}

	template <class T, class... Ts>
	constexpr void print(T const &x, Ts const&... xs)
	{
		stream << x;
		((stream << " " << xs), ...);
		stream << '\n';
	}
};

#endif
