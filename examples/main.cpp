#include <vector>
#include "../main.hpp"

struct Point { int x, y; };

template <>
inline void clear::fstream::write(Point const &point)
{
	write('(');
	write(point.x);
	write(", ");
	write(point.y);
	write(')');
}

auto main() -> int
{
	auto file = clear::open("file.txt", "w");
	file.print(Point {3, 4});

	auto vec = std::vector{1, 2, 3, 4, 5};
	clear::print(vec);

	clear::print(&vec);
}
