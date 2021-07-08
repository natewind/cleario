#include "cleario.hpp"

struct Point { int x, y; };

template <>
void clear::stream::write<Point>(Point const &point)
{
	/*write('(');
	write(point.x);
	write(", ");
	write(point.y);
	write(')');*/

	// TEST
	write(point.x == 0);
}

auto main() -> int
{
	auto file = clear::open("file.txt", "w");

	file.write(Point {3, 4});
}
