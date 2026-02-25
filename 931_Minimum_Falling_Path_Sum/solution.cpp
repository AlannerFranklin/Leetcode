#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        
        // dp[j] 表示到达上一行第 j 列的最小路径和
        // 初始化为矩阵的第一行
        vector<int> dp(matrix[0].begin(), matrix[0].end());
        
        // 从第 1 行开始向下遍历每一行
        for (int i = 1; i < n; ++i) {
            // temp 用于存储当前行的计算结果
            vector<int> temp(n);
            
            // 遍历当前行的每一列
            for (int j = 0; j < n; ++j) {
                // 1. 获取正上方的值 (上一行的第 j 列)
                int minV = dp[j];
                
                // 2. 尝试获取左上方的值 (上一行的第 j-1 列)
                if (j > 0) {
                    minV = min(minV, dp[j - 1]);
                }
                
                // 3. 尝试获取右上方的值 (上一行的第 j+1 列)
                if (j < n - 1) {
                    minV = min(minV, dp[j + 1]);
                }
                
                // 当前格子的最小路径和 = 上一行的最小值 + 当前格子的值
                temp[j] = minV + matrix[i][j];
            }
            
            // 更新 dp 数组，准备计算下一行（滚动数组优化）
            dp = move(temp);
        }
        
        // 返回最后一行中的最小值
        return *min_element(dp.begin(), dp.end());
    }
};
