/**
 * @file 0005.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 最长回文子串，中等
 *      https://leetcode.cn/problems/longest-palindromic-substring/
 * @version 0.1
 * @date 2023-12-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "data_define.h"

class Solution
{
public:
    string longestPalindrome(string s)
    {
        int len = (int)s.length();
        int left = 0;
        int right = 0;
        int leftres = 0;
        int maxlen = 0;

        int i = 0;
        while (i < len) {
            left = i;
            right = i;
            while (right + 1 < len && s[right] == s[right + 1])
                ++right;
            i = right + 1;
            while (left >= 0 && right < len && s[left] == s[right]) {
                --left;
                ++right;
            }
            if (maxlen < right - left - 1) {
                leftres = left + 1;
                maxlen = right - left - 1;
            }
        }
        return s.substr(leftres, maxlen);
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
        output = Solution().longestPalindrome(input);
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
        std::string
        >>  testCases = {
        {
            "bananas",
            "anana",
        },
        {
            "a",
            "a",
        },
        {
            "babad",
            "bab",
        },
        {
            "cbbd",
            "bb",
        },
        {
            "abbbbbb",
            "bbbbbb",
        },
        {
            "acbbbbbbcddd",
            "cbbbbbbc",
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
