/**
 * @file 0006.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief N 字形变换，中等
 *      https://leetcode.cn/problems/zigzag-conversion/description/
 * @version 0.1
 * @date 2023-12-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "data_define.h"

class Solution
{
public:
    string convert(string s, int numRows)
    {
        if (numRows == 1)
            return s;

        vector<string> rows(min(numRows, int(s.size())));
        int curRow = 0;
        bool goingDown = false;

        for (char c : s) {
            rows[curRow] += c;
            if (curRow == 0 || curRow == numRows - 1)
                goingDown = !goingDown;
            curRow += goingDown ? 1 : -1;
        }

        string ret;
        for (string row : rows)
            ret += row;
        return ret;
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
        output = Solution().convert(get<0>(input), get<1>(input));
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
        std::tuple<std::string, int>,
        std::string
        >>  testCases = {
        {
            {"PAYPALISHIRING", 3},
            "PAHNAPLSIIGYIR",
        },
        {
            {"PAYPALISHIRING", 4},
            "PINALSIGYAHRPI",
        },
        {
            {"A", 1},
            "A",
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
