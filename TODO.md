**Update README after extending functionality!**

* [ ] Public interface
	* [x] Open a file, close in the destructor
	* [x] `safe_open -> std::optional`
	* [ ] Output
		* [x] `io::write`
		* [x] Variadic `io::print`
		* [x] `::write` and `::print`
		* [x] `io::flush` and `::flush`
		* [ ] Custom `sep` and `end` for `print`
		* [ ] [?] `write_base` to the interface
		* [ ] [?] Binary writing
	* [ ] Input
		* [ ] Unsafe
			* [ ] `io::input<T = std::string, Ts...>(String auto prompt = "")`
			* [ ] Variadic `io::read<Ts...>() -> std::tuple<Ts...>`
			* [ ] `io::read<T> -> T`
			* [ ] `::read<Ts...>`
		* [ ] Safe
			* [ ] `io::safe_input`
			* [ ] `io::safe_read<Ts...>() -> std::optional<std::tuple<Ts...>>`
			* [ ] `io::safe_read<T> -> std::optional<T>`
			* [ ] `::safe_read<Ts...>`
		* [ ] Echoless read from `stdin`
		* [ ] [?] Public `read_base`
		* [ ] [?] Public `skip_ws` (for user-defined types)
		* [ ] Verify `char`/string, `else nullopt` (for user-defined types)
		* [ ] Differentiate between reading words and lines into `String`
		* [ ] [?] Logging errors to `stderr`
		* [ ] [?] Binary reading
		* [ ] [?] `read_until(pred)`
		* [ ] [?] `maybe_read(pred) -> std::optional`
	* [ ] Iterators
		* [ ] `write_iter` (working title)
		* [ ] `read_iter` (working title)
		* [ ] Verify with `std::ranges::{input_range, output_range}`
	* [ ] Concepts
		* [ ] `Writable`
		* [ ] `Readable`
* [ ] `impl::write`
	* [x] `char`
	* [x] `bool`
	* [x] Strings
		* [x] `char const*`
		* [x] `std::string`
		* [x] `std::string_view`
	* [x] Integral types
		* [x] `std::integral`
		* [x] `dec` wrapper (for `char`)
		* [x] `bin` wrapper -> 0b00...
		* [x] `oct` wrapper -> 0o00...
		* [x] `hex` wrapper -> 0x00...
	* [ ] Floating types
		* [ ] Default format
		* [ ] Set precision
		* [ ] Decimal places before the point
		* [ ] Decimal places after the point
		* [ ] Fillers (`'0'`, `' '` etc.)
		* [ ] Scientific notation
	* [x] Pointers
		* [x] `T*`
		* [x] `std::unique_ptr`
		* [x] `std::shared_ptr`
	* [x] Sequence containers
		* [x] `T[]`
		* [x] `std::array`
		* [x] `std::vector`
		* [x] `std::deque`
		* [x] `std::forward_list`
		* [x] `std::list`
	* [x] Sets
		* [x] `std::set`
		* [x] `std::multiset`
		* [x] `std::unordered_set`
		* [x] `std::unordered_multiset`
	* [x] Maps
		* [x] `std::map`
		* [x] `std::multimap`
		* [x] `std::unordered_map`
		* [x] `std::unordered_multimap`
	* [ ] Other STL types
		* [x] `std::optional`
		* [ ] `std::tuple` -> (a0, a1)
	* [x] User-defined types
* [ ] `impl::read`
	* [ ] Entire file
	* [ ] `char`
	* [ ] `bool`
	* [ ] `std::string`
	* [ ] Integral types
		* [ ] `std::integral`
		* [ ] `dec` wrapper (for `char`)
		* [ ] `bin` wrapper -> 0b00...
		* [ ] `oct` wrapper -> 0o00...
		* [ ] `hex` wrapper -> 0x00...
	* [ ] Floating types
		* [ ] Default format
		* [ ] Scientific notation
	* [ ] Pointers (`T*`)
	* [ ] Sequence containers
		* [ ] `std::vector`
		* [ ] `std::deque`
		* [ ] `std::forward_list`
		* [ ] `std::list`
	* [ ] Sets
		* [ ] `std::set`
		* [ ] `std::multiset`
		* [ ] `std::unordered_set`
		* [ ] `std::unordered_multiset`
	* [ ] Maps
		* [ ] `std::map`
		* [ ] `std::multimap`
		* [ ] `std::unordered_map`
		* [ ] `std::unordered_multimap`
	* [ ] Other STL types
		* [ ] `std::optional`
		* [ ] `std::tuple`
	* [ ] User-defined types
* [ ] Improvements
	* [ ] Modularize cleario when GCC gets module support
	* [ ] Print quotation marks around strings inside containers
	* [ ] Read quotation marks around strings inside containers
	* [ ] [Add](https://stackoverflow.com/questions/42832657/what-can-and-what-cant-throw-an-exception-in-c/42835627#42835627) `noexcept` specifiers for performance
	* [ ] [?] Use [{fmt}](https://github.com/fmtlib/fmt) for printing (compile-time format strings > variadic `print`)
	* [ ] `print`/`write` to take simple types by value (concept conflicts?)
	* [ ] README warning about using echoless with multithreading (stream may stay echoless)
	* [ ] Make `read` methods `const`
	* [ ] Investigate MSVC deprecation of `fopen` (check other functions?)
