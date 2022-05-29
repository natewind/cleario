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

## Output

To print a value without any additional characters:

```cpp
clear::write("Hello, World!\n"); // Hello, World!
```

To print one or more values delimited by spaces and ending in a newline:

```cpp
clear::print("Helo, World!", 42, true); // Hello, World! 42 True
```

To flush `stdout`:

```cpp
clear::flush();
```

All three functions return `true` on success and `false` on failure. `print` aborts after the first unsuccessful write.

### Chars

```cpp
clear::print('a', 'b', 'c'); // a b c
```

### Strings

* `char const*`
* `std::string`
* `std::string_view`

```cpp
auto const str = std::string("Qwerty");
clear::print(str); // Qwerty
```

### Booleans

```cpp
clear::print(true, false); // True False
```

### Integers

Integral types, except for `char`:

```cpp
clear::print(1, -2, 3); // 1 -2 3
```

### Pointers

* `T*`
* `std::unique_ptr`
* `std::shared_ptr`

```cpp
auto const x = 5;
auto const ptr = static_cast<void*>(&x);

clear::print(&x); // <int object at 0x7ffcb52c6c54>
clear::print(ptr); // <object at 0x7ffcb52c6c54>
```

### Optionals

```cpp
clear::print(std::optional<int> {}); // None
clear::print(std::optional {12}); // Some(12)
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
clear::print(vec); // [1, 2, 3, 4, 5]
```

### Associative containers

* `std::set`
* `std::multiset`
* `std::unordered_set`
* `std::unordered_multiset`

```cpp
auto const set = std::set {1, 2, 3, 4, 5};
clear::print(set); // {1, 2, 3, 4, 5}
```

* `std::map`
* `std::multimap`
* `std::unordered_map`
* `std::unordered_multimap`

```cpp
auto const map = std::unordered_map {{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}, {"e", 5}};
clear::print(map); // {e: 5, c: 3, b: 2, d: 4, a: 1}
```

### User-defined types

Consider a type:

```cpp
struct Point { int x, y; };
```

To make it printable, implement `write` for it, reducing it to a chain of `write` or `print` calls on already printable types:

```cpp
template <>
auto clear::io::write(Point const &point) -> bool
{
	return write('(')
	    && write(point.x)
	    && write(", ")
	    && write(point.y)
	    && write(')');
}
```

Try it out:

```cpp
clear::print(Point {3, 4}); // (3, 4)
```

## Files

To open a file:

```cpp
auto file1 = clear::open("file1.txt", "w");
```

The access modes are the same ones used with [`std::fopen`](https://en.cppreference.com/w/cpp/io/c/fopen) (the default is `"r+"`). Files are movable (but not copyable) and close automatically when leaving the scope.

To open a file safely (because it can fail):

auto file2 = clear::safe_open("file1.txt", "w"); // returns std::optional

To write to a file, simply use `write`, `print` and `flush` as member functions:

```cpp
file1.print("Helo, World!", 42, true);

if (file2)
	file2->print("Helo, World!", 42, true);
```
