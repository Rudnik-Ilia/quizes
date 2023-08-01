#include <iostream>
#include <cstring>
#include <gtest/gtest.h>

bool CheckIfedit(char *str1, char *str2)
{
    int m = strlen(str1);
    int n = strlen(str2);
    int j = 0;
    int i = 0;
    int count = 0;

    if(abs(m - n) > 1)
    {
        return false;
    }

    while(i < m && j < n)
    {
        if(str1[i] != str2[j])
        {
            if(count == 1)
            {
                return false;
            }
            if(m > n)
            {
                ++i;
            }
            if(m < n)
            {
                ++j;
            }
            else
            {
                ++i;
                ++j;
            }
            ++count;
        }
        else
        {
            ++i;
            ++j;
        }
    }
    if(i < m || j < n)
    {
        ++count;
    }
    return (count == 1);
}

TEST(CheckIfedit, positive1)
{
    ASSERT_EQ(true, CheckIfedit("ABOC", "ABC"));
}

TEST(CheckIfedit, positive2)
{
    ASSERT_EQ(true, CheckIfedit("ABCE", "ABC"));
}

TEST(CheckIfedit, positive3)
{
    ASSERT_EQ(true, CheckIfedit("ABC", "ABCE"));
}

TEST(CheckIfedit, positive4)
{
    ASSERT_EQ(true, CheckIfedit("ABEC", "ABC"));
}

TEST(CheckIfedit, positive5)
{
    ASSERT_EQ(true, CheckIfedit("ABC", "EABC"));
}

TEST(CheckIfedit, negative1)
{
    ASSERT_EQ(false, CheckIfedit("ABC", "ABCEE"));
}

TEST(CheckIfedit, negative2)
{
    ASSERT_EQ(false, CheckIfedit("ABECcc", "ABC"));
}

TEST(CheckIfedit, negative3)
{
    ASSERT_EQ(false, CheckIfedit("ABBBC", "EABC"));
}


int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}