#include "handle.hpp"
#include "process.hpp"

using namespace scrambleverse::win32;

void internal::DeleteHandle(HANDLE h)
{
    if (h != nullptr && h != INVALID_HANDLE_VALUE)
    {
        CloseHandle(h);
    }
}

Handle::Handle() noexcept = default;
Handle::Handle(HANDLE handle) noexcept : HandleBase(handle) {}

bool Handle::GetHandleInformation(DWORD *lpdwFlags) const noexcept
{
    return ::GetHandleInformation(get(), lpdwFlags);
}

bool Handle::DuplicateHandle(
    Process targetProcess,
    LPHANDLE lpTargetHandle,
    DWORD dwDesiredAccess,
    BOOL bInheritHandle,
    DWORD dwOptions) const noexcept
{
    return ::DuplicateHandle(
        GetCurrentProcess(),
        get(),
        targetProcess.get(),
        lpTargetHandle,
        dwDesiredAccess,
        bInheritHandle,
        dwOptions);
}

Handle::operator bool() const noexcept
{
    return get() != nullptr && get() != INVALID_HANDLE_VALUE;
}
