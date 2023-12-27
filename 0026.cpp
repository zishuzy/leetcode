/**
 * @file 0026.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 删除有序数组中的重复项，简单
 *      https://leetcode.cn/problems/remove-duplicates-from-sorted-array/description/
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
    int removeDuplicates(vector<int> &nums)
    {
        if (nums.empty()) {
            return 0;
        }
        int prev, len = 1;
        prev = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == prev) {
                continue;
            }
            nums[len++] = nums[i];
            prev = nums[i];
        }

        if (len != nums.size()) {
            nums.erase(nums.begin() + len, nums.end());
        }

        return len;
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
        output = Solution().removeDuplicates(input);
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
            {0,0,1,1,1,2,2,3,3,4},
            5,
        },
        {
            {1,1,2},
            2,
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
