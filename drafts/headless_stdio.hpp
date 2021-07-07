namespace impl
{
	using size_t = decltype(sizeof(int));
	using FILE = void;

	extern "C"
	{
		// This only works on Unix, standard says these are macros
		extern FILE *stdin, *stdout, *stderr;

		auto fputc(char c, FILE *stream) -> int;
		auto fputs(char const *str, FILE *stream) -> int;
		auto fwrite(void const *str, size_t size,
		            size_t count, FILE *stream) -> size_t;
	}
}
