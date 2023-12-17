/**
 * @file 00010.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 正则表达式匹配，困难
 *      https://leetcode.cn/problems/regular-expression-matching/description/
 * @version 0.1
 * @date 2023-12-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "data_define.h"

class Solution
{
public:
    bool isMatch(string s, string p)
    {
        s = " " + s;
        p = " " + p;
        int m = s.size();
        int n = p.size();
        std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));
        dp[0][0] = true;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (s[i] == p[j] || p[j] == '.') {
                    dp[i + 1][j + 1] = dp[i][j];
                } else if (p[j] == '*') {
                    if (s[i] == p[j - 1] || p[j - 1] == '.') {
                        dp[i + 1][j + 1] = dp[i + 1][j - 1] || dp[i + 1][j] || dp[i][j + 1];
                    } else {
                        dp[i + 1][j + 1] = dp[i + 1][j - 1];
                    }
                }
            }
        }

        return dp[m][n];
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
        output = Solution().isMatch(get<0>(input), get<1>(input));
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
        bool
        >>  testCases = {
        {
            {"cbab", ".*b"},
            true,
        },
        {
            {"aab", "c*a*b"},
            true,
        },
        {
            {"ab", ".*"},
            true,
        },
        {
            {"aa", "a*"},
            true,
        },
        {
            {"aa", "a"},
            false,
        },
        {
            {"cb", ".*b"},
            true,
        },
        {
            {"ccccb", "c*b"},
            true,
        },
        {
            {"cccca", "c*b"},
            false,
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
