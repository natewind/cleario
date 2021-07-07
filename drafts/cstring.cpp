#include <stdio.h>

using size_t = decltype(sizeof(int));

struct cstring
{
	char const *data;
	size_t const size;

	template <size_t Size>
	string(char const (&cstr)[Size]) : data(cstr), size(Size - 1) {}
};

inline void write(string s)
{
	fwrite(s.data, sizeof(char), s.size, stdout);
}

auto main() -> int
{
	write("Hello, World!\n");
}
