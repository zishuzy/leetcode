/**
 * @file 0002.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 两数相加，中等，https://leetcode.cn/problems/add-two-numbers/
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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *res = new ListNode(-1);
        ListNode *cur = res;
        int carry = 0;
        while (l1 || l2) {
            int n1 = l1 ? l1->val : 0;
            int n2 = l2 ? l2->val : 0;
            int sum = n1 + n2 + carry;
            carry = sum / 10;
            cur->next = new ListNode(sum % 10);
            cur = cur->next;
            if (l1)
                l1 = l1->next;
            if (l2)
                l2 = l2->next;
        }
        if (carry == 1)
            cur->next = new ListNode(1);
        return res->next;
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
        output = Solution().addTwoNumbers(get<0>(input), get<1>(input));
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
            {InitListNode({2,4,3}), InitListNode({5,6,4})}, 
            InitListNode({7,0,8}),
        },
        {
            {InitListNode({0}), InitListNode({0})}, 
            InitListNode({0}),
        },
        {
            {InitListNode({9,9,9,9,9,9,9}), InitListNode({9,9,9,9})}, 
            InitListNode({8,9,9,9,0,0,0,1}),
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
