#include <iostream>
#include <vector>

using namespace std;

class Solution {
    bool found = false;
public:
    void solveSudoku(vector<vector<char>>& board) {
        backtrack(board, 0);
    }

private:
    void backtrack(vector<vector<char>>& board, int index) {
        // 如果找到了解，直接返回，不再继续搜索
        if (found) return;

        // index 是当前格子的线性索引 (0 到 80)
        // 结束条件：当我们处理完第 80 个格子（即 index == 81），说明找到了一个可行解
        if (index == 81) {
            found = true;
            return;
        }

        // 坐标转换：将线性索引 index 转换为二维坐标 (i, j)
        int i = index / 9; // 行号
        int j = index % 9; // 列号

        // 如果当前格子已经有数字（不是 '.'），则跳过，处理下一个格子
        if (board[i][j] != '.') {
            backtrack(board, index + 1);
            return;
        }

        // 尝试填入数字 '1' 到 '9'
        for (char ch = '1'; ch <= '9'; ch++) {
            // 检查填入 ch 是否合法
            if (!isValid(board, i, j, ch)) continue;

            // 做选择
            board[i][j] = ch;
            // 递归进入下一层
            backtrack(board, index + 1);
            // 如果在后续递归中找到了解，直接返回，不再回溯（撤销选择）
            if (found) return;
            // 撤销选择（回溯）
            board[i][j] = '.';
        }
    }

    // 检查在 (r, c) 位置填入 num 是否合法
    bool isValid(vector<vector<char>>& board, int r, int c, char num) {
        for (int i = 0; i < 9; i++) {
            // 1. 检查当前行 r 是否已有该数字
            // board[r][i] 表示第 r 行的第 i 个元素
            if (board[r][i] == num) return false;
            
            // 2. 检查当前列 c 是否已有该数字
            // board[i][c] 表示第 i 行的第 c 个元素
            if (board[i][c] == num) return false;
            
            // 3. 检查当前 3x3 宫格是否已有该数字
            // board[r / 3 * 3 + i / 3][c / 3 * 3 + i % 3] 解释见 README
            if (board[r / 3 * 3 + i / 3][c / 3 * 3 + i % 3] == num) return false;
        }
        return true;
    }
};
