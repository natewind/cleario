#include <string> // std::string
#include <cstdio> // Wrappee

namespace clear
{
	struct cstring
	{
		char const *data;
		std::size_t const size;

		template <std::size_t BuffSize>
		constexpr cstring(char const (&ptr)[BuffSize])
			: data(ptr), size(BuffSize - 1) {}

		cstring(std::string const &str)
			: data(str.c_str()), size(str.size()) {}
	};

	struct open
	{
		std::FILE *const stream;

		explicit open(cstring name, cstring mode = "r+")
		{
			std::fopen(name.data, mode.data);
		}

		~open() { std::fclose(stream); }
	};
}
