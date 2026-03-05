# 695. 岛屿的最大面积 (Max Area of Island)

[LeetCode 链接](https://leetcode.cn/problems/max-area-of-island/)

## 题目描述

给你一个大小为 `m x n` 的二进制矩阵 `grid` 。
岛屿 是由一些相邻的 `1` (代表土地) 构成的组合，这里的「相邻」要求两个 `1` 必须在 水平或者竖直的四个方向上 相邻。
计算并返回 `grid` 中最大的岛屿面积。如果没有岛屿，则返回面积为 `0` 。

## 你的代码错误分析

你问：“维护了 `visited` 数组为什么会执行错误呢？理论上应该没什么关系啊。”

**实际上，你的 `visited` 逻辑和 DFS 递归逻辑冲突了，导致了重复计算或者漏算。**

### 1. `dfs` 函数内部逻辑问题

```cpp
// 你的代码
int dfs(vector<vector<int>>& grid, int i, int j) {
    if (/*越界*/ || visited[i][j]) return 0; // 检查 visited
    if (grid[i][j] == 0) return 0;
    
    visited[i][j] = true; // 标记 visited
    grid[i][j] = 0;       // 修改 grid
    
    // 递归调用
    return dfs(...) + ... + 1;
}
```
这段代码本身没问题。但是...

### 2. 主循环中的逻辑冲突 (Critical Error)

```cpp
// 你的代码
for (int i = 0; i < m; i++) { 
    for (int j = 0; j < n; j++) { 
        if (grid[i][j] == 1) { 
            visited[i][j] = true; // 错误点 1：在这里提前标记了 visited
            area = std::max(dfs(grid, i, j), area); 
        } 
    } 
}
```

**错误推演：**
1.  当你遇到一个陆地 `(i, j)`，你先把 `visited[i][j]` 设为 `true`。
2.  然后你调用 `dfs(grid, i, j)`。
3.  进入 `dfs` 函数的第一行：
    `if (i < 0 || ... || visited[i][j]) return 0;`
4.  **灾难发生**：因为你在外面已经把 `visited[i][j]` 设为 `true` 了，所以 `dfs` 函数一看“哦，这个点访问过了”，直接返回 `0`！
5.  结果：`dfs` 直接返回 `0`，没有任何递归，面积计算为 0。

**修正**：不要在调用 `dfs` 前手动标记 `visited`。让 `dfs` 函数自己去处理标记逻辑。

### 3. `visited` 数组初始化的位置

```cpp
// 你的代码
int maxAreaOfIsland(vector<vector<int>>& grid) {
    this->m = grid.size();
    this->n = grid[0].size();
    // ...
    this->visited = vector<vector<bool>> (m, vector<bool>(n, false));
    // ...
}
```
这部分是对的，先赋值 `m, n` 再初始化 `visited`。这比上一题（1020题）有进步。

### 4. 返回值 `INT_MIN`

```cpp
int area = INT_MIN;
```
如果没有岛屿，应该返回 `0`。`INT_MIN` 在没有岛屿时会返回错误的负数。

## 正确代码 (去掉冗余 visited)

既然我们允许修改 `grid`（题目通常允许，或者我们可以拷贝一份），直接把访问过的陆地 `1` 变成 `0` 就行了。这样 `grid` 本身就是 `visited` 数组。

```cpp
class Solution {
    int m, n;
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        int max_area = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    max_area = max(max_area, dfs(grid, i, j));
                }
            }
        }
        return max_area;
    }
    
    int dfs(vector<vector<int>>& grid, int i, int j) {
        if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == 0) {
            return 0;
        }
        grid[i][j] = 0; // 标记已访问
        return 1 + dfs(grid, i + 1, j) + dfs(grid, i - 1, j) + dfs(grid, i, j + 1) + dfs(grid, i, j - 1);
    }
};
```
