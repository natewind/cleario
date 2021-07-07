constexpr auto char_bit() -> int
{
    auto bits = 0;
    auto max = (unsigned char)(-1);
    while (max)
    {
        bits += bool(max);
        max <<= 1;
    }

    return bits;
}

template <class SignedInt>
constexpr auto max_shift =
    SignedInt(1) << (sizeof(SignedInt) * char_bit() - 2);

template <class SignedInt>
constexpr auto max = max_shift<SignedInt> - 1 + max_shift<SignedInt>;
