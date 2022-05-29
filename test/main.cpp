#include "../include.hpp"

struct Point { int x, y; };

template <>
inline auto clear::io::write(Point const &point) -> bool
{
	return write('(')
	    && write(point.x)
	    && write(", ")
	    && write(point.y)
	    && write(')');
}

template <>
inline auto clear::io::read<Point const &point>() -> std::optional<auto>
{
	auto const xy = read<int, int>('(', _, ", ", _, ')');
	return xy ? Point {xy.first, xy.second} : {};
}

auto main() -> int
{
	using namespace clear;

	// Print to stdout: =======================================================

	print("print<bool> =>", true);
	print("print<bool> =>", false);
	print("print<int>  =>", 42);
	print("print<int>  =>", -12, '\n');

	auto const cstr = "Hello, World!";
	auto const strv = std::string_view(cstr);
	auto const str = std::string("Hello, World!");

	print("print<char...>          =>", 'a', 'b', 'c');
	print("print<const char*>      =>", cstr);
	print("print<std::string_view> =>", strv);
	print("print<std::string>      =>", str, '\n');

	auto const x = 42;
	auto const vec = std::vector {1, 2, 3, 4, 5};

	print("print<void*>        =>", (void const*)&x);
	print("print<int*>         =>", &x);
	print("print<std::vector*> =>", &vec, '\n');

	auto const uptr1 = std::unique_ptr<int> {};
	auto const uptr2 = std::make_unique<int>(60);
	auto const sptr1 = std::shared_ptr<int> {};
	auto const sptr2 = std::make_shared<int>(60);

	print("print<std::unique_ptr<int>> =>", uptr1);
	print("print<std::unique_ptr<int>> =>", uptr2);
	print("print<std::shared_ptr<int>> =>", sptr1);
	print("print<std::shared_ptr<int>> =>", sptr2, '\n');

	auto const opt1 = std::optional(12);
	auto const opt2 = std::optional<int> {};

	print("print<std::optional<int>> =>", opt1);
	print("print<std::optional<int>> =>", opt2, '\n');

	 int const arr1[] =                   {1, 2, 3, 4, 5};
	auto const arr2   = std::array        {1, 2, 3, 4, 5};
	auto const deq    = std::deque        {1, 2, 3, 4, 5};
	auto const fls    = std::forward_list {1, 2, 3, 4, 5};
	auto const lst    = std::list         {1, 2, 3, 4, 5};

	print("print<int[]>                   =>", arr1);
	print("print<std::array<int>>         =>", arr2);
	print("print<std::vector<int>>        =>", vec);
	print("print<std::deque<int>>         =>", deq);
	print("print<std::forward_list<int>>  =>", fls);
	print("print<std::list<int>>          =>", lst, '\n');

	auto const set   = std::set                {1, 2, 3, 4, 5};
	auto const mset  = std::multiset           {1, 2, 3, 4, 5};
	auto const uset  = std::unordered_set      {1, 2, 3, 4, 5};
	auto const umset = std::unordered_multiset {1, 2, 3, 4, 5};

	print("print<std::set<int>>                =>", set);
	print("print<std::multiset<int>>           =>", mset);
	print("print<std::unordered_set<int>>      =>", uset);
	print("print<std::unordered_multiset<int>> =>", umset, '\n');

	auto const map = std::map<std::string, int>
		{{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}, {"e", 5}};

	auto const mmap  = std::multimap(begin(map), end(map));
	auto const umap  = std::unordered_map(begin(map), end(map));
	auto const ummap = std::unordered_multimap(begin(map), end(map));

	print("print<std::map<int>>                =>", map);
	print("print<std::multimap<int>>           =>", mmap);
	print("print<std::unordered_map<int>>      =>", umap);
	print("print<std::unordered_multimap<int>> =>", ummap, '\n');

	auto const point = Point {3, 4};

	print("print<Point> =>", point);

	// Print to a file: =======================================================

	auto file = open("file.txt", "w");

	file.print("print<bool> =>", true);
	file.print("print<bool> =>", false);
	file.print("print<int>  =>", 42);
	file.print("print<int>  =>", -12, '\n');

	file.print("print<char...>          =>", 'a', 'b', 'c');
	file.print("print<const char*>      =>", cstr);
	file.print("print<std::string_view> =>", strv);
	file.print("print<std::string>      =>", str, '\n');

	file.print("print<void*>        =>", (void const*)&x);
	file.print("print<int*>         =>", &x);
	file.print("print<std::vector*> =>", &vec, '\n');

	file.print("print<std::unique_ptr<int>> =>", uptr1);
	file.print("print<std::unique_ptr<int>> =>", uptr2);
	file.print("print<std::shared_ptr<int>> =>", sptr1);
	file.print("print<std::shared_ptr<int>> =>", sptr2, '\n');

	file.print("print<std::optional<int>> =>", opt1);
	file.print("print<std::optional<int>> =>", opt2, '\n');

	file.print("print<int[]>                   =>", arr1);
	file.print("print<std::array<int>>         =>", arr2);
	file.print("print<std::vector<int>>        =>", vec);
	file.print("print<std::deque<int>>         =>", deq);
	file.print("print<std::forward_list<int>>  =>", fls);
	file.print("print<std::list<int>>          =>", lst, '\n');

	file.print("print<std::set<int>>                =>", set);
	file.print("print<std::multiset<int>>           =>", mset);
	file.print("print<std::unordered_set<int>>      =>", uset);
	file.print("print<std::unordered_multiset<int>> =>", umset, '\n');

	file.print("print<std::map<int>>                =>", map);
	file.print("print<std::multimap<int>>           =>", mmap);
	file.print("print<std::unordered_map<int>>      =>", umap);
	file.print("print<std::unordered_multimap<int>> =>", ummap, '\n');

	file.print("print<Point> =>", point);
}
