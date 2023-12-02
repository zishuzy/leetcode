/**
 * @file 0003.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 无重复字符的最长子串，中等
 *      https://leetcode.cn/problems/longest-substring-without-repeating-characters/
 * @version 0.1
 * @date 2023-12-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "data_define.h"

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int bucket[256] = {0};
        int idx = 0, ss = 0;
        int len_max = 0;

        for (int i = 0; i < s.size(); i++) {
            idx = s[i] % 256;
            if (bucket[idx] == 0) {
                len_max = max(len_max, i - ss + 1);
            } else {
                for (int j = ss; j < bucket[idx] - 1; j++) {
                    bucket[s[j] % 256] = 0;
                }
                ss = bucket[idx];
            }
            bucket[idx] = i + 1;
        }

        return len_max;
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
        output = Solution().lengthOfLongestSubstring(input);
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
            "tmamzuxt",
            6,
        },
        {
            "abcabcbb",
            3,
        },
        {
            "bbbbb",
            1,
        },
        {
            "pwwkew",
            3,
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
