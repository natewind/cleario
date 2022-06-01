#include "../include.hpp"

struct Point { int x, y; };

template <>
inline auto clear::io::print(Point const &point) -> bool
{
	return print('(', point.x, ", ", point.y, ')');
}

// template <>
// inline auto clear::io::read<Point const &point>() -> std::optional<auto>
// {
// 	auto const xy = read<int, int>('(', _, ", ", _, ')');
// 	return xy ? Point {xy.first, xy.second} : {};
// }

auto main() -> int
{
	using namespace clear;

	// Print to stdout: =======================================================

	println("println<bool> => ", true);
	println("println<bool> => ", false);
	println("println<int>  => ", 42);
	println("println<int>  => ", -12, '\n');

	flush();

	println("println<float>       => ", 3.14f);
	println("println<double>      => ", -0.0000000005);
	println("println<long double> => ", 100000000000000.0l, '\n');

	println("println<bin>       => ", bin {150});
	println("println<oct>       => ", oct {150});
	println("println<hex>       => ", hex {150});
	println("println<dec<char>> => ", dec {'q'}, '\n');

	auto const cstr = "Hello, World!";
	auto const strv = std::string_view(cstr);
	auto const str = std::string("Hello, World!");

	println("println<char...>          => ", 'a', 'b', 'c');
	println("println<const char*>      => ", cstr);
	println("println<std::string_view> => ", strv);
	println("println<std::string>      => ", str, '\n');

	auto const x = 42;
	auto const vec = std::vector {1, 2, 3, 4, 5};

	println("println<void*>        => ", (void const*)&x);
	println("println<int*>         => ", &x);
	println("println<std::vector*> => ", &vec, '\n');

	auto const uptr1 = std::unique_ptr<int> {};
	auto const uptr2 = std::make_unique<int>(60);
	auto const sptr1 = std::shared_ptr<int> {};
	auto const sptr2 = std::make_shared<int>(60);

	println("println<std::unique_ptr<int>> => ", uptr1);
	println("println<std::unique_ptr<int>> => ", uptr2);
	println("println<std::shared_ptr<int>> => ", sptr1);
	println("println<std::shared_ptr<int>> => ", sptr2, '\n');

	auto const opt1 = std::optional(12);
	auto const opt2 = std::optional<int> {};

	println("println<std::optional<int>> => ", opt1);
	println("println<std::optional<int>> => ", opt2, '\n');

	println("println<std::tuple> => ", std::tuple());
	println("println<std::tuple> => ", std::tuple(5));
	println("println<std::tuple> => ", std::tuple(5, false, "qwerty"), '\n');

	 int const arr1[] =                   {1, 2, 3, 4, 5};
	auto const arr2   = std::array        {1, 2, 3, 4, 5};
	auto const deq    = std::deque        {1, 2, 3, 4, 5};
	auto const fls    = std::forward_list {1, 2, 3, 4, 5};
	auto const lst    = std::list         {1, 2, 3, 4, 5};

	println("println<int[]>                   => ", arr1);
	println("println<std::array<int>>         => ", arr2);
	println("println<std::vector<int>>        => ", vec);
	println("println<std::deque<int>>         => ", deq);
	println("println<std::forward_list<int>>  => ", fls);
	println("println<std::list<int>>          => ", lst, '\n');

	auto const set   = std::set                {1, 2, 3, 4, 5};
	auto const mset  = std::multiset           {1, 2, 3, 4, 5};
	auto const uset  = std::unordered_set      {1, 2, 3, 4, 5};
	auto const umset = std::unordered_multiset {1, 2, 3, 4, 5};

	println("println<std::set<int>>                => ", set);
	println("println<std::multiset<int>>           => ", mset);
	println("println<std::unordered_set<int>>      => ", uset);
	println("println<std::unordered_multiset<int>> => ", umset, '\n');

	auto const map = std::map<std::string, int>
		{{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}, {"e", 5}};

	auto const mmap  = std::multimap(begin(map), end(map));
	auto const umap  = std::unordered_map(begin(map), end(map));
	auto const ummap = std::unordered_multimap(begin(map), end(map));

	println("println<std::map<int>>                => ", map);
	println("println<std::multimap<int>>           => ", mmap);
	println("println<std::unordered_map<int>>      => ", umap);
	println("println<std::unordered_multimap<int>> => ", ummap, '\n');

	auto const point = Point {3, 4};

	println("println<Point> => ", point);

	// Print to a file: =======================================================

	auto file = open("file.txt", "w");

	file.println("println<bool> => ", true);
	file.println("println<bool> => ", false);
	file.println("println<int>  => ", 42);
	file.println("println<int>  => ", -12, '\n');

	file.flush();

	file.println("println<float>       => ", 3.14f);
	file.println("println<double>      => ", -0.0000000005);
	file.println("println<long double> => ", 100000000000000.0l, '\n');

	file.println("println<bin>       => ", bin {150});
	file.println("println<oct>       => ", oct {150});
	file.println("println<hex>       => ", hex {150});
	file.println("println<dec<char>> => ", dec {'q'}, '\n');

	file.println("println<char...>          => ", 'a', 'b', 'c');
	file.println("println<const char*>      => ", cstr);
	file.println("println<std::string_view> => ", strv);
	file.println("println<std::string>      => ", str, '\n');

	file.println("println<void*>        => ", (void const*)&x);
	file.println("println<int*>         => ", &x);
	file.println("println<std::vector*> => ", &vec, '\n');

	file.println("println<std::unique_ptr<int>> => ", uptr1);
	file.println("println<std::unique_ptr<int>> => ", uptr2);
	file.println("println<std::shared_ptr<int>> => ", sptr1);
	file.println("println<std::shared_ptr<int>> => ", sptr2, '\n');

	file.println("println<std::optional<int>> => ", opt1);
	file.println("println<std::optional<int>> => ", opt2, '\n');

	file.println("println<std::tuple> => ", std::tuple());
	file.println("println<std::tuple> => ", std::tuple(5));
	file.println("println<std::tuple> => ", std::tuple(5, false, "qwerty"));
	file.println();

	file.println("println<int[]>                   => ", arr1);
	file.println("println<std::array<int>>         => ", arr2);
	file.println("println<std::vector<int>>        => ", vec);
	file.println("println<std::deque<int>>         => ", deq);
	file.println("println<std::forward_list<int>>  => ", fls);
	file.println("println<std::list<int>>          => ", lst, '\n');

	file.println("println<std::set<int>>                => ", set);
	file.println("println<std::multiset<int>>           => ", mset);
	file.println("println<std::unordered_set<int>>      => ", uset);
	file.println("println<std::unordered_multiset<int>> => ", umset, '\n');

	file.println("println<std::map<int>>                => ", map);
	file.println("println<std::multimap<int>>           => ", mmap);
	file.println("println<std::unordered_map<int>>      => ", umap);
	file.println("println<std::unordered_multimap<int>> => ", ummap, '\n');

	file.println("println<Point> => ", point);
}
