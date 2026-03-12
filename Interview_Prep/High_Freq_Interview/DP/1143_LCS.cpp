#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// ==========================================
// 1143. 最长公共子序列 (Longest Common Subsequence, LCS)
// ==========================================
// 核心思想：动态规划 (DP)
// 状态定义：dp[i][j] 表示 text1[0...i-1] 和 text2[0...j-1] 的最长公共子序列长度。
// 状态转移：
// 1. 如果 text1[i-1] == text2[j-1]：
//    dp[i][j] = dp[i-1][j-1] + 1
// 2. 如果 text1[i-1] != text2[j-1]：
//    dp[i][j] = max(dp[i-1][j], dp[i][j-1])
// 初始状态：dp[0][j] = 0, dp[i][0] = 0 (空串的 LCS 为 0)
// 时间复杂度：O(M * N)
// 空间复杂度：O(M * N) (可优化至 O(min(M, N)))

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length();
        int n = text2.length();
        
        // DP table
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[m][n];
    }
};

int main() {
    Solution sol;
    string text1 = "abcde";
    string text2 = "ace"; 
    // LCS is "ace", length 3
    cout << "LCS of " << text1 << " and " << text2 << " is: " << sol.longestCommonSubsequence(text1, text2) << endl;
    
    return 0;
}
