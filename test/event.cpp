#include <gtest/gtest.h>
#include <Windows.h>

#include "scrambleverse/win32/event.hpp"

using namespace scrambleverse::win32;

TEST(EventTest, Create)
{
    auto event = Event::Create(nullptr, TRUE, FALSE, nullptr);
    EXPECT_TRUE(static_cast<bool>(event));
}
