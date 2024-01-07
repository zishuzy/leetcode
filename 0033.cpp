/**
 * @file 0033.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 搜索旋转排序数组，中等
 *      https://leetcode.cn/problems/search-in-rotated-sorted-array/
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
    int search(vector<int> &nums, int target)
    {
        int l = 0;
        int r = nums.size() - 1;
        int mid = l + (r - l) / 2;
        int res = -1;

        while (l <= r) {
            if (nums[mid] == target) {
                res = mid;
                break;
            }
            if (nums[l] < nums[r]) {
                if (nums[mid] < target) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            } else {
                if (nums[mid] < nums[r]) { // right
                    if (nums[mid] < target) {
                        if (nums[r] < target) {
                            r = mid - 1;
                        } else {
                            l = mid + 1;
                        }
                    } else {
                        r = mid - 1;
                    }
                } else { // left
                    if (nums[mid] > target) {
                        if (nums[l] > target) {
                            l = mid + 1;
                        } else {
                            r = mid - 1;
                        }
                    } else {
                        l = mid + 1;
                    }
                }
            }
            mid = l + (r - l) / 2;
        }
        return res;
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
        output_ = Solution().search(get<0>(input), get<1>(input));
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
        int
        >>  testCases = {
        {
            {{4,5,6,7,8,9,10,11,-3,-2,-1,0,1,2},4},
            0,
        },
        {
            {{4,5,6,7,0,1,2},0},
            4,
        },
        {
            {{4,5,6,7,0,1,2},3},
            -1,
        },
        {
            {{1},0},
            -1,
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
