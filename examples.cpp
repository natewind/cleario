struct Point { int x, y; };

// TODO: Find a way to get rid of this uglyness!
namespace clear { void write(Point const &); }

#include "io.hpp"

void clear::write(Point const &point)
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
