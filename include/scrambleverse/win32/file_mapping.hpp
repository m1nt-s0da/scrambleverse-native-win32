#pragma once

#include <Windows.h>
#include <memory>

#include "handle.hpp"

namespace scrambleverse::win32
{
    class ViewOfFile;

    class FileMapping : public Handle
    {
    public:
        FileMapping() noexcept;
        explicit FileMapping(HANDLE handle) noexcept;

        static FileMapping Create(
            HANDLE hFile,
            LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
            DWORD flProtect,
            size_t maximumSize,
            LPCWSTR lpName);

        static FileMapping Create(
            HANDLE hFile,
            LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
            DWORD flProtect,
            size_t maximumSize,
            LPCSTR lpName);

        static FileMapping Create(
            HANDLE hFile,
            LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
            DWORD flProtect,
            size_t maximumSize,
            std::nullptr_t lpName);

        static FileMapping Open(
            DWORD dwDesiredAccess,
            BOOL bInheritHandle,
            LPCWSTR lpName);

        static FileMapping Open(
            DWORD dwDesiredAccess,
            BOOL bInheritHandle,
            LPCSTR lpName);

        static FileMapping Open(
            DWORD dwDesiredAccess,
            BOOL bInheritHandle,
            std::nullptr_t lpName);

        ViewOfFile MapView(
            DWORD dwDesiredAccess,
            size_t offset,
            SIZE_T dwNumberOfBytesToMap);
    };
}
