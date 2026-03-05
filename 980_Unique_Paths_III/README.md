# LeetCode 980. Unique Paths III

## 题目描述

在二维网格 `grid` 上，有 4 种类型的方格：

*   `1` 表示起始方格。且只有一个起始方格。
*   `2` 表示结束方格，且只有一个结束方格。
*   `0` 表示我们可以走过的空方格。
*   `-1` 表示我们无法跨越的障碍。

返回在四个方向（上、下、左、右）上行走时，从起始方格到结束方格的不同路径的数目。

**每一个无障碍方格都要通过一次，但是一条路径中不能重复通过同一个方格。**

## 解题思路

这道题是一个典型的回溯（Backtracking）/ DFS 问题。我们需要找到从起点到终点的所有路径，并且每条路径必须经过所有的空方格（`0`）以及起点（`1`）和终点（`2`）各一次。

### 核心逻辑

为了确保我们经过了每一个无障碍方格，我们需要统计网格中**需要访问的方格总数**。

1.  **初始化**：
    *   遍历整个网格。
    *   找到起点 `(start_x, start_y)`。
    *   统计所有空方格 `0` 的数量。
    *   为了方便计算，我们可以定义 `totalCount` 为：`空方格数量` + `1` (起点) + `1` (终点)。
    *   *在我的代码实现中*：
        *   **`totalCount`** 统计了所有的 `0`、起点 `1` 和终点 `2`。
        *   **`visitedCount`** 初始为 1（站在起点）。
        *   每走一步（递归调用 DFS），`visitedCount` 加 1。
        *   **Base Case**：当走到终点 `2` 时，如果 `visitedCount == totalCount`，说明这条路径正好经过了所有需要经过的格子，是一条有效路径。

### 变量解释 (User Question)

你在问题中提到的 `totalCount` 和 `visitedCount` 代表：

*   **`totalCount`**: 网格中**必须被访问的格子总数**。
    *   在我的代码中，它等于：`空方格(0)的数量` + `起点(1)` + `终点(2)`。
    *   也就是整个网格中除了障碍物(-1)以外的所有格子数。
*   **`visitedCount`**: 当前路径**已经访问过的格子数量**。
    *   从起点开始，初始值为 1。
    *   每走一步（递归调用 DFS），这个值加 1。
    *   它的作用是用来验证我们是否走完了所有的空方格。因为题目要求“每一个无障碍方格都要通过一次”，所以单纯到达终点是不够的，必须 `visitedCount == totalCount` 才算成功。

### 代码实现细节

1.  **DFS 函数**：接收当前坐标 `(x, y)` 和当前的步数 `visitedCount`。
2.  **Base Case**：
    *   越界或遇到障碍物（-1）：返回 0。
    *   遇到终点（2）：检查 `visitedCount` 是否等于 `totalCount`。如果是，返回 1，否则返回 0。

```cpp
// 伪代码逻辑
int uniquePathsIII(vector<vector<int>>& grid) {
    int totalCount = 0;
    int sx, sy;
    for... {
        if cell != -1: totalCount++; // 统计所有非障碍物格子
        if cell == 1: sx, sy;
    }
    return dfs(grid, sx, sy, 1, totalCount); // 初始步数为1
}

int dfs(grid, x, y, empty) {
    if check_bound or visited: return 0;
    if grid[x][y] == 2:
        return empty == -1 ? 1 : 0; // 因为起点也消耗了一步，或者我们在起点调用时就处理好
    
    grid[x][y] = -1; // mark visited
    empty--;
    int res = dfs(neighbor) ...
    grid[x][y] = 0; // backtrack
    empty++;
    return res;
}
```

为了配合你问的 `visitedCount` 和 `totalCount`，我的 `solution.cpp` 采用了计数增加的方式，逻辑是一样的。

