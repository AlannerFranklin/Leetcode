#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int res = 0;
        int m = grid.size();
        int n = grid[0].size();
        
        // 核心思路：
        // 1. 封闭岛屿的定义是“完全由 1 包围”的岛屿（0）。
        // 2. 如果一个岛屿接触到了矩阵的边界，那么它就不可能是“封闭”的（因为边界外面不是 1，而是图外）。
        // 3. 所以，我们先把所有“靠边”的岛屿都淹没掉（变成 1）。
        
        // 淹没上下边界的岛屿
        for (int j = 0; j < n; j++) {
            dfs(grid, 0, j);      // 上边界
            dfs(grid, m - 1, j);  // 下边界
        }
        
        // 淹没左右边界的岛屿
        for (int i = 0; i < m; i++) {
            dfs(grid, i, 0);      // 左边界
            dfs(grid, i, n - 1);  // 右边界
        }
        
        // 剩下的 0 一定是封闭岛屿
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    res++;
                    dfs(grid, i, j); // 找到一个封闭岛屿后，把它淹没，避免重复计算
                }
            }
        }
        return res;
    }
    
    // DFS 函数：从 (i, j) 开始，将相连的 0 都变成 1（淹没岛屿）
    void dfs(vector<vector<int>>& grid, int i, int j) {
        int m = grid.size();
        int n = grid[0].size();
        
        // 越界检查
        if (i < 0 || i >= m || j < 0 || j >= n) return;
        
        // 如果已经是水 (1)，直接返回
        if (grid[i][j] == 1) return;
        
        // 将当前陆地变成水
        grid[i][j] = 1;
        
        // 向四个方向扩散
        dfs(grid, i + 1, j);
        dfs(grid, i - 1, j);
        dfs(grid, i, j - 1);
        dfs(grid, i, j + 1);
    }
};
