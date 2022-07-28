#include <cassert>
#include "../include.hpp"

struct Point { int x, y; };

template <>
inline auto clear::io::print(Point const &point) -> bool
{
	return print('(', point.x, ", ", point.y, ')');
}

// template <>
// inline auto clear::io::read<Point>() -> std::optional<auto>
// {
// 	auto const xy = scan<int, int>('(', _, ", ", _, ')');
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

	auto out = open("out.txt", "w");

	out.println("println<bool> => ", true);
	out.println("println<bool> => ", false);
	out.println("println<int>  => ", 42);
	out.println("println<int>  => ", -12, '\n');

	out.flush();

	out.println("println<float>       => ", 3.14f);
	out.println("println<double>      => ", -0.0000000005);
	out.println("println<long double> => ", 100000000000000.0l, '\n');

	out.println("println<bin>       => ", bin {150});
	out.println("println<oct>       => ", oct {150});
	out.println("println<hex>       => ", hex {150});
	out.println("println<dec<char>> => ", dec {'q'}, '\n');

	out.println("println<char...>          => ", 'a', 'b', 'c');
	out.println("println<const char*>      => ", cstr);
	out.println("println<std::string_view> => ", strv);
	out.println("println<std::string>      => ", str, '\n');

	out.println("println<void*>        => ", (void const*)&x);
	out.println("println<int*>         => ", &x);
	out.println("println<std::vector*> => ", &vec, '\n');

	out.println("println<std::unique_ptr<int>> => ", uptr1);
	out.println("println<std::unique_ptr<int>> => ", uptr2);
	out.println("println<std::shared_ptr<int>> => ", sptr1);
	out.println("println<std::shared_ptr<int>> => ", sptr2, '\n');

	out.println("println<std::optional<int>> => ", opt1);
	out.println("println<std::optional<int>> => ", opt2, '\n');

	out.println("println<std::tuple> => ", std::tuple());
	out.println("println<std::tuple> => ", std::tuple(5));
	out.println("println<std::tuple> => ", std::tuple(5, false, "qwerty"));
	out.println();

	out.println("println<int[]>                   => ", arr1);
	out.println("println<std::array<int>>         => ", arr2);
	out.println("println<std::vector<int>>        => ", vec);
	out.println("println<std::deque<int>>         => ", deq);
	out.println("println<std::forward_list<int>>  => ", fls);
	out.println("println<std::list<int>>          => ", lst, '\n');

	out.println("println<std::set<int>>                => ", set);
	out.println("println<std::multiset<int>>           => ", mset);
	out.println("println<std::unordered_set<int>>      => ", uset);
	out.println("println<std::unordered_multiset<int>> => ", umset, '\n');

	out.println("println<std::map<int>>                => ", map);
	out.println("println<std::multimap<int>>           => ", mmap);
	out.println("println<std::unordered_map<int>>      => ", umap);
	out.println("println<std::unordered_multimap<int>> => ", ummap, '\n');

	out.println("println<Point> => ", point);

	// Read from a file: ======================================================

	auto const in = open("in.txt");

	auto const [a, b] = in.read<char, char>();
	assert(a == 'q' && b == '\n');

	auto const [c, d, e, f] = in.read<int, int, int, char>();
	assert(c == 12 && d == -34 && e == 56 && f == '\n');

	auto const n = in.safe_read<int>();
	assert(!n);
}
