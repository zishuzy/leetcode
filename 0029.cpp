/**
 * @file 0029.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 两数相除，中等
 *      https://leetcode.cn/problems/divide-two-integers/description/
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
    int divide(int dividend, int divisor)
    {
        int res = 0;
        int sign = 0;
        if (dividend < 0) {
            if (divisor > 0) {
                sign = 0;
                divisor = -divisor;
            } else {
                sign = 1;
            }
        } else {
            if (divisor > 0) {
                sign = 1;
                divisor = -divisor;
            } else {
                sign = 0;
            }
            dividend = -dividend;
        }
        if (divisor == -1 || divisor == 1) {
            res = dividend;
        } else {
            std::vector<std::pair<int, int>> tb;
            int dd = -1;
            int dr = divisor;
            tb.push_back({dr, dd});
            while (dr >= -(1 << 30)) {
                dr += dr;
                dd += dd;
                tb.push_back({dr, dd});
            }

            for (int i = tb.size() - 1; i >= 0; i--) {
                if (tb[i].first >= dividend) {
                    dividend -= tb[i].first;
                    res += tb[i].second;
                }
            }
        }

        if (sign > 0) {
            if (res == INT_MIN) {
                res = INT_MAX;
            } else {
                res = -res;
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
        output = Solution().divide(get<0>(input), get<1>(input));
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
        std::tuple<int, int>,
        int
        >>  testCases = {
        {
            {-2147483648, -1},
            2147483647,
        },
        {
            {10, 3},
            3,
        },
        {
            {7, -3},
            -2,
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
