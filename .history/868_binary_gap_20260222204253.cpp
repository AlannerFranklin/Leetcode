#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int binaryGap(int n) {
        // 记录上一个 1 的位置，初始化为 -1 表示未找到
        int last = -1; 
        int ans = 0;   
        int i = 0;     // 当前位的索引 (从低位到高位)
        
        while (n > 0) {
            // 如果当前位是 1
            if (n % 2 == 1) {
                // 如果之前已经遇到过 1，计算距离
                if (last != -1) {
                    ans = std::max(ans, i - last);
                }
                // 更新上一个 1 的位置
                last = i;
            }
            n /= 2; // 右移一位
            i++;
        }
        return ans;
    }
};
