#include "cleario.hpp"

struct Point { int x, y; };

template <>
inline void clear::fstream::write<Point>(Point const &/*point*/)
{
	write('(');
	// write(point.x);
	write(", ");
	// write(point.y);
	write(')');
}

auto main() -> int
{
	auto file = clear::open("file.txt", "w");

	file.print(Point {3, 4});

	clear::print(std::array{true, false, true, false}, std::array<bool, 0>{});
}
