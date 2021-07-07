#include <cstdio>
#include <utility> // std::forward

class open
{
	FILE *handle;

public:
	void write(bool b)
	{
		std::fputs(b ? "True" : "False", handle);
	}

    void write(int x)
	{
		std::fprintf(handle, "%d", x);
	}

	// TODO: constructor(char const*) { fopen }, destructor { fclose }

    static auto cout() -> open
    {
        auto file = open();
        file.handle = stdout;
        return file;
    }
};

template <class T>
void write(T &&x)
{
	open::cout().write(std::forward<T>(x));
}

auto main() -> int
{

	write(true);
}
