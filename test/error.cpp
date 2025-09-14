#include <gtest/gtest.h>
#include <Windows.h>

#include "scrambleverse/win32/error.hpp"

TEST(Win32ErrorTest, Throw)
{
    SetLastError(ERROR_FILE_NOT_FOUND);
    try
    {
        scrambleverse::win32::Win32Error::throw_when_error();
        FAIL() << "Expected Win32Error to be thrown";
    }
    catch (const scrambleverse::win32::Win32Error &e)
    {
        EXPECT_EQ(e.code(), ERROR_FILE_NOT_FOUND);
        EXPECT_NE(e.message(), "");
    }
    catch (...)
    {
        FAIL() << "Expected Win32Error, but caught different exception";
    }
}

TEST(Win32ErrorTest, NoThrow)
{
    SetLastError(ERROR_SUCCESS);
    try
    {
        scrambleverse::win32::Win32Error::throw_when_error();
    }
    catch (...)
    {
        FAIL() << "Did not expect any exception to be thrown";
    }
}
