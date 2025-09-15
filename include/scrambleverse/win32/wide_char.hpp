#pragma once

#include <string>
#include <cinttypes>

namespace scrambleverse::win32
{
    std::wstring u8_to_wide(const char8_t *u8str, size_t u8str_len);
    std::wstring u8_to_wide(const std::u8string &u8str);

    std::u8string wide_to_u8(const wchar_t *wide_str, size_t wide_str_len);
    std::u8string wide_to_u8(const std::wstring &wide_str);
}
