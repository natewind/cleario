#ifndef CLEARIO_IO_HPP
#define CLEARIO_IO_HPP

#include <cstdio>  // fclose, fopen, stdout
#include <utility> // forward, move, swap

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

		template <class T>
		void write(T &&x) { impl::write(handle, std::forward<T>(x)); }

		void print() { write('\n'); }

		void print(auto const &x, auto const&... xs)
		{
			write(x);

			if constexpr (sizeof...(xs) > 0)
				write(' ');

			print(xs...);
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

		template <class T>
		void write(T &&x) { file.write(std::forward<T>(x)); }

		template <class... Ts>
		void print(Ts &&... xs) { file.print(std::forward<Ts>(xs)...); }
	};

	template <class T>
	void write(T &&x) { io(stdout).write(std::forward<T>(x)); }

	template <class... Ts>
	void print(Ts &&... xs) { io(stdout).print(std::forward<Ts>(xs)...); }
}

#endif
