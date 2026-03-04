# 51. N 皇后 (N-Queens)

[LeetCode 链接](https://leetcode.cn/problems/n-queens/)

## 题目描述

n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

## 思路解析

你说得非常对！回溯算法的核心就是**框架** + **选择/撤销** + **合法性判断**。

对于 N 皇后问题：
1.  **路径**：我们已经做出的选择（已经在 `0` 到 `row-1` 行放置了皇后）。
2.  **选择列表**：当前在第 `row` 行，我们可以选择在哪一列 (`col`) 放置皇后。
3.  **结束条件**：`row` 超过了最后一行（即 `row == n`），说明成功放满了 n 个皇后，记录结果。

### 框架结构

```cpp
void backtrack(board, row) {
    // 触发结束条件
    if (row == n) {
        res.push_back(board);
        return;
    }
    
    for (int col = 0; col < n; col++) {
        // 排除不合法选择
        if (!isValid(board, row, col)) continue;
        
        // 做选择
        board[row][col] = 'Q';
        // 进入下一行决策
        backtrack(board, row + 1);
        // 撤销选择
        board[row][col] = '.';
    }
}
```

### isValid 判断逻辑

我们需要检查在 `board[row][col]` 放置皇后是否合法。
因为我们是一行一行从上往下放的，所以：
1.  **不需要检查行**：当前行肯定还没有放过皇后（正在尝试放）。
2.  **不需要检查下面**：下面的行还没放，肯定没冲突。

只需要检查三个方向（都在上方）：
1.  **正上方（列冲突）**：`board[0...row-1][col]` 有没有皇后。
2.  **左上方（斜线冲突）**：`board[row-1][col-1]`, `board[row-2][col-2]`... 有没有皇后。
3.  **右上方（斜线冲突）**：`board[row-1][col+1]`, `board[row-2][col+2]`... 有没有皇后。

```cpp
bool isValid(vector<string>& board, int row, int col) {
    int n = board.size();
    // 检查列
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 'Q') return false;
    }
    // 检查左上方
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') return false;
    }
    // 检查右上方
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 'Q') return false;
    }
    return true;
}
```

## 复杂度分析

*   **时间复杂度**：$O(N!)$。第一行有 N 种选法，第二行有 N-1 种... 虽然有剪枝，但最坏情况仍接近阶乘级。
*   **空间复杂度**：$O(N)$。递归栈深度为 N，加上棋盘存储空间。
