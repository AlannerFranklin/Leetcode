#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

// 优化解法：Two-Pass Greedy (O(S * T) 或 O(S))
// 这是 LeetCode 727. Minimum Window Subsequence 的标准解法
// 核心思想：
// 1. 正向寻找：在 S 中找到一个包含 T 的子序列，得到结束位置 end。
// 2. 反向优化：从 end 开始向左回溯，找到该子序列的最晚开始位置 start。
//    这样 [start, end] 就是以 end 为结尾的最短窗口。

int main() {
    string S, T;
    cin >> S >> T;
    
    int n = S.size(), m = T.size();
    int min_len = INT_MAX;
    string result = "";
    
    int s_index = 0; // S 的指针
    int t_index = 0; // T 的指针
    
    while (s_index < n) {
        if (S[s_index] == T[t_index]) {
            t_index++;
            
            // 当 T 全部匹配完时
            if (t_index == m) {
                // 1. 此时 s_index 是当前窗口的结束位置 (end)
                int end = s_index;
                
                // 2. 反向优化：寻找最优的起点 (start)
                int temp_t = m - 1;
                int start = s_index;
                
                while (temp_t >= 0) {
                    if (S[start] == T[temp_t]) {
                        temp_t--;
                    }
                    start--;
                }
                start++; // 回退一步，指向匹配的第一个字符
                
                // 3. 更新最小窗口
                int len = end - start + 1;
                if (len < min_len) {
                    min_len = len;
                    result = S.substr(start, len);
                }
                
                // 4. 重要优化：下一次搜索从 start + 1 开始
                // 这样可以发现重叠的更优解
                s_index = start; 
                t_index = 0;
            }
        }
        s_index++;
    }
    
    cout << result << endl;
    return 0;
}
