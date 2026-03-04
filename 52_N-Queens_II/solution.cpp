#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
    int count = 0;

public:
    int totalNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        backtrack(board, 0);
        return count;
    }

private:
    void backtrack(vector<string>& board, int row) {
        if (row == board.size()) {
            count++;
            return;
        }

        int n = board[row].size();
        for (int col = 0; col < n; col++) {
            if (!isValid(board, row, col)) {
                continue;
            }
            // 修正错误：应该是 board[row][col] = 'Q'
            // 你的代码写成了 board[col][row] = 'Q'，搞反了行列
            board[row][col] = 'Q';
            
            backtrack(board, row + 1);
            
            // 撤销选择
            board[row][col] = '.';
        }
    }

    bool isValid(vector<string>& board, int row, int col) {
        int n = board.size();
        
        // 修正错误：列检查范围
        // 只需要检查 0 到 row-1 行，因为下面的行还没放
        // 你的代码检查了整个 board，这会导致把 '.' 当作没冲突，
        // 但问题是如果你的 board[col][row] 写错了，这里的逻辑也会乱。
        // 正确逻辑：
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') return false;
        }

        // 检查右上
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') return false;
        }
        
        // 检查左上
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') return false;
        }
        return true;
    }
};
