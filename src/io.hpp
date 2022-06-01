#ifndef CLEARIO_IO_HPP
#define CLEARIO_IO_HPP

#include <cstdio>   // fclose, fflush, fopen, stdout
#include <optional> // make_optional, nullopt
#include <tuple>    // tuple
#include <utility>  // move, swap

#include "read.hpp"
#include "write.hpp"

namespace clear
{
	class io
	{
	protected:
		impl::cfile handle;

	public:
		constexpr io() : handle(nullptr) {}
		explicit constexpr io(impl::cfile h) : handle(h) {}

		auto print() -> bool { return true; }

		auto print(auto const &x) -> bool { return impl::write(handle, x); }
		auto print(auto const &x, auto const&... xs) -> bool
		{
			return print(x) && print(xs...);
		}

		auto println(auto const&... xs) -> bool
		{
			return print(xs...) && print('\n');
		}

		auto flush() -> bool { return std::fflush(handle) == 0; }

		template <class T>
		auto read() const -> T { return impl::read<T>(handle); }

		// TODO: tuple_cat cannot use read that returns non-tuple!

		// template <class T, class... Ts>
		// auto read() const -> std::tuple<T, Ts...>
		// {
		// 	// Old code:
		// 	auto x = std::tuple(read_one<T>());

		// 	if constexpr (sizeof...(Ts) == 0)
		// 		return x;
		// 	else
		// 		return std::tuple_cat(std::move(x), read_tuple<Ts...>(src));
		// 	return TODO();
		// }
	};

	struct file final : public io
	{
		explicit constexpr file(impl::cfile handle) : io(handle) {}

		file(file const&) = delete;
		auto operator=(file const&) = delete;

		file(file &&other) { (*this) = std::move(other); }

		auto operator=(file &&other) -> file&
		{
			std::swap(handle, other.handle);
			return *this;
		}

		~file()
		{
			if (handle != nullptr)
				std::fclose(handle);
		}
	};

	auto safe_open(char const *name, char const *mode = "r+")
	{
		auto const handle = std::fopen(name, mode);
		return handle ? std::make_optional<file>(handle) : std::nullopt;
	}

	auto open(char const *name, char const *mode = "r+")
	{
		return *safe_open(name, mode);
	}

	auto print  (auto const&... xs) { return io(stdout).print  (xs...); }
	auto println(auto const&... xs) { return io(stdout).println(xs...); }
	inline auto flush()             { return io(stdout).flush(); }

	template <class... Ts>
	auto read() { return io(stdin).read<Ts...>(); }
}

#endif
