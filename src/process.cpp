#include <windows.h>

#include "scrambleverse/win32/process.hpp"
#include "scrambleverse/win32/error.hpp"

using namespace scrambleverse::win32;

Process::Process() noexcept = default;
Process::Process(HANDLE handle) noexcept : Handle(handle) {}

Process Process::Current() noexcept
{
    return Process(GetCurrentProcess());
}

Process Process::Open(
    DWORD dwDesiredAccess,
    BOOL bInheritHandle,
    DWORD dwProcessId)
{
    HANDLE hProcess = ::OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
    if (hProcess == nullptr)
    {
        Win32Error::throw_when_error();
        return Process();
    }
    return Process(hProcess);
}
