/**
 * @file 0004.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 寻找两个正序数组的中位数，困难
 *      https://leetcode.cn/problems/median-of-two-sorted-arrays/description/
 * @version 0.1
 * @date 2023-12-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "data_define.h"

class Solution
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        if (nums1.empty() && nums2.empty()) {
            return 0;
        }

        int mid1, mid2, mid_idx1, mid_idx2;
        int idx1 = 0, idx2 = 0, idx = 0;
        int len = nums1.size() + nums2.size();
        vector<int> *nums;
        int *pidx;

        mid_idx2 = len / 2;
        if (len % 2 == 1) {
            mid_idx1 = mid_idx2;
        } else {
            mid_idx1 = mid_idx2 - 1;
        }

        if (nums1.empty()) {
            return (nums2[mid_idx1] + nums2[mid_idx2]) / 2.0;
        } else if (nums2.empty()) {
            return (nums1[mid_idx1] + nums1[mid_idx2]) / 2.0;
        }

        while (idx <= mid_idx2) {
            if (idx1 < nums1.size() && idx2 < nums2.size()) {
                if (nums1[idx1] < nums2[idx2]) {
                    nums = &nums1;
                    pidx = &idx1;
                } else {
                    nums = &nums2;
                    pidx = &idx2;
                }
            } else if (idx1 < nums1.size()) {
                nums = &nums1;
                pidx = &idx1;
            } else if (idx2 < nums2.size()) {
                nums = &nums2;
                pidx = &idx2;
            }
            if (idx == mid_idx1) {
                mid1 = (*nums)[*pidx];
            }
            if (idx == mid_idx2) {
                mid2 = (*nums)[*pidx];
            }
            (*pidx)++;
            idx++;
        }

        return (mid1 + mid2) / 2.0;
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
        output = Solution().findMedianSortedArrays(get<0>(input), get<1>(input));
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
        std::tuple<std::vector<int>, std::vector<int>>, 
        double
        >>  testCases = {
        {
            {{1,3}, {2}},
            2,
        },
        {
            {{1,2}, {3,4}},
            2.5,
        },
        {
            {{}, {1,2,3,3,4}},
            3,
        },
        {
            {{1,3,5,7}, {2,4,6,8}},
            4.5,
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
