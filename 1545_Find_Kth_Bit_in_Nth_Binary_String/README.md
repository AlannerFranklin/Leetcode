# 1545. 找出第 N 个二进制字符串中的第 K 位 (Find Kth Bit in Nth Binary String)

[LeetCode 链接](https://leetcode.cn/problems/find-kth-bit-in-nth-binary-string/)

## 题目描述

给你两个正整数 `n` 和 `k`，二进制字符串 `Sn` 的形成规则如下：
*   `S1 = "0"`
*   当 `i > 1` 时，`Si = Si-1 + "1" + reverse(invert(Si-1))`

其中 `+` 表示串联操作，`reverse(x)` 返回反转 `x` 后得到的字符串，而 `invert(x)` 则会翻转 `x` 中的每一位（0 变为 1，而 1 变为 0）。

请你返回 `Sn` 的 第 `k` 位字符。

## 思路解析

### 方法一：模拟法 (你的思路)

虽然题目中 `n` 最大只到 20，生成的字符串长度约为 $2^{20} \approx 10^6$ (100万字符)，直接模拟生成字符串在内存和时间上都是勉强可行的。但是代码实现上有一些细节需要注意。

**你的代码中的问题：**
1.  **返回值类型错误**：`char* str(...)` 应该返回 `string`。
2.  **reverse 用法错误**：`reverse(s1.begin(), s1.end())` 是就地修改，返回 `void`，不能赋值给 `s2`。
3.  **循环逻辑**：题目是从 `S1` 推导到 `Sn`，需要循环 `n-1` 次。
4.  **索引问题**：题目中的 `k` 是从 1 开始的，而字符串索引是从 0 开始的，所以最后应该返回 `s[k-1]`。

### 方法二：递归法 (推荐)

我们可以利用 `Sn` 的构造规则，直接计算第 `k` 位，而不需要生成整个字符串。这种方法时间复杂度为 $O(n)$，空间复杂度为 $O(n)$ (递归栈)。

**观察规律：**
`Sn` 的长度是 $L_n = 2^n - 1$。
`Sn` 的结构是：`[ 左半部分 (Sn-1) ] [ 中间位 '1' ] [ 右半部分 (reverse(invert(Sn-1))) ]`

我们可以把 `k` 分为三种情况：
1.  **`k` 刚好在中间**：即 $k = \lceil L_n / 2 \rceil$。根据规则，中间位总是添加的那个 `"1"`。直接返回 `'1'`。
2.  **`k` 在左半部分**：即 $k < \lceil L_n / 2 \rceil$。这就完全等同于在 `Sn-1` 中找第 `k` 位。递归调用 `findKthBit(n-1, k)`。
3.  **`k` 在右半部分**：即 $k > \lceil L_n / 2 \rceil$。这部分是 `Sn-1` 先**取反**再**反转**得到的。
    *   **反转**意味着：第 `k` 位对应 `Sn-1` 中的第 `Len - k + 1` 位。
    *   **取反**意味着：我们需要把找到的那一位（'0'变'1'，'1'变'0'）。
    *   所以递归调用 `findKthBit(n-1, Len - k + 1)`，然后把结果取反。

**递归终止条件：**
当 `n = 1` 时，`S1 = "0"`，直接返回 `'0'`。

## 代码实现 (递归法)

```cpp
class Solution {
public:
    char findKthBit(int n, int k) {
        if (n == 1) return '0';
        
        int len = (1 << n) - 1; // Sn 的长度
        int mid = len / 2 + 1;  // 中间位置
        
        if (k == mid) {
            return '1';
        } else if (k < mid) {
            return findKthBit(n - 1, k);
        } else {
            // 右半部分：对称位置取反
            char bit = findKthBit(n - 1, len - k + 1);
            return bit == '0' ? '1' : '0';
        }
    }
};
```
