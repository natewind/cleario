#include "io.hpp"

struct Point { int x, y; };

template <>
void clear::write<Point>(Point const &point)
{
	write('(');
	write(point.x);
	write(", ");
	write(point.y);
	write(')');
}

auto main() -> int
{
	clear::print("Hello World!", 42, true, Point {3, 4});
}
