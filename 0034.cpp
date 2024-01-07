/**
 * @file 0034.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 在排序数组中查找元素的第一个和最后一个位置，中等
 *      https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/description/
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
    vector<int> searchRange(vector<int> &nums, int target)
    {
        if (nums.empty()) {
            return {-1, -1};
        }
        int l = 0;
        int r = nums.size() - 1;
        int mid = l + (r - l) / 2;
        int res_l = -1, res_r = -1;
        int res_mid = -1;

        while (l <= r) {
            if (nums[mid] == target) {
                if (res_mid == -1) {
                    res_mid = mid;
                }
                res_l = mid;
                r = mid - 1;
            } else if (nums[mid] < target) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
            mid = l + (r - l) / 2;
        }
        if (res_mid != -1) {
            l = res_mid;
            r = nums.size() - 1;
            mid = l + (r - l) / 2;
            while (l <= r) {
                if (nums[mid] == target) {
                    res_r = mid;
                    l = mid + 1;
                } else if (nums[mid] < target) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
                mid = l + (r - l) / 2;
            }
        }

        return {res_l, res_r};
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
        output_ = Solution().searchRange(get<0>(input), get<1>(input));
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
        std::tuple<std::vector<int>, int>,
        std::vector<int>
        >>  testCases = {
        {
            {{1,2,3,4,8,8,8,8,8,8,8,8,8,8,9,10,11},8},
            {4,13},
        },
        {
            {{5,7,7,8,8,10},8},
            {3,4},
        },
        {
            {{5,7,7,8,8,10},6},
            {-1,-1},
        },
        {
            {{1},0},
            {-1,-1},
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
