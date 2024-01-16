/**
 * @file 0038.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 外观数列，中等
 *      https://leetcode.cn/problems/count-and-say/description/
 * @version 0.1
 * @date 2024-01-16
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "data_define.h"

class Solution
{
public:
    string countAndSay(int n)
    {
        std::string s = "1";
        for (int i = 1; i < n; i++) {
            std::string tmp;
            char c = s[0];
            int count = 1;

            tmp.swap(s);

            for (int j = 1; j < tmp.size(); j++) {
                if (tmp[j] == c) {
                    count++;
                } else {
                    s += std::to_string(count) + c;
                    c = tmp[j];
                    count = 1;
                }
            }
            if (count != 0) {
                s += std::to_string(count) + c;
            }
        }

        return s;
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
        output_ = Solution().countAndSay(input);
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
        int,
        std::string
        >>  testCases = {
        {
            4,
            "1211",
        },
        {
            1,
            "1",
        },
        {
            12,
            "3113112221232112111312211312113211",
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
