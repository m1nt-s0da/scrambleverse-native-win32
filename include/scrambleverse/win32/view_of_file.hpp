#pragma once

#include <Windows.h>
#include <memory>
#include <cinttypes>

#include "handle.hpp"
#include "handle_base.hpp"

namespace scrambleverse::win32
{
    namespace internal {
        void UnmapViewOfFile(LPVOID lpBaseAddress);
    };

    class ViewOfFile : public HandleBase<LPVOID, internal::UnmapViewOfFile, nullptr>
    {
    public:
        ViewOfFile() noexcept;
        explicit ViewOfFile(LPVOID ptr, bool auto_close = true) noexcept;

        static ViewOfFile Map(
            HANDLE hFileMappingObject,
            DWORD dwDesiredAccess,
            size_t offset,
            SIZE_T dwNumberOfBytesToMap);

        void *ptr(size_t offset = 0) const noexcept;

        template <typename T>
        T *ptr(size_t offset = 0) const noexcept
        {
            return static_cast<T*>(ptr(offset));
        }
    };

}
