#include <cctype>   // std::isspace
#include <cstddef>  // std::ptrdiff_t, std::nullptr_t
#include <fstream>  // std::fstream
#include <istream>  // std::istream
#include <iterator> // std::input_iterator_tag

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

	// No unget() but reads everything twice?
	void skip_ws_alt(char stop = '\n')
	{
		for (char c; (c = src.peek()) != stop && std::isspace(c); src.get());
	}

public:
	constexpr istream_iterator(std::istream &stream) : src(stream) {}

	template <class T>
	operator T()
	{
		auto res = read<T>(src);
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
		auto res = read<T>(src);
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
};
