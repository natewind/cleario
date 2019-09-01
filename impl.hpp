namespace impl
{
	using size_t = decltype(sizeof(int));
	using FILE = void;

	extern "C"
	{
		extern FILE *stdin, *stdout, *stderr;

		auto fputc(char c, FILE *stream) -> int;
		auto fputs(const char *str, FILE *stream) -> int;
		auto fwrite(const void *str, size_t size,
		            size_t count, FILE *stream) -> size_t;
	}
}
