/**
 * @file 0001.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 两数之和，简单，https://leetcode.cn/problems/two-sum/description
 * @version 0.1
 * @date 2023-12-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "data_define.h"

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> map_num;
        vector<int> result;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            auto p = map_num.find(target - nums[i]);
            if (p != map_num.end()) {
                result.push_back(p->second);
                result.push_back(i);
                break;
            }
            map_num[nums[i]] = i;
        }
        return result;
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
        output = Solution().twoSum(get<0>(input), get<1>(input));
    }
    bool IsOk() { return output == expected; }

    _Tin input;
    _Tout output;
    _Tout expected;
};

TEST(Solution, leetcode)
{
    // clang-format off
    std::vector<CCase<
        std::tuple<std::vector<int>, int>, 
        std::vector<int>
        >>  testCases = {
        {
            {{2,7,11,15}, 9}, 
            {0, 1},
        },
        {
            {{3,2,4}, 6}, 
            {1, 2},
        },
        {
            {{3,3}, 6}, 
            {0, 1},
        },
    };
    // clang-format on

    for (auto item : testCases) {
        EXPECT_TRUE(item.IsOk()) << "\ninput:\n"
                                 << GetString(item.input) << "\nouput:\n"
                                 << GetString(item.output) << "\nexpected:\n"
                                 << GetString(item.expected);
    }
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
