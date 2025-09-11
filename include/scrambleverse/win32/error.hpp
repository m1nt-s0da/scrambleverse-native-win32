#pragma once

#include <Windows.h>
#include <stdexcept>
#include <system_error>
#include <string>
#include <memory>

namespace scrambleverse::win32
{
    class Win32Error : public std::system_error
    {
    public:
        explicit Win32Error(DWORD code, const std::string &message);

        virtual DWORD code() const noexcept = 0;
        virtual const std::string &message() const noexcept = 0;

        static void throw_when_error() noexcept(false);
        static void throw_when_error(DWORD err) noexcept(false);
    };
}
