#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.length();
        if (n == 0) return 0;
        
        // dp[i] 表示以 s[i] 结尾的最长有效括号子串的长度
        vector<int> dp(n, 0);
        int maxLen = 0;
        
        for (int i = 1; i < n; i++) {
            if (s[i] == ')') {
                // 情况一：...()
                // 直接匹配前面的 (
                if (s[i - 1] == '(') {
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                }
                // 情况二：...))
                // 这是一个嵌套结构，如 ((...))
                // 我们需要跳过中间已经匹配好的 dp[i-1] 长度，去看前面的字符
                else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') {
                    // dp[i] = 内部长度 + 当前这对括号(2) + 前面的有效长度
                    dp[i] = dp[i - 1] + 2 + 
                           ((i - dp[i - 1] >= 2) ? dp[i - dp[i - 1] - 2] : 0);
                }
                
                maxLen = max(maxLen, dp[i]);
            }
        }
        
        return maxLen;
    }
};
