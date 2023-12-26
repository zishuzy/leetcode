/**
 * @file 0024.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 两两交换链表中的节点，中等
 *      https://leetcode.cn/problems/swap-nodes-in-pairs/description/
 * @version 0.1
 * @date 2023-12-26
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "data_define.h"

class Solution
{
public:
    ListNode *swapPairs(ListNode *head)
    {
        ListNode *prev, *l, *r, *next;
        if (!head || !head->next) {
            return head;
        }

        prev = nullptr;
        l = head;
        r = head->next;
        next = r->next;

        while (true) {
            if (prev == nullptr) {
                head = r;
            } else {
                prev->next = r;
            }

            l->next = next;
            r->next = l;

            prev = l;
            l = next;
            if (next == nullptr) {
                break;
            }
            r = next->next;
            if (r == nullptr) {
                break;
            }
            next = r->next;
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
        output = Solution().swapPairs(CopyListNode(input));
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
        ListNode*,
        ListNode*
        >>  testCases = {
        {
            InitListNode({1,2,3,4}),
            InitListNode({2,1,4,3}),
        },
        {
            InitListNode({1,2,3,4,5}),
            InitListNode({2,1,4,3,5}),
        },
        {
            InitListNode({}),
            InitListNode({}),
        },
        {
            InitListNode({1}),
            InitListNode({1}),
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
