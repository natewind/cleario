#ifndef CLEARIO_IO_HPP
#define CLEARIO_IO_HPP

#include <utility> // forward, move, swap

#include "write.hpp"

namespace clear
{
	// class io
	// {
	// 	std::FILE *handle = nullptr;

	// public:
	// 	explicit constexpr io(std::FILE *f) : handle(f) {}
	// 	constexpr auto unsafe() { return handle; }

	// 	io(io const&) = delete;
	// 	auto operator=(io const&) = delete;

	// 	io(io &&other) { (*this) = std::move(other); }

	// 	auto operator=(io &&other) -> io&
	// 	{
	// 		std::swap(handle, other.handle);
	// 		return *this;
	// 	}

	// 	template <class T>
	// 	void write(T &&x) { impl::write(handle, std::forward<T>(x)); }

	// 	void print() { write('\n'); }

	// 	void print(auto const &x, auto const&... xs)
	// 	{
	// 		write(x);

	// 		if constexpr (sizeof...(xs) > 0)
	// 			write(' ');

	// 		print(xs...);
	// 	}
	// };
}

#endif
