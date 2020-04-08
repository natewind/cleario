#include <limits> // TODO: Custom limits
#include <iterator>
#include <algorithm>
#include <type_traits>

namespace clear
{
	template <class T>
	using IsIntegral = std::enable_if_t<std::is_integral_v<T>, bool>;

	template <int Base, class T, IsIntegral<T> = true>
	class IntTraits
	{
		using limits = std::numeric_limits<T>;

	public:
		static constexpr auto log(T x, T acc = 0) -> T
		{
			return (x == 0) ? acc : log(x / Base, acc + 1);
		}

		// TODO: Fix a bug: charlen(0) returns 0
		static constexpr auto charlen(T x) -> T
		{
			return log(x, T((x < 0) ? 1 : 0));
		}

		static constexpr auto min = limits::min(), max = limits::max();
		static constexpr auto maxlen = std::max(charlen(min), charlen(max));

		// TODO: Also return size
		static auto to_string(T value, char (&result)[maxlen]) -> char *
		{
			static constexpr auto min_base = 2, max_base = 36;

			static_assert
			(
				Base >= min_base && Base <= max_base,
				"to_string() requires Base to be in range [2, 36]."
			);

			static constexpr char digits_impl[] =
				"zyxwvutsrqponmlkjihgfedcba987654321"
				"0123456789abcdefghijklmnopqrstuvwxyz";
			static constexpr auto digits = &digits_impl[max_base - 1];

			const auto negative = value < 0;

			auto end = std::end(result);

			while (value != 0)
			{
				*(--end) = digits[value % Base];
				value /= Base;
			}

			if (negative)
				*(--end) = '-';

			return end;
		}
	};
}
