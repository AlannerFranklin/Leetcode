#include <vector>

using namespace std;

class Solution {
public:
    void dfs(vector<vector<char>>& grid, int r, int c) {
        // 1. 终止条件：越界 或者 是水
        if (r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size() || grid[r][c] == '0') {
            return;
        }
        
        // 2. 标记：把陆地沉下去
        grid[r][c] = '0';
        
        // 3. 递归四个方向
        dfs(grid, r - 1, c);
        dfs(grid, r + 1, c);
        dfs(grid, r, c - 1);
        dfs(grid, r, c + 1);
    }

    int numIslands(vector<vector<char>>& grid) {
        int count = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == '1') {
                    count++; // 发现新大陆！
                    dfs(grid, i, j); // 把这块大陆全淹了
                }
            }
        }
        return count;
    }
};
