#pragma once

#include <Windows.h>

#include "handle.hpp"

namespace scrambleverse::win32
{
    class Process : public Handle
    {
    public:
        Process() noexcept;
        explicit Process(HANDLE handle) noexcept;

        static Process Current() noexcept;

        static Process Open(
            DWORD dwDesiredAccess,
            BOOL bInheritHandle,
            DWORD dwProcessId);
    };
}
