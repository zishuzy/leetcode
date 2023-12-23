/**
 * @file 0021.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 合并两个有序链表，简单
 *      https://leetcode.cn/problems/merge-two-sorted-lists/description/
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
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        ListNode *head, *node;
        if (list1 == nullptr && list2 == nullptr) {
            return nullptr;
        } else if (list1 == nullptr) {
            return list2;
        } else if (list2 == nullptr) {
            return list1;
        }

        if (list1->val < list2->val) {
            head = list1;
            list1 = list1->next;
        } else {
            head = list2;
            list2 = list2->next;
        }
        node = head;

        while (list1 && list2) {
            if (list1->val < list2->val) {
                node->next = list1;
                node = list1;
                list1 = list1->next;
            } else {
                node->next = list2;
                node = list2;
                list2 = list2->next;
            }
        }
        if (list1) {
            node->next = list1;
        } else if (list2) {
            node->next = list2;
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
        output = Solution().mergeTwoLists(get<0>(input), get<1>(input));
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
        std::tuple<ListNode*, ListNode*>,
        ListNode*
        >>  testCases = {
        {
            {InitListNode({1,2,4}), InitListNode({1,3,4})},
            InitListNode({1,1,2,3,4,4}),
        },
        {
            {InitListNode({}), InitListNode({})},
            InitListNode({}),
        },
        {
            {InitListNode({}), InitListNode({0})},
            InitListNode({0}),
        },
        {
            {InitListNode({1,2,3}), InitListNode({2,3,4,5,6})},
            InitListNode({1,2,2,3,3,4,5,6}),
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
