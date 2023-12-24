/**
 * @file 0023.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 合并 K 个升序链表，困难
 *      https://leetcode.cn/problems/merge-k-sorted-lists/description/
 * @version 0.1
 * @date 2023-12-24
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "data_define.h"

class Solution
{
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        if (lists.empty()) {
            return nullptr;
        }
        std::vector<bool> vec_flag(lists.size(), true);
        std::vector<ListNode *> vec_tmp = lists;
        ListNode *head = nullptr, *cur;
        int nums = lists.size();
        int idx = -1;

        for (int i = 0; i < vec_tmp.size(); i++) {
            if (vec_tmp[i] == nullptr) {
                continue;
            }

            if (head == nullptr || vec_tmp[i]->val < head->val) {
                head = vec_tmp[i];
                idx = i;
            }
        }
        if (head == nullptr) {
            return nullptr;
        }

        vec_tmp[idx] = vec_tmp[idx]->next;
        cur = head;

        while (nums) {
            int val_min = INT_MAX;
            std::vector<std::pair<ListNode *, int>> list_min;
            for (int i = 0; i < vec_tmp.size(); i++) {
                if (!vec_flag[i]) {
                    continue;
                }
                if (vec_tmp[i] == nullptr) {
                    vec_flag[i] = false;
                    nums--;
                } else if (vec_tmp[i]->val == val_min) {
                    list_min.push_back({vec_tmp[i], i});
                } else if (vec_tmp[i]->val < val_min) {
                    list_min.clear();
                    list_min.push_back({vec_tmp[i], i});
                    val_min = vec_tmp[i]->val;
                }
            }

            for (const auto &item : list_min) {
                cur->next = item.first;
                vec_tmp[item.second] = item.first->next;
                cur = item.first;
            }
        }

        return head;
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
        output = Solution().mergeKLists(input);
    }
    bool IsOk() { return IsEqualListNode(output, expected); }

    _Tin input;
    _Tout output;
    _Tout expected;
};

TEST(Solution, leetcode)
{
    // clang-format off
    std::vector<CCase<
        vector<ListNode*>,
        ListNode*
        >>  testCases = {
        {
            {InitListNode({1,4,5}), InitListNode({1,3,4}), InitListNode({2,6})},
            InitListNode({1,1,2,3,4,4,5,6}),
        },
        {
            {},
            InitListNode({}),
        },
        {
            {InitListNode({})},
            InitListNode({}),
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
