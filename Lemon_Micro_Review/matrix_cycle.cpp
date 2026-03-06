#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 题目3：矩阵循环检测
// 题目描述：给定一个矩阵，每个位置可能有某种指令（如 U,D,L,R），
// 或者题目意思是：给定起点，按照某种规则走，判断是否会无限循环。
// 根据你的描述：“判断是否矩阵中存在位置通过udlr操作一直在矩阵内出不来的点”
// 这通常意味着矩阵中的每个点都有一个固定的移动方向（或者你可以选择方向？如果是选择，通常是能不能走出去的问题）。
// 假设是每个点有固定方向（Functional Graph），我们需要检测是否有环，或者路径通向环。

// 核心思路：DFS + 三色标记法
// 0: 未访问 (Unvisited)
// 1: 正在访问 (Visiting) - 当前递归栈中，如果遇到说明有环
// 2: 已访问且安全 (Visited & Safe) - 已知会走出边界
// 3: 已访问且有环 (Visited & Cycle) - 已知会导致无限循环

// 假设输入是一个 char 矩阵，包含 'U', 'D', 'L', 'R'
// 如果走出边界，则不算“出不来”。“出不来” = 进入环。

class Solution {
public:
    // 返回 true 表示存在“出不来”的点
    bool hasCycle(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        // status: 0=未访问, 1=正在访问, 2=能走出, 3=出不来(环)
        vector<vector<int>> status(m, vector<int>(n, 0));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dfs(grid, i, j, status)) {
                    return true; // 只要找到一个点出不来，就返回 true
                }
            }
        }
        return false;
    }

private:
    // 返回 true 表示从 (r, c) 出发会无限循环
    bool dfs(vector<vector<char>>& grid, int r, int c, vector<vector<int>>& status) {
        int m = grid.size();
        int n = grid[0].size();

        // 1. 越界检查 -> 能走出去 -> false (不是环)
        if (r < 0 || r >= m || c < 0 || c >= n) {
            return false;
        }

        // 2. 状态检查
        if (status[r][c] == 1) return true; // 遇到正在访问的节点 -> 发现环！
        if (status[r][c] == 2) return false; // 已知能走出去
        if (status[r][c] == 3) return true;  // 已知是环

        // 3. 标记为正在访问
        status[r][c] = 1;

        // 4. 根据当前格子的指令移动
        int next_r = r, next_c = c;
        char dir = grid[r][c];
        if (dir == 'U') next_r--;
        else if (dir == 'D') next_r++;
        else if (dir == 'L') next_c--;
        else if (dir == 'R') next_c++;
        else {
            // 如果有非法字符，视作停止？或者陷阱？
            // 假设非法字符也是出不去，或者视为原地不动（环）
            // 这里假设只有UDLR
        }

        bool isCycle = dfs(grid, next_r, next_c, status);

        // 5. 标记最终状态
        status[r][c] = isCycle ? 3 : 2;
        return isCycle;
    }
};

// 另一种可能性：如果题目是“你可以选择UDLR”，问是否存在一个点怎么走都出不去？
// 那就是“封闭岛屿”问题，或者被 'X' 包围的区域。
// 但根据“操作一直在矩阵内出不来”，更像是环检测。
