#include <vector>

using namespace std;

class Solution {
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        int startX, startY;
        int totalCount = 0; // 需要访问的总格子数（包括起点和所有的0）
        int rows = grid.size();
        int cols = grid[0].size();

        // 1. 遍历网格，找到起点，并统计需要访问的格子总数
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 1) {
                    startX = i;
                    startY = j;
                    totalCount++; // 起点
                } else if (grid[i][j] == 0) {
                    totalCount++; // 空方格
                } else if (grid[i][j] == 2) {
                    totalCount++; // 终点（把它也算进总数，这样Base Case判断更简单）
                }
            }
        }

        return dfs(grid, startX, startY, 1, totalCount); // 初始visitedCount为1
    }

private:
    // dfs函数返回从(x, y)出发，且当前已访问visitedCount个格子，最终能到达终点的路径数量
    int dfs(vector<vector<int>>& grid, int x, int y, int visitedCount, int totalCount) {
        int rows = grid.size();
        int cols = grid[0].size();

        // 越界检查
        if (x < 0 || x >= rows || y < 0 || y >= cols || grid[x][y] == -1) {
            return 0;
        }

        // 到达终点
        if (grid[x][y] == 2) {
            // 如果访问的格子数等于需要访问的总数，说明找到了一条有效路径
            return visitedCount == totalCount ? 1 : 0;
        }

        // 标记当前格子为已访问（通过设置为-1，障碍物）
        // 注意：因为grid[x][y]可能是1（起点）或者0，我们都先变成-1，回溯时复原
        int temp = grid[x][y];
        grid[x][y] = -1;

        int paths = 0;
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (auto& dir : dirs) {
            int nx = x + dir[0];
            int ny = y + dir[1];
            // 递归调用
            // 注意：这里我们传递 visitedCount + 1 吗？
            // 我们当前格子(x,y)算是路径中的一步。
            // 下一步是(nx, ny)。
            // 如果(nx, ny)是0，那么它会继续递归。
            // 如果(nx, ny)是2，它会在下一层递归中被检测到。
            // 所以这里传 visitedCount 应该怎么算？
            // 我们定义 visitedCount 为“进入当前dfs之前已经访问的格子数 + 当前格子”。
            // 所以传给下一层应该是 visitedCount + 1？
            // 不对，totalCount只包含了1和0。2不在totalCount里。
            // 当我们站在1时，visitedCount=1。
            // 走到下一个0时，visitedCount=2。
            // ...
            // 走到最后一个0时，visitedCount=totalCount。
            // 从最后一个0走到2时，dfs(2)被调用，此时传入的visitedCount还是totalCount（因为2不算在计数里？或者算？）。
            // 让我们看代码逻辑：
            // 如果 grid[nx][ny] 是 0，调用 dfs(nx, ny, visitedCount + 1, totalCount)
            // 如果 grid[nx][ny] 是 2，调用 dfs(nx, ny, visitedCount, totalCount) ？？ 这样写很麻烦。
            
            // 更简单的逻辑：
            // totalCount 统计 0 的个数。
            // 起点算不算无所谓，只要统一。
            // 官方题解通常是：totalCount = 0的个数 + 1 (起点) + 1 (终点)？ 或者只是 0的个数 + 1。
            // 让我们统一标准：
            // totalCount = 所有 0 的个数 + 1 (起点)。
            // 目标：走到 2 的时候，步数刚好消耗完 totalCount。
            // 所以在 dfs(x,y) 中：
            // 1. 标记 x,y 已访问。
            // 2. 遍历邻居 nx, ny。
            // 3. dfs(nx, ny, visitedCount + 1)。
            // 4. 回溯。
            
            // 等等，如果 nx,ny 是 2，我们进去吗？
            // 是的，进去。
            // 进入 dfs(2) 后，判断 base case。
            // 此时传入的 visitedCount 是从上一步传过来的。
            // 假设路径是 1 -> 2 (0个0)。 totalCount = 1 (起点)。
            // dfs(start) -> visitedCount=1.
            //   -> dfs(end) -> param visitedCount = 1 + ? 
            //      如果是直接传 visitedCount+1，那就是2。
            //      此时 2 == totalCount + 1 ?
            
            // 让我们修正定义，让代码更清晰：
            // totalCount = 0的个数 + 1 (起点)。
            // 当我们到达 2 时，我们需要确认之前的路径经过了 totalCount 个格子。
            // 所以，到达 2 时，如果参数 visitedCount == totalCount，则由该路径有效。
            // 这样意味着 2 本身不增加 count。
            // 所以在递归调用时，如果下一步是 2，我们不加 1？
            // 或者，我们可以把 2 也算进 totalCount。
            // 这样 totalCount = 0的个数 + 1(起点) + 1(终点)。
            // 初始 dfs(start, visitedCount=1)。
            // 走到 2 时，visitedCount 应该是 totalCount。
            // 这样逻辑最顺。
            
            paths += dfs(grid, nx, ny, visitedCount + 1, totalCount);
        }

        // 回溯
        grid[x][y] = temp;
        
        return paths;
    }
};
