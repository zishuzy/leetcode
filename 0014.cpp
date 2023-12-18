/**
 * @file 0014.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 最长公共前缀，简单
 *      https://leetcode.cn/problems/longest-common-prefix/description/
 * @version 0.1
 * @date 2023-12-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "data_define.h"

class Solution
{
public:
    string longestCommonPrefix(vector<string> &strs)
    {
        std::string res;
        int len = strs.size();
        if (strs.empty()) {
            return res;
        }
        res = strs[0];

        for (int i = 1; i < len && !res.empty(); i++) {
            if (strs[i].empty()) {
                res = "";
                break;
            }
            int j = 0;
            for (j = 0; j < res.size() && j < strs[i].size(); j++) {
                if (res[j] != strs[i][j]) {
                    break;
                }
            }
            res.erase(j);
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
        output = Solution().longestCommonPrefix(input);
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
        std::vector<std::string>,
        std::string
        >>  testCases = {
        {
            {"flower","flow","flight"},
            "fl",
        },
        {
            {"dog","racecar","car"},
            "",
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
