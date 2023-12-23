/**
 * @file 0019.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 删除链表的倒数第 N 个结点，中等
 *      https://leetcode.cn/problems/remove-nth-node-from-end-of-list/
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
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *target_pre = head;
        ListNode *target = head;
        ListNode *res = head;
        int i = 0;

        for (ListNode *node = head; node != nullptr; node = node->next) {
            i++;
            if (i > n) {
                target_pre = target;
                target = target->next;
            }
        }
        if (target == head) {
            res = head->next;
            // delete head;
        } else {
            target_pre->next = target->next;
            // delete target;
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
        output = Solution().removeNthFromEnd(get<0>(input), get<1>(input));
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
        std::tuple<ListNode*, int>,
        ListNode*
        >>  testCases = {
        {
            {InitListNode({1,2,3,4,5}), 2},
            InitListNode({1,2,3,5}),
        },
        {
            {InitListNode({1}), 1},
            InitListNode({}),
        },
        {
            {InitListNode({1,2}), 1},
            InitListNode({1}),
        },
        {
            {InitListNode({1,2}), 2},
            InitListNode({2}),
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
