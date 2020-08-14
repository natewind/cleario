namespace impl
{
	using size_t = decltype(sizeof(int));
	using FILE = void;

	extern "C"
	{
		// TODO [Fix]: this only works on Unix, standard says these are macros
		// Wait for C++20 modules and just include stdio?
		extern FILE *stdin, *stdout, *stderr;

		auto fputc(char c, FILE *stream) -> int;
		auto fputs(char const *str, FILE *stream) -> int;
		auto fwrite(void const *str, size_t size,
		            size_t count, FILE *stream) -> size_t;
	}
}
