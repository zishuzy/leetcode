/**
 * @file 0018.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 四数之和，中等
 *      https://leetcode.cn/problems/4sum/description/
 * @version 0.1
 * @date 2023-12-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "data_define.h"

class Solution
{
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        std::vector<std::vector<int>> res;
        if (nums.size() < 4) {
            return res;
        }

        std::sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size() - 3; i++) {
            if (i > 0 && nums[i - 1] == nums[i]) {
                continue;
            }
            int t = target - nums[i];
            for (int j = i + 1; j < nums.size() - 2; j++) {
                if (j > i + 1 && nums[j - 1] == nums[j]) {
                    continue;
                }

                int l = j + 1;
                int r = nums.size() - 1;
                while (l < r) {
                    long sum = (long)nums[j] + (long)nums[l] + (long)nums[r];
                    if (sum == t) {
                        res.push_back({nums[i], nums[j], nums[l], nums[r]});
                        l++;
                        r--;
                        while (l < r && nums[l - 1] == nums[l]) {
                            l++;
                        }
                        while (l < r && nums[r] == nums[r + 1]) {
                            r--;
                        }
                    } else if (sum < t) {
                        l++;
                        while (l < r && nums[l - 1] == nums[l]) {
                            l++;
                        }
                    } else if (sum > t) {
                        r--;
                        while (l < r && nums[r] == nums[r + 1]) {
                            r--;
                        }
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
        output = Solution().fourSum(get<0>(input), get<1>(input));
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
        std::vector<std::vector<int>>
        >>  testCases = {
        {
            {{1,0,-1,0,-2,2}, 0},
            {{-2,-1,1,2},{-2,0,0,2},{-1,0,0,1}},
        },
        {
            {{2,2,2,2,2}, 8},
            {{2,2,2,2}},
        },
        {
            {{1000000000,1000000000,1000000000,1000000000}, 0},
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
