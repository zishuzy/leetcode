/**
 * @file 0036.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 有效的数独，中等
 *      https://leetcode.cn/problems/valid-sudoku/
 * @version 0.1
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "data_define.h"

class Solution
{
public:
    bool isValidSudoku(vector<vector<char>> &board)
    {
        std::vector<int> row_bucket(9, 0);
        std::vector<int> col_bucket(9, 0);
        std::vector<int> block_bucket(9, 0);

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    continue;
                }
                int idx = board[i][j] - '1';
                if ((row_bucket[i] >> idx) & 1) {
                    return false;
                }
                row_bucket[i] = row_bucket[i] ^ (1 << idx);
                if ((col_bucket[j] >> idx) & 1) {
                    return false;
                }
                col_bucket[j] = col_bucket[j] ^ (1 << idx);
                int block_row = 3 * (i / 3) + j / 3;
                if ((block_bucket[block_row] >> idx) & 1) {
                    return false;
                }
                block_bucket[block_row] = block_bucket[block_row] ^ (1 << idx);
            }
        }

        return true;
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
        output_ = Solution().isValidSudoku(input);
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
        std::vector<std::vector<char>>,
        bool
        >>  testCases = {
        {
            {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
             {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
             {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
             {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
             {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
             {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
             {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
             {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
             {'.', '.', '.', '.', '8', '.', '.', '7', '9'}},
            true,
        },
        {
            {{'9', '3', '.', '.', '7', '.', '.', '.', '.'},
             {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
             {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
             {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
             {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
             {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
             {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
             {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
             {'.', '.', '.', '.', '8', '.', '.', '7', '9'}},
            false,
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
