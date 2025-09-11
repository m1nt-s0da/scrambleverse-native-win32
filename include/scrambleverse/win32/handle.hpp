#pragma once

#include <Windows.h>
#include <memory>
#include "handle_base.hpp"

namespace scrambleverse::win32
{
    namespace internal {
        void DeleteHandle(HANDLE h);
    }

    class Process;

    /// @brief 現在のプロセス上のハンドルを表します。
    class Handle : public HandleBase<HANDLE, internal::DeleteHandle, nullptr>
    {
    public:
        Handle() noexcept;
        explicit Handle(HANDLE handle) noexcept;


        bool GetHandleInformation(DWORD *lpdwFlags) const noexcept;

        bool DuplicateHandle(
            Process targetProcess,
            LPHANDLE lpTargetHandle,
            DWORD dwDesiredAccess,
            BOOL bInheritHandle,
            DWORD dwOptions) const noexcept;

        explicit operator bool() const noexcept;
    };
}
