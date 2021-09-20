#include "pythonize_legacy.hpp"

#define with(...) if (__VA_ARGS__; true)

using namespace py;

// TODO: print(sep="", end="");

auto main() -> int
{
	for (int a : open("file.txt"))
		print(a);

	with (auto f = open("hw.txt", write))
		f.print("Hello World!");
}
