#include <gtest/gtest.h>
#include <Windows.h>

#include "scrambleverse/win32/file_mapping.hpp"
#include "scrambleverse/win32/error.hpp"
#include "scrambleverse/win32/view_of_file.hpp"

using namespace scrambleverse::win32;

TEST(FileMappingTest, Create)
{
    auto fileMapping = FileMapping::Create(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 1024 * 1024, nullptr);
    EXPECT_TRUE(static_cast<bool>(fileMapping));
}

TEST(FileMappingTest, Open_NonExistent)
{
    try
    {
        auto fileMapping = FileMapping::Open(FILE_MAP_READ, FALSE, L"NonExistentMapping");
    }
    catch (Win32Error &e)
    {
        EXPECT_EQ(e.code(), ERROR_FILE_NOT_FOUND);
        return;
    }
}

TEST(FileMappingTest, Open_Existing)
{
    auto createdMapping = FileMapping::Create(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 1024 * 1024, L"TestMapping");
    ASSERT_TRUE(static_cast<bool>(createdMapping));

    auto openedMapping = FileMapping::Open(FILE_MAP_READ, FALSE, L"TestMapping");
    EXPECT_TRUE(static_cast<bool>(openedMapping));
}

TEST(FileMappingTest, MapView)
{
    auto fileMapping = FileMapping::Create(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 1024 * 1024, nullptr);
    ASSERT_TRUE(static_cast<bool>(fileMapping));

    auto view = fileMapping.MapView(FILE_MAP_WRITE, 0, 1024);
    EXPECT_TRUE(static_cast<bool>(view));
    EXPECT_NE(view.ptr(), nullptr);
}
