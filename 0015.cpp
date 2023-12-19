/**
 * @file 0015.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 三数之和，中等
 *      https://leetcode.cn/problems/3sum/
 * @version 0.1
 * @date 2023-12-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "data_define.h"

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        std::vector<std::vector<int>> res;
        if (nums.size() < 3) {
            return {};
        }

        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size() - 2; i++) {
            if (i > 0 && nums[i - 1] == nums[i]) {
                continue;
            }
            int l = i + 1;
            int r = nums.size() - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (sum == 0) {
                    res.push_back({nums[i], nums[l], nums[r]});
                    l++;
                    r--;
                    while (l < r && nums[l - 1] == nums[l]) {
                        l++;
                    }
                    while (l < r && nums[r] == nums[r + 1]) {
                        r--;
                    }
                } else if (sum < 0) {
                    l++;
                    while (l < r && nums[l - 1] == nums[l]) {
                        l++;
                    }
                } else if (sum > 0) {
                    r--;
                    while (l < r && nums[r] == nums[r + 1]) {
                        r--;
                    }
                }
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
        output = Solution().threeSum(input);
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
        std::vector<std::vector<int>>
        >>  testCases = {
        {
            {0,0,0,0},
            {{0,0,0}},
        },
        {
            {-2,-1,-1,-1,0,3,3},
            {{-2,-1,3}},
        },
        {
            {-1,0,1,2,-1,-4},
            {{-1,-1,2},{-1,0,1}},
        },
        {
            {0,1,1},
            {},
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
