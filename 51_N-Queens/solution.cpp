#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
    vector<vector<string>> res;

public:
    vector<vector<string>> solveNQueens(int n) {
        // 初始化棋盘，全部填充 '.'
        vector<string> board(n, string(n, '.'));
        // 从第 0 行开始回溯
        backtrack(board, 0);
        return res;
    }

private:
    // 路径：board 中小于 row 的那些行都已经成功放置了皇后
    // 选择列表：第 row 行的所有列都是放置皇后的选择
    // 结束条件：row 超过 board 的最后一行
    void backtrack(vector<string>& board, int row) {
        // 触发结束条件
        if (row == board.size()) {
            res.push_back(board);
            return;
        }

        int n = board[row].size();
        // 在当前行 row，尝试在每一列 col 放置皇后
        for (int col = 0; col < n; col++) {
            // 排除不合法选择
            if (!isValid(board, row, col)) {
                continue;
            }
            // 做选择
            board[row][col] = 'Q';
            // 进入下一行决策
            backtrack(board, row + 1);
            // 撤销选择
            board[row][col] = '.';
        }
    }

    /* 是否可以在 board[row][col] 放置皇后？ */
    bool isValid(vector<string>& board, int row, int col) {
        int n = board.size();

        // 1. 检查列是否有皇后冲突
        // 只需要检查上面的行，因为下面的行还没放
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') {
                return false;
            }
        }

        // 2. 检查左上方是否有皇后冲突
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }

        // 3. 检查右上方是否有皇后冲突
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }
        
        // 为什么不需要检查行？因为我们是一行一行放的，当前行肯定只有一个。
        // 为什么不需要检查左下和右下？因为我们是自上而下放的，下面还没放呢。

        return true;
    }
};
