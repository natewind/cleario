# ClearIO

A header-only IO library implemented in C++20, internally a wrapper over `stdio`.

The library is under development and subject to change. Contributions are welcome (but keep in mind that I’m very opinionated). You can also [log an issue](https://github.com/natewind/cleario/issues) if you spot a bug or if you want a particular feature not already listed in [TODO](https://github.com/natewind/cleario/blob/master/TODO.md).

## Advantages

* Clean and consistent interface
* Pretty-printing STL containers and pointers
* No `sync_with_stdio`, so should be faster than `iostream`
* No runtime format strings, so might be faster than `stdio`

## Installation

Add it to your Git project as a submodule:

```bash
git submodule add git@github.com:natewind/cleario.git
```

Or simply clone:

```bash
git clone git@github.com:natewind/cleario.git
```

Include the public interface:

```cpp
#include "cleario/include.hpp"
```

## Input

To read a value of type `T`:

```cpp
auto const x = clear::read<T>(); // x: T
```

To read multiple values of types `Ts`:

```cpp
auto const xs = clear::read<Ts...>(); // xs: std::tuple<Ts...>
```

### Chars

```cpp
auto const [a, b] = clear::read<char, char>();
```

## Output

To print one or more values without a newline:

```cpp
clear::print("Helo, World! ", 42, ' ', true); // Hello, World! 42 True
```

With a newline:

```cpp
clear::println("Helo, World! ", 42, ' ', true); // Hello, World! 42 True
```

To flush `stdout`:

```cpp
clear::flush();
```

All three functions return `true` on success and `false` on failure. `print` / `println` aborts after the first unsuccessful write.

### Chars

```cpp
clear::println('a', 'b', 'c'); // abc
```

### Strings

* `char const*`
* `std::string`
* `std::string_view`

```cpp
auto const str = std::string("Qwerty");
clear::println(str); // Qwerty
```

### Booleans

```cpp
clear::println(true, ' ', false); // True False
```

### Integers

Integral types (except for char) in different bases:

```cpp
clear::println(150); // 150
clear::println(clear::bin {150}); // 0b10010110
clear::println(clear::oct {150}); // 0o226
clear::println(clear::hex {150}); // 0x96
```

Explicit decimal base to print `char` as an integer:

```cpp
clear::println(clear::dec {'q'}); // 113
```

### Floats

* `float`
* `double`
* `long double`

Chooses the shortest notation between `std::chars_format::fixed` and `std::chars_format::scientific`:

```cpp
clear::println(3.14); // 3.14
clear::println(-0.0000000005); // -5e-10
```

### Pointers

* `T*`
* `std::unique_ptr`
* `std::shared_ptr`

```cpp
auto const x = 5;
auto const ptr = static_cast<void*>(&x);

clear::println(&x); // <int object at 0x7ffcb52c6c54>
clear::println(ptr); // <object at 0x7ffcb52c6c54>
```

### Optionals

```cpp
clear::println(std::optional<int> {}); // None
clear::println(std::optional {12}); // Some(12)
```

### Tuples

```cpp
clear::println(std::tuple(5, false, "qwerty")); // (5, False, qwerty)
```

### Sequence containers

* `T[]`
* `std::array`
* `std::vector`
* `std::deque`
* `std::forward_list`
* `std::list`

```cpp
auto const vec = std::vector {1, 2, 3, 4, 5};
clear::println(vec); // [1, 2, 3, 4, 5]
```

### Associative containers

* `std::set`
* `std::multiset`
* `std::unordered_set`
* `std::unordered_multiset`

```cpp
auto const set = std::set {1, 2, 3, 4, 5};
clear::println(set); // {1, 2, 3, 4, 5}
```

* `std::map`
* `std::multimap`
* `std::unordered_map`
* `std::unordered_multimap`

```cpp
auto const map = std::unordered_map {{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}, {"e", 5}};
clear::println(map); // {e: 5, c: 3, b: 2, d: 4, a: 1}
```

### User-defined types

Consider a type:

```cpp
struct Point { int x, y; };
```

To make it printable, implement `print` for it by calling `print` on already printable types:

```cpp
template <>
auto clear::io::print(Point const &point) -> bool
{
	return print('(', point.x, ", ", point.y, ')');
}
```

Try it out:

```cpp
clear::println(Point {3, 4}); // (3, 4)
```

## Files

To open a file:

```cpp
auto file = clear::open("file.txt", "w");
```

The access modes are the same ones used with [`std::fopen`](https://en.cppreference.com/w/cpp/io/c/fopen) (the default is `"r+"`). Files are movable (but not copyable) and close automatically when leaving the scope.

To open a file safely (because it can fail):

```cpp
auto maybe_file = clear::safe_open("maybe_file.txt", "w"); // returns std::optional
```

To write to a file, simply use `print` / `println` and `flush` as member functions:

```cpp
file.println("Helo, World! ", 42, ' ', true);

if (maybe_file)
	maybe_file->println("Helo, World! ", 42, ' ', true);
```

To read from a file, use `read` as a member function:

```cpp
auto const [a, b] = open("input.txt").read<char, char>();
```
