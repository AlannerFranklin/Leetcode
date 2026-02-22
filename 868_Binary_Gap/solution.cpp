#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int binaryGap(int n) {
        int left = -1; // 上一个 1 的位置，初始化为 -1 表示未找到
        int ans = 0;   // 最大距离
        int i = 0;     // 当前位的索引
        
        while (n > 0) {
            // 如果当前位是 1
            if (n % 2 == 1) {
                // 如果之前已经遇到过 1，则计算距离
                if (left != -1) {
                    ans = std::max(ans, i - left);
                }
                // 更新上一个 1 的位置
                left = i;
            }
            // 右移一位（相当于除以 2）
            n /= 2;
            i++;
        }
        return ans;
    }
};
