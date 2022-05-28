**Update README after extending functionality!**

* [ ] Public interface
	* [x] Open a file, close in the destructor
	* [x] `io::write`
	* [x] Variadic `io::print`
	* [x] `open::write` and `open::print`
	* [x] `::write` and `::print`
	* [x] `open::flush` and `::flush` (use [`std::fflush`](https://en.cppreference.com/w/cpp/io/c/fflush))
	* [ ] Custom `sep` and `end` for `print`
	* [ ] [?] `write_base` to the interface
	* [ ] Concepts
		* [ ] `Writable`
		* [ ] `Readable`
* [ ] `impl::write`
	* [x] `char`
	* [ ] `char8_t`
	* [x] `bool`
	* [x] Strings
		* [x] `char const*`
		* [x] `std::string`
		* [x] `std::string_view`
	* [ ] Integral types
		* [x] Default format (decimal)
		* [ ] `dec` wrapper (for `char`)
		* [ ] `bin` wrapper -> 0b00...
		* [ ] `oct` wrapper -> 0o00...
		* [ ] `hex` wrapper -> 0x00...
	* [ ] Floating types
		* [ ] Default format
		* [ ] Set precision
		* [ ] Decimal places before the point
		* [ ] Decimal places after the point
		* [ ] Fillers (`'0'`, `' '` etc.)
	* [ ] Pointers
		* [x] `T*`
		* [x] `std::unique_ptr`
		* [x] `std::shared_ptr`
		* [ ] `std::nullptr_t`
	* [x] `std::optional`
	* [ ] Sequence containers
		* [x] `T[]`
		* [x] `std::array`
		* [x] `std::vector`
		* [x] `std::deque`
		* [x] `std::forward_list`
		* [x] `std::list`
		* [ ] `std::span`
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
		* [ ] `std::byte` -> 0x00...
		* [ ] `std::complex` -> a + bi
	* [x] User-defined types
* [ ] Design improvements
	* [ ] Modularize cleario when GCC gets module support
	* [ ] [Add](https://stackoverflow.com/questions/42832657/what-can-and-what-cant-throw-an-exception-in-c/42835627#42835627) `noexcept` specifiers for performance
	* [ ] [?] Use [{fmt}](https://github.com/fmtlib/fmt) for printing (compile-time format strings > variadic `print`)

# Unsorted

* [ ] Variadic `read` (one/tuple)
* [ ] Reading integers in other bases
* [ ] `read` for basic types
* [ ] `read` for STL types [?]
* [ ] `read` for user-class specializations
* [ ] `input<T = std::string>(prompt = "")`
* [ ] `::read` and `::input` from `stdin`
* [ ] Error printing / logging to `stderr` [?]
* [ ] Echoless input from `stdin`
* [ ] Reading an entire line
* [ ] Input iterator
* [ ] Output iterator
* [ ] Safe file opening/closing (+MSVC `fopen` “deprecation”)
* [ ] `safe_read -> std::optional`
* [ ] `safe_input -> std::optional`
* [ ] Binary writing/reading
* [ ] Make reading `const` [?]
* [ ] Add quotation marks to strings inside containers
* [ ] README warning about echoless bad state with multithreading
* [ ] Take simple types by value (concept conflicts?)
* [ ] `verify_read(char)` or something (auxiliary, to verify input format)
