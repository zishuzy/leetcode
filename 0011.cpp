/**
 * @file 0011.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 盛最多水的容器，中等
 *      https://leetcode.cn/problems/container-with-most-water/description/
 * @version 0.1
 * @date 2023-12-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "data_define.h"

class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        int l = 0;
        int r = height.size() - 1;
        int res = 0;

        while (l < r) {
            if (height[l] < height[r]) {
                res = max(res, height[l] * (r - l));
                l++;
            } else {
                res = max(res, height[r] * (r - l));
                r--;
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
        output = Solution().maxArea(input);
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
        std::vector<int>,
        int
        >>  testCases = {
        {
            {1,8,6,2,5,4,8,3,7},
            49,
        },
        {
            {1,1},
            1,
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
