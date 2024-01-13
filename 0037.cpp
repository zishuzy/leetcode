/**
 * @file 0037.cpp
 * @author zishu (zishuzy@gmail.com)
 * @brief 解数独，困难
 *      https://leetcode.cn/problems/sudoku-solver/description/
 * @version 0.1
 * @date 2024-01-13
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "data_define.h"

class Solution
{
public:
    bool dfs(vector<vector<char>> &board, int row, int col, std::vector<int> &row_bucket,
             std::vector<int> &col_bucket, std::vector<int> block_bucket)
    {
        bool ok = true;

        for (int i = row; i < 9; i++) {
            for (int j = i == row ? col : 0; j < 9; j++) {
                int r = i, c = j;
                int b = 3 * (i / 3) + j / 3;
                if (board[i][j] == '.') {
                    for (int tmp = 0; tmp < 9; tmp++) {
                        if ((row_bucket[r] >> tmp) & 1 || (col_bucket[c] >> tmp) & 1 ||
                            (block_bucket[b] >> tmp) & 1) {
                            continue;
                        }
                        board[i][j] = '1' + tmp;

                        row_bucket[r] = row_bucket[r] ^ (1 << tmp);
                        col_bucket[c] = col_bucket[c] ^ (1 << tmp);
                        block_bucket[b] = block_bucket[b] ^ (1 << tmp);

                        if (dfs(board, j == 8 ? i + 1 : i, j == 8 ? 0 : j + 1, row_bucket,
                                col_bucket, block_bucket)) {
                            goto out;
                        } else {

                            row_bucket[r] = row_bucket[r] ^ (1 << tmp);
                            col_bucket[c] = col_bucket[c] ^ (1 << tmp);
                            block_bucket[b] = block_bucket[b] ^ (1 << tmp);
                            board[i][j] = '.';
                        }
                    }
                    ok = false;
                    goto out;
                }
            }
        }
    out:
        return ok;
    }

    void solveSudoku(vector<vector<char>> &board)
    {
        vector<vector<char>> bk(board);
        std::vector<int> row_bucket(9, 0);
        std::vector<int> col_bucket(9, 0);
        std::vector<int> block_bucket(9, 0);

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                int r = i, c = j;
                int b = 3 * (i / 3) + j / 3;
                if (board[i][j] != '.') {
                    int idx = board[i][j] - '1';
                    row_bucket[r] = row_bucket[r] ^ (1 << idx);
                    col_bucket[c] = col_bucket[c] ^ (1 << idx);
                    block_bucket[b] = block_bucket[b] ^ (1 << idx);
                }
            }
        }

        dfs(board, 0, 0, row_bucket, col_bucket, block_bucket);
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
        Solution().solveSudoku(input);
        output_ = input;
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
        std::vector<std::vector<char>>
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
            {{'5', '3', '4', '6', '7', '8', '9', '1', '2'},
             {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
             {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
             {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
             {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
             {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
             {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
             {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
             {'3', '4', '5', '2', '8', '6', '1', '7', '9'}},
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
