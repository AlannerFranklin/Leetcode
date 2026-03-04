# 52. N 皇后 II (N-Queens II)

[LeetCode 链接](https://leetcode.cn/problems/n-queens-ii/)

## 题目描述

n 皇后问题 研究的是如何将 n 个皇后放置在 n × n 的棋盘上，并且使皇后彼此之间不能相互攻击。
给你一个整数 n ，返回 n 皇后问题 不同的解决方案的数量。

## 你的代码错误分析

你的代码整体框架是对的，但是有两个关键错误导致结果不对（或者逻辑混乱）：

### 1. 数组索引行列搞反 (Critical Error)

在 `backtrack` 函数中：
```cpp
// 你的代码
board[col][row] = 'Q'; 
```
`board` 是 `vector<string>`。
*   `board[i]` 访问的是第 `i` 个字符串（也就是第 `i` 行）。
*   `board[i][j]` 访问的是第 `i` 行的第 `j` 个字符（即第 `j` 列）。

你写成了 `board[col][row]`，意思是你在**第 `col` 行、第 `row` 列**放置了皇后。
但是你的递归参数是 `backtrack(board, row + 1)`，这意味着你本来想是一行一行放的。
如果你实际上是按列放（把 `col` 当行用），那逻辑就全乱了。

**修正**：应该始终使用 `board[row][col]`。

### 2. `isValid` 检查范围

在 `isValid` 函数中：
```cpp
// 你的代码
for (int i = 0; i < board.size(); i++) {
    if (board[i][col] == 'Q') return false;
}
```
你检查了整列 `0` 到 `n-1`。
虽然这在某些情况下可能没问题（因为下面的行还是 `.`），但加上第一个错误（行列搞反），这就彻底乱了。
如果你按照标准的“逐行放置”，只需要检查 `0` 到 `row-1` 行即可。

## 正确代码

```cpp
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
            // 正确：board[row][col]
            board[row][col] = 'Q';
            backtrack(board, row + 1);
            board[row][col] = '.';
        }
    }

    bool isValid(vector<string>& board, int row, int col) {
        int n = board.size();
        // 检查列（只查上面的行）
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
```
