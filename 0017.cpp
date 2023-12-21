/**
 * @file 0017.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 电话号码的字母组合，中等
 *      https://leetcode.cn/problems/letter-combinations-of-a-phone-number/description/
 * @version 0.1
 * @date 2023-12-21
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "data_define.h"

class Solution
{
public:
    vector<string> letterCombinations(string digits)
    {
        std::unordered_map<char, std::vector<char>> map_tmp;
        std::vector<std::string> res;

        if (digits.empty()) {
            return {};
        }

        map_tmp['2'] = {'a', 'b', 'c'};
        map_tmp['3'] = {'d', 'e', 'f'};
        map_tmp['4'] = {'g', 'h', 'i'};
        map_tmp['5'] = {'j', 'k', 'l'};
        map_tmp['6'] = {'m', 'n', 'o'};
        map_tmp['7'] = {'p', 'q', 'r', 's'};
        map_tmp['8'] = {'t', 'u', 'v'};
        map_tmp['9'] = {'w', 'x', 'y', 'z'};

        for (const auto &c : map_tmp[digits[0]]) {
            res.push_back(std::string(1, c));
        }

        for (size_t i = 1; i < digits.size(); i++) {
            std::vector<std::string> tmp;
            for (size_t j = 0; j < res.size(); j++) {
                for (const auto &c : map_tmp[digits[i]]) {
                    tmp.push_back(res[j] + c);
                }
            }

            res.swap(tmp);
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
        output = Solution().letterCombinations(input);
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
        string,
        vector<string>
        >>  testCases = {
        {
            "23",
            {"ad","ae","af","bd","be","bf","cd","ce","cf"},
        },
        {
            "",
            {},
        },
        {
            "2",
            {"a", "b", "c"},
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
