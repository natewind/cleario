# TODO

* [x] Open/close file (RAII class) with name and mode
* [ ] `write()` for basic types
	* [x] `char`
	* [x] C-style string
	* [x] `bool` -> False/True
	* [x] Integer types
	* [ ] Floating types
	* [ ] Pointers -> <TYPE object / memory (`void*`) at 0x00...>
	* [x] Arrays -> [a0, a1]
	* [ ] `void` (`write()`) -> () [?]
* [ ] Do something about `char` vs `int8_t` (wrapper type?) [?]
* [ ] Printing integers in other bases
* [ ] Reading integers in other bases
* [ ] `write()` for STL types
	* [ ] Sequences -> [a0, a1]
		* [x] `std::array`
		* [x] `std::vector`
		* [ ] `std::deque`
		* [ ] `std::forward_list`
		* [ ] `std::list`
	* [ ] Sets -> {a0, a1}
		* [ ] `std::set`
		* [ ] `std::multiset`
		* [ ] `std::unordered_set`
		* [ ] `std::unordered_multiset`
	* [ ] Maps -> {a0: b0, a1: b1}
		* [ ] `std::map`
		* [ ] `std::multimap`
		* [ ] `std::unordered_map`
		* [ ] `std::unordered_multimap`
	* [ ] Pointers -> <TYPE object / memory (`void*`) at 0x00...>
		* [ ] `std::unique_ptr`
		* [ ] `std::shared_ptr`
	* [ ] Strings
		* [x] `std::string`
		* [x] `std::string_view`
	* [ ] Other
		* [ ] `std::tuple` -> (a0, a1)
		* [ ] `std::optional` -> None/Refl
		* [ ] `std::nullptr_t` -> None
		* [ ] `std::byte` -> 0x00
		* [ ] `std::char8_t` [?]
		* [ ] `std::complex` -> a + bi
		* [ ] `std::span` (C++20) -> [a0, a1]
* [x] `write()` for user-class specializations
* [x] Variadic `print()` with spaces and a newline
* [x] `::write()` and `::print()` to `stdout`
* [ ] Fancy-print floating types
	* [ ] Precision
	* [ ] Digits before the point
	* [ ] Digits after the point
	* [ ] Fillers ('0', ' ' etc.)
* [ ] Variadic `read()` (one/tuple)
* [ ] `read()` for basic types
* [ ] `read()` for STL types [?]
* [ ] `read()` for user-class specializations
* [ ] `input<T = std::string>(prompt = "")`
* [ ] `::read()` and `::input()` from `stdin`
* [ ] Error printing / logging to `stderr` [?]
* [ ] Echoless input from `stdin`
* [ ] Custom `sep` and `end` for `print()` [?]
* [ ] Reading an entire line
* [ ] Input iterator
* [ ] Output iterator
* [ ] Optional `write()` (default?)
* [ ] Optional `print()` (default?)
* [ ] `safe_read() -> std::optional`
* [ ] `safe_input() -> std::optional`
* [ ] Binary writing/reading
* [ ] Flush [?]
* [ ] Modularize cleario to get rid of global namespace pollution
* [ ] Use `<format>` instead of custom serialization of basic types [?]
* [ ] Add `noexcept` specifiers for performance (esp. on GCC) [?]
* [ ] Make reading `const` [?]
* [ ] Nice README with examples (test beforehand)
