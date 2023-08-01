#include <iostream>
#define WORD (4096)

#include <gtest/gtest.h>

// g++ main.cpp -lgtest -lgtest_main -lpthread

size_t AlignMemory(size_t size)
{
    return (size % WORD) ? ((size - (size % WORD)) + WORD) : size;
}

TEST(AlignMemory, Test1) 
{
    ASSERT_TRUE(AlignMemory(20480) == 20480);
    ASSERT_TRUE(AlignMemory(4096) == WORD);
    ASSERT_TRUE(AlignMemory(40960) == 40960);
    ASSERT_TRUE(AlignMemory(40900) == 40960);
    ASSERT_TRUE(AlignMemory(4095) == 4096);
}

int main() 
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}