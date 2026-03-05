#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minOperations(string s) {
        // 思路：交替字符串只有两种情况：
        // 1. "010101..." (以 '0' 开头)
        // 2. "101010..." (以 '1' 开头)
        
        // 我们可以只计算变成第一种情况需要的操作数 count
        // 那么变成第二种情况的操作数必然是 s.length() - count
        // 因为如果一个位置和 "0101..." 匹配，它必然和 "1010..." 不匹配，反之亦然。
        
        int count = 0;
        int n = s.length();
        
        for (int i = 0; i < n; ++i) {
            // 目标字符：如果 i 是偶数，应该是 '0'；如果 i 是奇数，应该是 '1'
            // 也就是 s[i] 应该等于 i % 2 对应的字符 ('0' 或 '1')
            // 如果不相等，说明需要修改
            if (s[i] - '0' != i % 2) {
                count++;
            }
        }
        
        // 返回 count 和 n - count 中的较小值
        return min(count, n - count);
    }
};
