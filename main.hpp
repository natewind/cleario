#ifndef CLEARIO_HPP
#define CLEARIO_HPP

#include <utility> // std::forward
#include <cstdio>  // Wrappee

#include "src/fstream.hpp"

namespace clear
{
	class open
	{
		fstream file;

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
	void write(T &&x) { fstream(stdout).write(std::forward<T>(x)); }

	template <class... Ts>
	void print(Ts &&... xs) { fstream(stdout).print(std::forward<Ts>(xs)...); }
}

#endif
