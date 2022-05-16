#include <set>
#include <unordered_map>
#include <vector>

#include "../main.hpp"

struct Point { int x, y; };

template <>
inline void clear::io::write(Point const &point)
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

	clear::print(std::set{"qwe", "rty", "uio"});
	clear::print(std::unordered_map<char const*, int>
		{{"qwe", 4}, {"rty", 5}, {"uio", 6}});

	clear::print(std::deque{1, 2, 3, 4, 5});
	clear::print(std::forward_list{6, 7, 8, 9, 10});
	clear::print(std::list{11, 12, 13, 14, 15});

	int array[] = {16, 17, 18, 19, 20};
	clear::print(array);

	clear::print(std::make_unique<int>(12));
	clear::print(std::optional<int>(60));
	clear::print(std::optional<int>());

	void *ptr = &vec;
	clear::print(ptr);
}
