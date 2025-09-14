#include "scrambleverse/win32/error.hpp"
#include "scrambleverse/win32/view_of_file.hpp"
#include "macros.h"

using namespace scrambleverse::win32;

void internal::UnmapViewOfFile(LPVOID lpBaseAddress)
{
    if (lpBaseAddress)
    {
        ::UnmapViewOfFile(lpBaseAddress);
    }
}

ViewOfFile::ViewOfFile() noexcept = default;

ViewOfFile::ViewOfFile(LPVOID ptr, bool auto_close) noexcept : HandleBase(ptr, auto_close) {}

ViewOfFile ViewOfFile::Map(
    HANDLE hFileMappingObject,
    DWORD dwDesiredAccess,
    size_t offset,
    SIZE_T dwNumberOfBytesToMap)
{
    LPVOID ptr = ::MapViewOfFile(
        hFileMappingObject,
        dwDesiredAccess,
        high_dword(offset),
        low_dword(offset),
        dwNumberOfBytesToMap);

    if (ptr == nullptr)
    {
        Win32Error::throw_when_error();
        return ViewOfFile();
    }

    return ViewOfFile(ptr);
}

void *ViewOfFile::ptr(size_t offset) const noexcept
{
    return reinterpret_cast<uint8_t *>(get()) + offset;
}
