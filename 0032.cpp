/**
 * @file 0032.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 最长有效括号，困难
 *      https://leetcode.cn/problems/longest-valid-parentheses/
 * @version 0.1
 * @date 2024-01-07
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "data_define.h"

class Solution
{
public:
    int longestValidParentheses(string s)
    {
        if (s.empty()) {
            return 0;
        }
        std::vector<int> arr(s.size(), -1);
        std::stack<int> stk;
        int cnt = 0;
        int res = 0;

        for (std::size_t i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                stk.push(i);
            } else {
                if (!stk.empty()) {
                    int idx = stk.top();
                    stk.pop();
                    arr[idx] = i;
                    arr[i] = idx;
                }
            }
        }
        for (std::size_t i = 0; i < arr.size();) {
            if (arr[i] < 0) {
                res = max(res, cnt);
                cnt = 0;
                i++;
                continue;
            } else {
                cnt += (arr[i] - i + 1);
                i = arr[i] + 1;
            }
        }
        res = max(res, cnt);

        return res;
    }
};

template <typename _Tin, typename _Tout>
class CCase
{
public:
    CCase(_Tin input, _Tout expected)
        : input_(input)
        , expected_(expected)
    {
        output_ = Solution().longestValidParentheses(input);
    }
    bool IsOk() { return IsEqual(output_, expected_); }

    _Tin input_;
    _Tout output_;
    _Tout expected_;
};

TEST(Solution, leetcode)
{
    // clang-format off
    std::vector<CCase<
        std::string,
        int
        >>  testCases = {
        {
            ")()())",
            4,
        },
        {
            "(())",
            4,
        },
        {
            "()(()",
            2,
        },
        {
            "(()",
            2,
        },
        {
            "",
            0,
        },
        {
            "",
            0,
        },

    };
    // clang-format on

    for (auto item : testCases) {
        EXPECT_TRUE(item.IsOk()) << "\ninput:   " << GetString(item.input_)
                                 << "\nouput:   " << GetString(item.output_)
                                 << "\nexpected:" << GetString(item.expected_);
    }
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
