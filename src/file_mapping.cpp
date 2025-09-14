#include "scrambleverse/win32/file_mapping.hpp"
#include "scrambleverse/win32/view_of_file.hpp"
#include "scrambleverse/win32/error.hpp"
#include "macros.h"

using namespace scrambleverse::win32;

FileMapping::FileMapping() noexcept = default;
FileMapping::FileMapping(HANDLE handle) noexcept : Handle(handle) {}

FileMapping FileMapping::Create(
    HANDLE hFile,
    LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
    DWORD flProtect,
    size_t maximumSize,
    LPCWSTR lpName)
{
    HANDLE hMapFile = CreateFileMappingW(
        hFile,
        lpFileMappingAttributes,
        flProtect,
        high_dword(maximumSize),
        low_dword(maximumSize),
        lpName);

    if (hMapFile == nullptr)
    {
        Win32Error::throw_when_error();
        return FileMapping();
    }

    return FileMapping(hMapFile);
}

FileMapping FileMapping::Create(
    HANDLE hFile,
    LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
    DWORD flProtect,
    size_t maximumSize,
    LPCSTR lpName)
{
    HANDLE hMapFile = CreateFileMapping(
        hFile,
        lpFileMappingAttributes,
        flProtect,
        high_dword(maximumSize),
        low_dword(maximumSize),
        lpName);

    if (hMapFile == nullptr)
    {
        Win32Error::throw_when_error();
        return FileMapping();
    }

    return FileMapping(hMapFile);
}

FileMapping FileMapping::Create(
    HANDLE hFile,
    LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
    DWORD flProtect,
    size_t maximumSize,
    std::nullptr_t lpName)
{
    return Create(hFile, lpFileMappingAttributes, flProtect, maximumSize, static_cast<LPCWSTR>(lpName));
}

FileMapping FileMapping::Open(
    DWORD dwDesiredAccess,
    BOOL bInheritHandle,
    LPCWSTR lpName)
{
    HANDLE hMapFile = OpenFileMappingW(
        dwDesiredAccess,
        bInheritHandle,
        lpName);

    if (hMapFile == nullptr)
    {
        Win32Error::throw_when_error();
        return FileMapping();
    }

    return FileMapping(hMapFile);
}

FileMapping FileMapping::Open(
    DWORD dwDesiredAccess,
    BOOL bInheritHandle,
    LPCSTR lpName)
{
    HANDLE hMapFile = OpenFileMappingA(
        dwDesiredAccess,
        bInheritHandle,
        lpName);

    if (hMapFile == nullptr)
    {
        Win32Error::throw_when_error();
        return FileMapping();
    }

    return FileMapping(hMapFile);
}

FileMapping FileMapping::Open(
    DWORD dwDesiredAccess,
    BOOL bInheritHandle,
    std::nullptr_t lpName)
{
    return Open(dwDesiredAccess, bInheritHandle, static_cast<LPCWSTR>(lpName));
}

ViewOfFile FileMapping::MapView(
    DWORD dwDesiredAccess,
    size_t offset,
    SIZE_T dwNumberOfBytesToMap)
{
    return ViewOfFile::Map(
        this->get(),
        dwDesiredAccess,
        offset,
        dwNumberOfBytesToMap);
}
