/**
 * @file 0031.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 下一个排列，中等
 *      https://leetcode.cn/problems/next-permutation/description/
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
    void reverse(std::vector<int> &nums, int start)
    {
        int l = start;
        int r = nums.size() - 1;
        while (l < r) {
            swap(nums[l], nums[r]);
            l++;
            r--;
        }
    }

    void nextPermutation(vector<int> &nums)
    {
        if (nums.empty() || nums.size() == 1) {
            return;
        }
        int last = -1;

        for (size_t i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i - 1]) {
                last = i;
            }
        }
        if (last == -1) {
            reverse(nums, 0);
        } else {
            reverse(nums, last);
            for (size_t j = last; j < nums.size(); j++) {
                if (nums[last - 1] < nums[j]) {
                    swap(nums[last - 1], nums[j]);
                    break;
                }
            }
        }
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
        Solution().nextPermutation(input);
        output_ = input;
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
        std::vector<int>,
        std::vector<int>
        >>  testCases = {
        {
            {1,4,3,2,2},
            {2,1,2,3,4},
        },
        {
            {1,2,3},
            {1,3,2},
        },
        {
            {3,2,1},
            {1,2,3},
        },
        {
            {1,1,5},
            {1,5,1},
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
