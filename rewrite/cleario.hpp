#include <string>    // std::string
#include <vector>    // std::vector
#include <utility>   // std::move, std::swap, std::forward
#include <iterator>  // std::next
#include <algorithm> // std::for_each
#include <cstdio>    // Wrappee

namespace clear
{
	// TODO: Do I need size, or this class at all?
	struct cstring
	{
		char const *const data;
		std::size_t const size;

		template <std::size_t BuffSize>
		constexpr cstring(char const (&ptr)[BuffSize])
			: data(ptr), size(BuffSize - 1) {}

		cstring(std::string const &str)
			: data(str.c_str()), size(str.size()) {}
	};

	class fstream
	{
		std::FILE *stream = nullptr;

	public:
		explicit constexpr fstream(std::FILE *f) : stream(f) {}
		constexpr auto unsafe() { return stream; }

		fstream(fstream const&) = delete;
		auto operator=(fstream const&) = delete;

		fstream(fstream &&other) { (*this) = std::move(other); }

		auto operator=(fstream &&other) -> fstream&
		{
			std::swap(stream, other.stream);
			return *this;
		}

		template <class T>
		void write(const T&);

		void write(bool b)        { std::fputs(b ? "True" : "False", stream); }
		void write(char c)        { std::fputc(c, stream); }
		void write(char const *s) { std::fputs(s, stream); }

		template <class T>
		void write(std::vector<T> const &xs)
		{
			write('[');

			if (auto const it = begin(xs); it != end(xs))
			{
				write(*it);

				std::for_each(next(it), end(xs), [this](auto const &x)
				{
					write(',');
					write(' ');
					write(x);
				});
			}

			write(']');
		}

		void print() { write('\n'); }

		template <class T, class... Ts>
		void print(T const &x, Ts const&... xs)
		{
			write(x);

			if constexpr (sizeof...(Ts) > 0)
				write(' ');

			print(xs...);
		}
	};

	class open
	{
		fstream file;

	public:
		explicit open(cstring name, cstring mode = "r+")
			: file(std::fopen(name.data, mode.data)) {}

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
