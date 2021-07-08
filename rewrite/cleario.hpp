#include <string> // std::string
#include <cstdio> // Wrappee

class clear
{
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
		std::FILE *file;

	public:
		explicit stream(std::FILE *file) : file(file) {}

		// TODO: move constructor/assignment op
		// TODO: ban copy constructor/assignment op

		template <class T>
		void write(const &T);

		void write(bool x) { std::fputs(x ? "True" : "False", file); }
	};

	struct open
	{
		explicit open(cstring name, cstring mode = "r+")
		{
			file = std::fopen(name.data, mode.data);
		}

		~open() { std::fclose(file); }
	};

	template <class T>
	void write(T &&x) { stream{stdout}.write(std::forward<T>(x));}
};
