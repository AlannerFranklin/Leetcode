#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
    int m, n;
    // 实际上不需要 visited，直接修改 grid 即可
    // 如果要用 visited，必须保证逻辑严密
    
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        int area = 0; // 初始化为 0，因为如果没有岛屿返回 0，而不是 INT_MIN
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    // 这里不需要先把 visited[i][j] 设为 true
                    // 也不需要在这里修改 visited
                    // 因为 dfs 函数内部会处理
                    area = std::max(dfs(grid, i, j), area);
                }
            }
        }
        return area;
    }
    
    int dfs(vector<vector<int>>& grid, int i, int j) {
        // 越界检查
        if (i < 0 || i >= m || j < 0 || j >= n) return 0;
        
        // 如果是水 (0)，直接返回 0
        // 注意：这里我们修改 grid[i][j] = 0 来标记已访问
        // 所以 grid[i][j] == 0 包含了“水”和“已访问的陆地”两种情况
        if (grid[i][j] == 0) return 0;
        
        // 将当前陆地变成水 (标记为已访问)
        grid[i][j] = 0;
        
        // 向四个方向扩散，并累加面积
        // 1 是当前这个格子的面积
        return 1 + dfs(grid, i + 1, j) 
                 + dfs(grid, i - 1, j) 
                 + dfs(grid, i, j + 1) 
                 + dfs(grid, i, j - 1);
    }
};
