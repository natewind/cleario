#include "pythonize_legacy.hpp"

#define with(...) if (__VA_ARGS__; true)

using namespace py;

// TODO: Input the whole line
// TODO: auto [a, b, c] = input();
// TODO: print(sep="", end="");

auto main() -> int
{
	auto number = float(input("Enter float: "));
	print(number, 42);

	print("a + b =", int(input("a = ")) + int(input("b = ")));

	for (int a : open("file.txt"))
		print(a);

	with (auto f = open("hw.txt", write))
		f.print("Hello World!");
}
