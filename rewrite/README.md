# TODO

* [x] Open/close file (RAII class) with name and mode
* [ ] Non-zero-terminated string class [?]
* [ ] `write()` for basic types
    * [ ] `char`
    * [ ] C-style string
    * [x] `bool` -> False/True
    * [ ] Integer types
    * [ ] Floating types
    * [ ] Pointer types
    * [ ] Arrays
    * [ ] `std::nullptr_t` -> None
    * [ ] `std::char8_t` [?]
* [ ] Do something about `char` vs `int8_t` (wrapper type?) [?]
* [ ] `write()` for STL types [?]
    * [ ] `std::string`
    * [ ] `std::vector`
    * [ ] `std::optional` -> None/Refl
    * [ ] [More]
* [ ] `write()` for user-class specializations
* [ ] Variadic `print()` with spaces and a newline
* [ ] `::write()` and `::print()` to `stdout`
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
* [ ] Modularize cleario to get rid of global namespace pollution
* [ ] Use `<format>` instead of custom serialization of basic types [?]
* [ ] Nice README with examples
