# TODO

* [x] Open/close file (RAII class) with name and mode
* [ ] Non-zero-terminated string class [?]
* [ ] `write()` for basic types
	* [x] `char`
	* [x] C-style string
	* [x] `bool` -> False/True
	* [ ] Integer types
	* [ ] Floating types
	* [ ] Pointer types
	* [ ] Arrays
	* [ ] `std::nullptr_t` -> None
	* [ ] `std::char8_t` [?]
* [ ] Do something about `char` vs `int8_t` (wrapper type?) [?]
* [ ] `write()` for STL types [?]
	* [x] `std::string`
	* [ ] `std::string_view`
	* [ ] `std::vector`
	* [ ] `std::optional` -> None/Refl
	* [ ] [More]
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
* [ ] Modularize cleario to get rid of global namespace pollution
* [ ] Use `<format>` instead of custom serialization of basic types [?]
* [ ] Add `noexcept` specifiers for performance (esp. on GCC) [?]
* [ ] Nice README with examples (test beforehand)
