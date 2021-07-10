#include <string>  // std::string
#include <utility> // std::move, std::swap, std::forward
#include <cstdio>  // Wrappee

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

	class stream
	{
		std::FILE *handle = nullptr;

	public:
		explicit constexpr stream(std::FILE *h) : handle(h) {}
		constexpr auto unsafe() { return handle; }

		stream(stream const&) = delete;
		auto operator=(stream const&) = delete;

		stream(stream &&other) { (*this) = std::move(other); }

		auto operator=(stream &&other) -> stream&
		{
			std::swap(handle, other.handle);
			return *this;
		}

		template <class T>
		void write(const T&);

		void write(bool x)     { std::fputs(x ? "True" : "False", handle); }
		void write(char x)     { std::fputc(x, handle); }
		void write(cstring xs) { std::fputs(xs.data, handle); }
	};

	class open
	{
		stream file;

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
	};

	template <class T>
	void write(T &&x) { stream(stdout).write(std::forward<T>(x)); }
}
