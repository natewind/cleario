#ifndef CLEARIO_IO_HPP
#define CLEARIO_IO_HPP

#include <cstdio>   // fclose, fflush, fopen, stdout
#include <optional> // make_optional, nullopt
#include <utility>  // move, swap

#include "write.hpp"

namespace clear
{
	class io
	{
		impl::cfile handle = nullptr;

	public:
		explicit constexpr io(impl::cfile h) : handle(h) {}
		constexpr auto unsafe() { return handle; }

		io(io const&) = delete;
		auto operator=(io const&) = delete;

		io(io &&other) { (*this) = std::move(other); }

		auto operator=(io &&other) -> io&
		{
			std::swap(handle, other.handle);
			return *this;
		}

		auto write(auto const &x) -> bool { return impl::write(handle, x); }

		auto print() -> bool { return write('\n'); }

		auto print(auto const &x) -> bool { return write(x) && print(); }

		auto print(auto const &x, auto const&... xs) -> bool
		{
			return write(x)
			    && write(' ')
			    && print(xs...);
		}

		auto flush() -> bool { return std::fflush(handle) == 0; }
	};

	class file
	{
		io stream;

	public:
		explicit constexpr file(impl::cfile handle) : stream(handle) {}

		file(file&&) = default;
		auto operator=(file&&) -> file& = default;

		~file()
		{
			if (stream.unsafe() != nullptr)
				std::fclose(stream.unsafe());
		}

		auto write(auto const &x) -> bool { return stream.write(x); }
		auto print(auto const&... xs) -> bool { return stream.print(xs...); }
		auto flush() -> bool { return stream.flush(); }
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

	auto write(auto const &x) -> bool { return io(stdout).write(x); }
	auto print(auto const&... xs) -> bool { return io(stdout).print(xs...); }
	inline auto flush() -> bool { return io(stdout).flush(); }
}

#endif
