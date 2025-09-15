
#include <string>
#include <Windows.h>

#include "scrambleverse/win32/wide_char.hpp"
#include "scrambleverse/win32/error.hpp"

std::wstring scrambleverse::win32::u8_to_wide(const char8_t *u8str, size_t u8str_len)
{
    if (u8str == nullptr || u8str_len == 0)
    {
        return std::wstring();
    }

    int wide_char_len = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char *>(u8str), static_cast<int>(u8str_len), nullptr, 0);
    if (wide_char_len == 0)
    {
        Win32Error::throw_when_error();
    }

    std::wstring wide_str(wide_char_len, L'\0');
    int result = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char *>(u8str), static_cast<int>(u8str_len), wide_str.data(), wide_char_len);
    if (result == 0)
    {
        Win32Error::throw_when_error();
    }

    return wide_str;
}

std::wstring scrambleverse::win32::u8_to_wide(const std::u8string &u8str)
{
    return u8_to_wide(u8str.data(), u8str.size());
}

std::u8string scrambleverse::win32::wide_to_u8(const wchar_t *wide_str, size_t wide_str_len)
{
    if (wide_str == nullptr || wide_str_len == 0)
    {
        return std::u8string();
    }

    int u8str_len = WideCharToMultiByte(CP_UTF8, 0, wide_str, static_cast<int>(wide_str_len), nullptr, 0, nullptr, nullptr);
    if (u8str_len == 0)
    {
        Win32Error::throw_when_error();
    }

    std::u8string u8str(u8str_len, u8'\0');
    int result = WideCharToMultiByte(CP_UTF8, 0, wide_str, static_cast<int>(wide_str_len), reinterpret_cast<char *>(u8str.data()), u8str_len, nullptr, nullptr);
    if (result == 0)
    {
        Win32Error::throw_when_error();
    }

    return u8str;
}

std::u8string scrambleverse::win32::wide_to_u8(const std::wstring &wide_str)
{
    return wide_to_u8(wide_str.data(), wide_str.size());
}
