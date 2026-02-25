# 415. 字符串相加

## 题目描述

[LeetCode 链接](https://leetcode.cn/problems/add-strings/)

给定两个字符串形式的非负整数 `num1` 和 `num2` ，计算它们的和并同样以字符串形式返回。

你不能使用任何內建的用于处理大整数的库（比如 `BigInteger`）， 也不能直接将输入的字符串转换为整数形式。

## 思路解析

模拟人工竖式加法。

1.  **双指针**：`i` 指向 `num1` 末尾，`j` 指向 `num2` 末尾。
2.  **进位处理**：维护一个 `carry` 变量存储进位。
3.  **循环条件**：只要 `i >= 0` 或 `j >= 0` 或 `carry != 0`，就继续计算。这意味着即使两个数字都遍历完了，如果还有进位，也要继续处理。
4.  **补零**：如果某个指针已经越界（小于 0），则对应位置的数字视为 0。
5.  **拼接与反转**：每次计算出的个位数字拼接到结果字符串末尾，最后将整个字符串反转。

## 代码实现

```cpp
class Solution {
public:
    string addStrings(string num1, string num2) {
        string res = "";
        int i = num1.size() - 1;
        int j = num2.size() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry != 0) {
            int x = (i >= 0) ? num1[i] - '0' : 0;
            int y = (j >= 0) ? num2[j] - '0' : 0;
            
            int sum = x + y + carry;
            res += to_string(sum % 10);
            carry = sum / 10;
            
            i--;
            j--;
        }
        
        reverse(res.begin(), res.end());
        return res;
    }
};
```
