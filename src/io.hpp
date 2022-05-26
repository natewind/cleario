#ifndef CLEARIO_IO_HPP
#define CLEARIO_IO_HPP

#include <cstdio>  // fclose, fopen, stdout
#include <utility> // move, swap

#include "write.hpp"

namespace clear
{
	class io
	{
		impl::file handle = nullptr;

	public:
		explicit constexpr io(impl::file h) : handle(h) {}
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
	};

	class open
	{
		io file;

	public:
		explicit open(char const *name, char const *mode = "r+")
			: file(std::fopen(name, mode)) {}

		open(open&&) = default;
		auto operator=(open&&) -> open& = default;

		~open()
		{
			if (file.unsafe() != nullptr)
				std::fclose(file.unsafe());
		}

		auto write(auto const &x) -> bool { return file.write(x); }
		auto print(auto const&... xs) -> bool { return file.print(xs...); }
	};

	auto write(auto const &x) -> bool { return io(stdout).write(x); }
	auto print(auto const&... xs) -> bool { return io(stdout).print(xs...); }
}

#endif
