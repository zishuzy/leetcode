/**
 * @file 0012.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 整数转罗马数字，中等
 *      https://leetcode.cn/problems/integer-to-roman/description/
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
    string intToRoman(int num)
    {
        int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        std::string reps[] = {"M",  "CM", "D",  "CD", "C",  "XC", "L",
                              "XL", "X",  "IX", "V",  "IV", "I"};
        std::string res;

        for (int i = 0; i < 13; i++) {
            while (num >= values[i]) {
                num -= values[i];
                res += reps[i];
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
        output = Solution().intToRoman(input);
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
        std::string
        >>  testCases = {
        {
            3,
            "III",
        },
        {
            4,
            "IV",
        },
        {
            9,
            "IX",
        },
        {
            58,
            "LVIII",
        },
        {
            1994,
            "MCMXCIV",
        },
        {
            3999,
            "MMMCMXCIX",
        },
        {
            999,
            "CMXCIX",
        },
        {
            99,
            "XCIX",
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
