#include <gtest/gtest.h>
#include <Windows.h>

#include "scrambleverse/win32/process.hpp"
#include "scrambleverse/win32/error.hpp"

using namespace scrambleverse::win32;

TEST(ProcessTest, Open)
{
    auto currentProcessId = GetCurrentProcessId();
    auto process = Process::Open(PROCESS_QUERY_INFORMATION, FALSE, currentProcessId);
    EXPECT_TRUE(static_cast<bool>(process));
}

TEST(ProcessTest, Open_NonExistent)
{
    try
    {
        auto process = Process::Open(PROCESS_QUERY_INFORMATION, FALSE, 0xFFFFFFFF);
    }
    catch (Win32Error &e)
    {
        EXPECT_EQ(e.code(), ERROR_INVALID_PARAMETER);
        return;
    }
}

TEST(ProcessTest, Current)
{
    auto proc = GetCurrentProcess();
    auto process = Process::Current();
    EXPECT_EQ(process.get(), proc);
}
