#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        
        // dp[i][j] 代表 word1 前 i 个字符转换成 word2 前 j 个字符的最少步数
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        
        // 初始化边界
        for (int i = 0; i <= n; i++) dp[i][0] = i; // word1 -> 空串 (全删除)
        for (int j = 0; j <= m; j++) dp[0][j] = j; // 空串 -> word2 (全插入)
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1]; // 字符相等，不用操作
                } else {
                    dp[i][j] = min({
                        dp[i - 1][j],    // 删除
                        dp[i][j - 1],    // 插入
                        dp[i - 1][j - 1] // 替换
                    }) + 1;
                }
            }
        }
        
        return dp[n][m];
    }
};
