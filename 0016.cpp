/**
 * @file 0016.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 最接近的三数之和，中等
 *      https://leetcode.cn/problems/3sum-closest/description/
 * @version 0.1
 * @date 2023-12-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "data_define.h"

class Solution
{
public:
    int threeSumClosest(vector<int> &nums, int target)
    {
        bool found = false;
        int res = INT_MAX;
        int diff_min = INT_MAX;
        if (nums.size() < 3) {
            return {};
        }

        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size() - 2 && !found; i++) {
            if (i > 0 && nums[i - 1] == nums[i]) {
                continue;
            }
            int l = i + 1;
            int r = nums.size() - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                int diff = abs(sum - target);
                if (diff == 0) {
                    res = sum;
                    found = true;
                    break;
                } else if (sum < target) {
                    if (diff < diff_min) {
                        diff_min = diff;
                        res = sum;
                    }
                    l++;
                    while (l < r && nums[l - 1] == nums[l]) {
                        l++;
                    }
                } else if (sum > target) {
                    if (diff < diff_min) {
                        diff_min = diff;
                        res = sum;
                    }
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
        output = Solution().threeSumClosest(get<0>(input), get<1>(input));
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
        std::tuple<std::vector<int>, int>,
        int
        >>  testCases = {
        {
            {{4,0,5,-5,3,3,0,-4,-5},-2},
            -2,
        },
        {
            {{-1,2,1,-4},1},
            2,
        },
        {
            {{0,0,0},1},
            0,
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
