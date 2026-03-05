# 1020. 飞地的数量 (Number of Enclaves)

[LeetCode 链接](https://leetcode.cn/problems/number-of-enclaves/)

## 题目描述

给你一个大小为 `m x n` 的二进制矩阵 `grid` ，其中 `0` 表示一个海洋单元格、`1` 表示一个陆地单元格。
一次 移动 是指从一个陆地单元格走到另一个相邻（上、下、左、右）的陆地单元格或跨过 `grid` 的边界。
返回网格中 无法 在任意次数的移动中离开网格边界的陆地单元格的数量。

## 你的代码错误分析

### 1. 变量初始化顺序 (Critical Error)

```cpp
// 你的代码
int m, n;
vector<vector<bool>> visited;
int numEnclaves(vector<vector<int>>& grid) {
    // 错误！此时 m 和 n 还没有被赋值（通常是 0 或随机值）
    this->visited = vector<vector<bool>>(m, vector<bool>(n, false)); 
    int res = 0; 
    this->m = grid.size(); // 这里才赋值 m
    this->n = grid[0].size(); // 这里才赋值 n
    // ...
}
```
*   **后果**：`visited` 数组的大小被初始化为 `0x0`（或者随机大小），当你后面访问 `visited[i][j]` 时，会发生 **越界访问 (Segmentation Fault)**。
*   **修正**：必须先获取 `m` 和 `n` 的值，再初始化 `visited`。

### 2. 逻辑冗余：为什么不需要 `visited` 数组？

你在代码中同时做了两件事来标记“已访问”：
1.  `grid[i][j] = 0;` （把陆地变成海洋）
2.  `visited[i][j] = true;`

**其实只需要第 1 步就够了！**
*   这道题的目标是统计“无法离开边界”的陆地。
*   我们的策略是：先把“能离开边界”的陆地（靠边的陆地）全部变成海洋（`0`）。
*   一旦 `grid[i][j]` 变成了 `0`，对于后续的 DFS 来说，它就等同于海洋，自然会被忽略。
*   所以，**修改原数组本身就可以充当 `visited` 的功能**。
*   这样可以把空间复杂度从 $O(M \times N)$ 降低到 $O(1)$（不考虑递归栈）。

### 3. DFS 中的逻辑小问题

```cpp
// 你的代码
void dfs(vector<vector<int>>& grid, int i, int j) {
    if (/*越界*/ || visited[i][j]) return;
    if (grid[i][j] == 0) return;
    
    grid[i][j] = 0;
    visited[i][j] = true; // 既然上面 grid 已经是 0 了，下一次递归就会在 if (grid==0) 处返回
    // ...
}
```
由于你把 `grid` 改成了 `0`，下次再遇到这个格子时，`if (grid[i][j] == 0)` 就会拦截住，所以 `visited` 数组完全是多余的。

## 正确思路 (Flood Fill)

这道题和 [1254. 统计封闭岛屿的数目](../1254_Number_of_Closed_Islands/README.md) 几乎一模一样。

1.  **淹没边界**：从矩阵的四个边界出发，DFS 遍历所有相连的陆地（`1`），把它们变成海洋（`0`）。这些陆地就是“能飞出去”的。
2.  **统计剩余**：遍历整个矩阵，剩下的 `1` 就是“飞地”（无法离开边界的陆地）。直接统计个数即可。

## 复杂度分析

*   **时间复杂度**：$O(M \times N)$。每个格子最多被访问一次。
*   **空间复杂度**：$O(M \times N)$（递归栈），如果算上 `visited` 也是 $O(M \times N)$，去掉后是 $O(1)$（原地修改）。
