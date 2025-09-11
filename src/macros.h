inline unsigned long low_dword(unsigned long long value)
{
    return static_cast<unsigned long>(value & 0xFFFFFFFF);
}

inline unsigned long high_dword(unsigned long long value)
{
    return static_cast<unsigned long>((value >> 32) & 0xFFFFFFFF);
}
