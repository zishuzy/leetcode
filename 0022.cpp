/**
 * @file 0022.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 括号生成，中等
 *      https://leetcode.cn/problems/generate-parentheses/description/
 * @version 0.1
 * @date 2023-12-24
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "data_define.h"

class Solution
{
public:
    void dfs(int l, int r, int n, std::string &tmp, std::vector<std::string> &res)
    {
        if (r == n) {
            res.push_back(tmp);
            return;
        }
        if (l < n) {
            tmp.push_back('(');
            dfs(l + 1, r, n, tmp, res);
            tmp.pop_back();
        }
        if (r < l) {
            tmp.push_back(')');
            dfs(l, r + 1, n, tmp, res);
            tmp.pop_back();
        }
    }

    vector<string> generateParenthesis(int n)
    {
        std::vector<std::string> res;
        std::string tmp;
        dfs(0, 0, n, tmp, res);
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
        output = Solution().generateParenthesis(input);
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
        std::vector<std::string>
        >>  testCases = {
        {
            3,
            {"((()))","(()())","(())()","()(())","()()()"},
        },
        {
            2,
            {"(())","()()"},
        },
        {
            1,
            {"()"},
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
