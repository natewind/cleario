* [x] Open/close file (RAII class) with name and mode
* [ ] `write()` for basic types
	* [x] `char`
	* [x] C-style string
	* [x] `bool` -> False/True
	* [x] Integer types
	* [ ] Floating types
	* [x] Pointers -> <object at 0x00...>
	* [x] Arrays -> [a0, a1]
	* [ ] `void` (`write()`) -> () [?]
* [ ] Do something about `char` vs `int8_t` (wrapper type?) [?]
* [ ] Printing integers in other bases
* [ ] Reading integers in other bases
* [ ] Concepts
	* [ ] `Writable`
	* [ ] `Readable`
* [ ] `write()` for STL types
	* [x] Sequences -> [a0, a1]
		* [x] `std::array`
		* [x] `std::vector`
		* [x] `std::deque`
		* [x] `std::forward_list`
		* [x] `std::list`
	* [x] Sets -> {a0, a1}
		* [x] `std::set`
		* [x] `std::multiset`
		* [x] `std::unordered_set`
		* [x] `std::unordered_multiset`
	* [x] Maps -> {a0: b0, a1: b1}
		* [x] `std::map`
		* [x] `std::multimap`
		* [x] `std::unordered_map`
		* [x] `std::unordered_multimap`
	* [x] Pointers -> <object at 0x00...>
		* [x] `std::unique_ptr`
		* [x] `std::shared_ptr`
	* [x] Strings
		* [x] `std::string`
		* [x] `std::string_view`
	* [ ] Other
		* [ ] `std::tuple` -> (a0, a1)
		* [x] `std::optional` -> None/Refl
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
* [ ] Safe file opening/closing (+MSVC `fopen` “deprecation”)
* [ ] `safe_read() -> std::optional`
* [ ] `safe_input() -> std::optional`
* [ ] Binary writing/reading
* [ ] Flush [?]
* [ ] Modularize cleario to get rid of global namespace pollution (C++20)
* [ ] Use `<format>` instead of custom serialization of basic types [?]
* [ ] Add `noexcept` specifiers for performance (esp. on GCC) [?]
* [ ] Make reading `const` [?]
* [ ] Return self on write? `open(...).print(x).print(y)`
* [ ] Read/write `bin<Int>`, `oct<Int>`, `hex<Int>`
* [ ] `void*` -> <object at ...> (no type)
* [ ] Nice README with examples (test beforehand)
