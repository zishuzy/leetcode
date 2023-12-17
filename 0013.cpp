/**
 * @file 0013.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 罗马数字转整数，简单
 *      https://leetcode.cn/problems/roman-to-integer/
 * @version 0.1
 * @date 2023-12-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "data_define.h"

class Solution
{
public:
    int romanToInt(string s)
    {
        int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        std::string reps[] = {"M",  "CM", "D",  "CD", "C",  "XC", "L",
                              "XL", "X",  "IX", "V",  "IV", "I"};
        int idx = 0;
        int res = 0;

        for (int i = 0; i < 13; i++) {
            while (s.substr(idx, reps[i].size()) == reps[i]) {
                res += values[i];
                idx += reps[i].size();
            }
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
        output = Solution().romanToInt(input);
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
        std::string,
        int
        >>  testCases = {
        {
            "III",
            3,
        },
        {
            "IV",
            4,
        },
        {
            "IX",
            9,
        },
        {
            "LVIII",
            58,
        },
        {
            "MCMXCIV",
            1994,
        },
        {
            "MMMCMXCIX",
            3999,
        },
        {
            "CMXCIX",
            999,
        },
        {
            "XCIX",
            99,
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
