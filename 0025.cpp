/**
 * @file 0025.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief K 个一组翻转链表，困难
 *      https://leetcode.cn/problems/reverse-nodes-in-k-group/description/
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
    ListNode *reverse(ListNode *head)
    {
        ListNode *l, *r, *next;
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        l = head;
        r = head->next;
        l->next = nullptr;
        while (r != nullptr) {
            next = r->next;
            r->next = l;
            l = r;
            r = next;
        }

        return l;
    }

    ListNode *reverseKGroup(ListNode *head, int k)
    {
        ListNode *root = nullptr, *last_tail = nullptr, *node, *next;
        int count = 0;

        if (k == 1) {
            return head;
        }

        node = head;
        for (node = head; node != nullptr;) {
            count++;
            if (count == k) {
                if (root == nullptr) {
                    root = node;
                    last_tail = head;
                } else {
                    last_tail->next = node;
                }

                next = node->next;
                node->next = nullptr;
                reverse(head);
                last_tail = head;
                last_tail->next = next;
                head = next;
                node = next;
                count = 0;
            } else {
                node = node->next;
            }
        }

        return root;
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
        output = Solution().reverseKGroup(CopyListNode(get<0>(input)), get<1>(input));
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
            InitListNode({2,1,4,3,5}),
        },
        {
            {InitListNode({1,2,3,4,5}), 3},
            InitListNode({3,2,1,4,5}),
        },
        {
            {InitListNode({1,2,3,4,5}), 1},
            InitListNode({1,2,3,4,5}),
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
