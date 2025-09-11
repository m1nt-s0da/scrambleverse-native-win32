#include "error.hpp"

using scrambleverse::win32::Win32Error;

class Win32ErrorImpl : public Win32Error
{
private:
    DWORD errorCode;
    std::string message_;

public:
    explicit Win32ErrorImpl(DWORD errorCode, const std::string &message)
        : Win32Error(errorCode, message), errorCode(errorCode), message_(message) {};

    DWORD code() const noexcept override
    {
        return errorCode;
    }

    const std::string &message() const noexcept override
    {
        return message_;
    }
};

std::string format_message(DWORD err)
{
    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        err,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&messageBuffer,
        0,
        NULL);

    if (size != 0 && messageBuffer != nullptr)
    {
        std::string message(messageBuffer, size);
        LocalFree(messageBuffer);
        return message;
    }
    else
    {
        return "Unknown error";
    }
}

Win32Error::Win32Error(DWORD code, const std::string &message)
    : std::system_error(static_cast<int>(code), std::system_category(), message) {}

void Win32Error::throw_when_error()
{
    DWORD err = GetLastError();
    throw_when_error(err);
}

void Win32Error::throw_when_error(DWORD err)
{
    if (err != ERROR_SUCCESS)
    {
        auto msg = format_message(err);
        throw Win32ErrorImpl(err, msg);
    }
}
