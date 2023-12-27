/**
 * @file 0028.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 找出字符串中第一个匹配项的下标，简单
 *      https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/description/
 * @version 0.1
 * @date 2023-12-27
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "data_define.h"

class Solution
{
public:
    int strStr(string haystack, string needle)
    {
        int res = -1;
        if (haystack.size() < needle.size()) {
            return -1;
        } else if (haystack.size() == needle.size()) {
            return haystack == needle ? 0 : -1;
        }

        for (int i = 0; i < haystack.size() - needle.size() + 1; i++) {
            if (haystack.substr(i, needle.size()) == needle) {
                res = i;
                break;
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
        output = Solution().strStr(get<0>(input), get<1>(input));
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
        std::tuple<std::string, std::string>,
        int
        >>  testCases = {
        {
            {"c", "caaa"},
            -1,
        },
        {
            {"abc", "c"},
            2,
        },
        {
            {"a", "a"},
            0,
        },
        {
            {"sadbutsad", "sad"},
            0,
        },
        {
            {"leetcode", "leeto"},
            -1,
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
