/**
 * @file 0027.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 移除元素，简单
 *      https://leetcode.cn/problems/remove-element/description/
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
    int removeElement(vector<int> &nums, int val)
    {
        if (nums.empty()) {
            return 0;
        }
        int len = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (val == nums[i]) {
                continue;
            }
            nums[len] = nums[i];
            len++;
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
        output = Solution().removeElement(get<0>(input), get<1>(input));
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
            {{3,2,2,3}, 3},
            2,
        },
        {
            {{0,1,2,2,3,0,4,2}, 2},
            5,
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
