# 3859. 计数满足条件的子数组 (Count Subarrays with K Different Integers and Frequency M)

[题目链接](https://leetcode.cn/problems/count-subarrays-with-k-distinct-integers/description/) (近似链接，实际为竞赛题)

## 题目描述

给你一个整数数组 `nums` 和两个整数 `k` 和 `m`。
返回一个整数，表示满足以下条件的子数组的数量：
1.  子数组恰好包含 `k` 个不同的整数。
2.  在子数组中，每个不同的整数至少出现 `m` 次。

## 解题思路 (Correct Sliding Window)

这道题其实是一个经典的 **"恰好 K 个"** 问题的变种。
通常解决 "恰好 K 个" 的思路是转化为：
`count(恰好 K) = count(至少 K) - count(至少 K+1)`
或者
`count(恰好 K) = count(最多 K) - count(最多 K-1)`

在这里，我们定义一个辅助函数 `calc(target_k)`，用于统计 **满足频次 >= m 的不同整数个数 至少为 target_k** 的子数组数量。

### 辅助函数逻辑 `calc(target_k)`
我们维护一个滑动窗口 `[left, right]`：
1.  **入窗口**：右指针 `right` 向右移动，将 `nums[right]` 加入窗口，更新计数。如果某个数的频次达到 `m`，则满足条件的整数个数 `ge_m` 加 1。
2.  **出窗口 (收缩)**：当窗口内满足条件的整数个数 `ge_m >= target_k` 时，说明当前窗口（以及所有以 `left` 为起点、`right` 为终点的更长窗口）都满足条件。
    *   我们可以尝试收缩左指针 `left`，直到 `ge_m < target_k` 为止。
    *   在收缩的过程中，每一个被移除的 `left`，都代表一个合法的子数组起点（对于当前的 `right`）。
    *   也就是：对于当前的 `right`，有 `left` 个子数组满足 `ge_m >= target_k`。
3.  **累加答案**：`ans += left`。

### 最终答案
`calc(k) - calc(k + 1)`
*   `calc(k)`：满足频次 >= m 的数至少有 k 个。
*   `calc(k + 1)`：满足频次 >= m 的数至少有 k+1 个。
*   相减即得：满足频次 >= m 的数 **恰好有 k 个**。

注意：这个解法其实稍微简化了题目条件。题目要求是“子数组里恰好有 k 个不同整数，且这 k 个数频次都 >= m”。
如果子数组里还有其他频次 < m 的数，它们不被计入 `ge_m`，但会被计入 `cnt.size()`。
但在 `calc` 函数里，只要 `ge_m >= k` 就行，多余的杂质数不影响“至少”的逻辑。
当相减时，刚好把那些多余的情况抵消掉了。

```cpp
class Solution {
    // ... 见 solution.cpp ...
};
```
