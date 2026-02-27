#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numSteps(string s) {
        // 思路：从后往前遍历
        // 遇到 '0'：如果是偶数，除以 2（step+1）
        // 遇到 '1'：如果是奇数，加 1 变成偶数再除以 2（step+2），并且产生进位
        // 进位 carry 会一直影响前面的位
        
        int steps = 0;
        int carry = 0;
        
        // 从最后一位遍历到第 1 位（下标 1），因为第 0 位是最高位，最后处理
        for (int i = s.size() - 1; i > 0; i--) {
            // 当前位的值加上进位
            // 如果是 0 + 0 = 0 (偶数) -> 除2 -> step+1, carry=0
            // 如果是 1 + 0 = 1 (奇数) -> 加1变偶数再除2 -> step+2, carry=1
            // 如果是 0 + 1 = 1 (奇数) -> 加1变偶数再除2 -> step+2, carry=1
            // 如果是 1 + 1 = 2 (偶数) -> 相当于变成0且进位 -> 除2 -> step+1, carry=1
            
            if (s[i] - '0' + carry == 1) {
                steps += 2;
                carry = 1;
            } else {
                steps += 1;
            }
        }
        
        // 处理最高位 s[0]
        // 如果最后还有进位 (carry=1)，说明 s[0] (也就是 '1') + carry = 2 (10)
        // 这时变成了 10，还需要再除以 2 一次，变成 1
        // 所以如果 carry=1，还需要 +1 步
        return steps + carry;
    }
};
