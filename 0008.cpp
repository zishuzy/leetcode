/**
 * @file 0008.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 字符串转换整数 (atoi)，中等
 *      https://leetcode.cn/problems/string-to-integer-atoi/description/
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
    int myAtoi(string s)
    {
        size_t len = s.size();
        int res = 0;
        std::string::size_type i;
        int tmp;
        bool sign = true;

        if (s.empty()) {
            return 0;
        }
        i = s.find_first_not_of(' ');
        if (i == std::string::npos) {
            return 0;
        }
        if (s[i] == '-') {
            sign = false;
            i++;
        } else if (s[i] == '+') {
            sign = true;
            i++;
        }

        for (; i < len; i++) {
            if (s[i] < '0' || s[i] > '9') {
                break;
            }
            tmp = s[i] - '0';
            if (res > INT_MAX / 10 || (res == INT_MAX / 10 && tmp > 7)) {
                res = INT_MAX;
                break;
            } else if (res < INT_MIN / 10 || (res == INT_MIN / 10 && tmp > 8)) {
                res = INT_MIN;
                break;
            }
            if (sign) {
                res = res * 10 + (s[i] - '0');
            } else {
                res = res * 10 - (s[i] - '0');
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
        output = Solution().myAtoi(input);
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
            "42",
            42,
        },
        {
            "   -42",
            -42,
        },
        {
            "4193 with words",
            4193,
        },
        {
            "    ",
            0,
        },
        {
            "2147483647",
            2147483647,
        },
        {
            "2147483648",
            2147483647,
        },
        {
            "-2147483648",
            -2147483648,
        },
        {
            "-2147483649",
            -2147483648,
        },
        {
            "-91283472332",
            -2147483648,
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
