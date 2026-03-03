#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    char findKthBit(int n, int k) {
        // 思路：
        // 第 n 个字符串 Sn 的长度是 2^n - 1。
        // Sn = Sn-1 + "1" + reverse(invert(Sn-1))
        // 我们可以利用这种递归结构，不需要生成整个字符串。
        
        // 基本情况：n=1 时，S1="0"，k只能是1，返回'0'。
        if (n == 1) {
            return '0';
        }
        
        // 计算 Sn 的长度 len = 2^n - 1
        int len = (1 << n) - 1;
        
        // 中间位置 mid = len / 2 + 1 (1-based index)
        // 例如 n=3, len=7, mid=4. S3="011 1 001"
        int mid = len / 2 + 1;
        
        if (k == mid) {
            // 如果 k 正好在中间，根据规则，中间位总是 '1'
            return '1';
        } else if (k < mid) {
            // 如果 k 在左半部分，完全等同于在 Sn-1 中找第 k 位
            return findKthBit(n - 1, k);
        } else {
            // 如果 k 在右半部分，它是 Sn-1 反转并取反后的结果
            // 它的原位置在 Sn-1 中是对称的
            // 比如 len=7, k=6 (倒数第2个), 对应左半边的第 2 个 (len - k + 1)
            // 找到原来的位后，记得取反 ('0'->'1', '1'->'0')
            char bit = findKthBit(n - 1, len - k + 1);
            return bit == '0' ? '1' : '0';
        }
    }
};
