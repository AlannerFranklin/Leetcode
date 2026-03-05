#include <iostream>
#include <vector>

using namespace std;

class Solution {
    int m, n;
    
public:
    int numEnclaves(vector<vector<int>>& grid) {
        // 修正：初始化顺序问题
        // 你在初始化 m, n 之前就使用了 m, n 来初始化 visited，这时候 m, n 还是随机值（或者 0）
        // 这会导致 visited 大小不对，或者直接 crash。
        this->m = grid.size();
        this->n = grid[0].size();
        
        // 实际上，这道题并不需要 visited 数组
        // 我们可以直接修改 grid[i][j] 的值（比如变成 0）来标记已访问
        // 这样空间复杂度可以从 O(MN) 降到 O(1)
        
        // 1. 淹没靠边的陆地
        for (int j = 0; j < n; j++) {
            dfs(grid, 0, j);      // 上边界
            dfs(grid, m - 1, j);  // 下边界
        }
        for (int i = 0; i < m; i++) {
            dfs(grid, i, 0);      // 左边界
            dfs(grid, i, n - 1);  // 右边界
        }
        
        // 2. 统计剩下的陆地
        int res = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    res++;
                }
            }
        }
        return res;
    }
    
    // DFS: 将 (i, j) 及其相连的陆地淹没（变成 0）
    void dfs(vector<vector<int>>& grid, int i, int j) {
        // 越界检查
        if (i < 0 || i >= m || j < 0 || j >= n) return;
        
        // 如果是海洋 (0)，直接返回
        // 注意：因为我们把访问过的陆地也变成了 0，所以这里也包含了“已访问”的检查
        if (grid[i][j] == 0) return;
        
        // 将陆地变成海洋 (标记为已访问)
        grid[i][j] = 0;
        
        // 向四个方向扩散
        dfs(grid, i + 1, j);
        dfs(grid, i - 1, j);
        dfs(grid, i, j + 1);
        dfs(grid, i, j - 1);
    }
};
