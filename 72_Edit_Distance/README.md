# 72. 编辑距离

## 题目描述

[LeetCode 链接](https://leetcode.cn/problems/edit-distance/)

给你两个单词 `word1` 和 `word2`， 请返回将 `word1` 转换成 `word2` 所使用的最少操作数 。

你可以对一个单词进行如下三种操作：
*   插入一个字符
*   删除一个字符
*   替换一个字符

## 思路解析

这是一道经典的 **二维动态规划 (DP)** 题目。

### 状态定义
`dp[i][j]` 表示将 `word1` 的前 `i` 个字符转换成 `word2` 的前 `j` 个字符所需要的最少操作数。

### 状态转移
1.  如果 `word1[i-1] == word2[j-1]`（当前字符相等）：
    *   不需要操作，直接继承之前的状态：`dp[i][j] = dp[i-1][j-1]`。
2.  如果 `word1[i-1] != word2[j-1]`（当前字符不相等）：
    *   我们可以在插入、删除、替换中选择步数最少的一个，然后 +1。
    *   **删除** `word1[i]`：`dp[i-1][j] + 1`
    *   **插入** 字符以匹配 `word2[j]`：`dp[i][j-1] + 1`
    *   **替换** `word1[i]` 为 `word2[j]`：`dp[i-1][j-1] + 1`
    *   取最小值：`dp[i][j] = min(删除, 插入, 替换) + 1`

### 初始化
*   `dp[i][0] = i`：把 `word1` 前 `i` 个字符变成空串，需要删除 `i` 次。
*   `dp[0][j] = j`：把空串变成 `word2` 前 `j` 个字符，需要插入 `j` 次。

## 代码实现

```cpp
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
```
