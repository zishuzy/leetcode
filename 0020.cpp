/**
 * @file 0020.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 有效的括号，简单
 *      https://leetcode.cn/problems/valid-parentheses/
 * @version 0.1
 * @date 2023-12-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "data_define.h"

class Solution
{
public:
    bool isValid(string s)
    {
        int len = s.size();
        bool res = true;
        std::stack<char> stk;

        for (int i = 0; i < len; i++) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
                stk.push(s[i]);
            } else {
                if (stk.empty()) {
                    res = false;
                    break;
                } else if (s[i] == ')' && stk.top() != '(') {
                    res = false;
                    break;
                } else if (s[i] == ']' && stk.top() != '[') {
                    res = false;
                    break;
                } else if (s[i] == '}' && stk.top() != '{') {
                    res = false;
                    break;
                }
                stk.pop();
            }
        }

        return res ? stk.empty() : false;
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
        output = Solution().isValid(input);
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
        bool
        >>  testCases = {
        {
            "([)]",
            false,
        },
        {
            "()",
            true,
        },
        {
            "()[]{}",
            true,
        },
        {
            "(}",
            false,
        },
        {
            "((((((((()))))))))[]}",
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
