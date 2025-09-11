#pragma once

#include <Windows.h>
#include <memory>

#include "handle.hpp"

namespace scrambleverse::win32
{
    class Event : public Handle
    {
    public:
        Event() noexcept;
        explicit Event(HANDLE handle) noexcept;

        static Event Create(
            LPSECURITY_ATTRIBUTES lpEventAttributes,
            BOOL bManualReset,
            BOOL bInitialState,
            LPCWSTR lpName);

        static Event Create(
            LPSECURITY_ATTRIBUTES lpEventAttributes,
            BOOL bManualReset,
            BOOL bInitialState,
            LPCSTR lpName);
    };
}
