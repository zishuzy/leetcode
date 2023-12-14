/**
 * @file 0007.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 整数反转，中等
 *      https://leetcode.cn/problems/reverse-integer/
 * @version 0.1
 * @date 2023-12-14
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "data_define.h"

class Solution
{
public:
    int reverse(int x)
    {
        int res = 0;
        int tmp = 0;

        while (x) {
            tmp = x % 10;
            if (res > INT_MAX / 10 || res < INT_MIN / 10) {
                res = 0;
                break;
            }
            res = res * 10 + tmp;
            x /= 10;
        }
        return res;
    }
};

template <typename _Tin, typename _Tout>
class CCase
{
public:
    CCase(_Tin input, _Tout expected)
        : input(input)
        , expected(expected)
    {
        output = Solution().reverse(input);
    }
    bool IsOk() { return IsEqual(output, expected); }

    _Tin input;
    _Tout output;
    _Tout expected;
};

TEST(Solution, leetcode)
{
    // clang-format off
    std::vector<CCase<
        int,
        int
        >>  testCases = {
        {
            123,
            321,
        },
        {
            -123,
            -321,
        },
        {
            0,
            0,
        },
        {
            1534236469,
            0,
        },
    };

    // clang-format on

    for (auto item : testCases) {
        EXPECT_TRUE(item.IsOk()) << "\ninput:   " << GetString(item.input)
                                 << "\nouput:   " << GetString(item.output)
                                 << "\nexpected:" << GetString(item.expected);
    }
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
