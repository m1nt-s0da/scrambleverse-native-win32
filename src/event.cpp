#include "event.hpp"
#include "error.hpp"

using namespace scrambleverse::win32;

Event::Event() noexcept = default;
Event::Event(HANDLE handle) noexcept : Handle(handle) {}

Event Event::Create(
    LPSECURITY_ATTRIBUTES lpEventAttributes,
    BOOL bManualReset,
    BOOL bInitialState,
    LPCWSTR lpName)
{
    HANDLE handle = ::CreateEventW(
        lpEventAttributes,
        bManualReset,
        bInitialState,
        lpName);
    if (handle == nullptr)
    {
        Win32Error::throw_when_error();
        return Event();
    }
    return Event(handle);
}

Event Event::Create(
    LPSECURITY_ATTRIBUTES lpEventAttributes,
    BOOL bManualReset,
    BOOL bInitialState,
    LPCSTR lpName)
{
    HANDLE handle = ::CreateEventA(
        lpEventAttributes,
        bManualReset,
        bInitialState,
        lpName);
    if (handle == nullptr)
    {
        Win32Error::throw_when_error();
        return Event();
    }
    return Event(handle);
}

Event Event::Create(
    LPSECURITY_ATTRIBUTES lpEventAttributes,
    BOOL bManualReset,
    BOOL bInitialState,
    std::nullptr_t lpName)
{
    return Create(lpEventAttributes, bManualReset, bInitialState, static_cast<LPCWSTR>(lpName));
}
