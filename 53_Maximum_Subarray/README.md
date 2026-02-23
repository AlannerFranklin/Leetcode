# 53. 最大子数组和

## 题目链接
[LeetCode Link](https://leetcode.cn/problems/maximum-subarray/)

## 解题思路
### 动态规划 (Kadane's Algorithm)
这道题的核心在于：**什么时候应该抛弃前面的子数组，重新开始？**

假设我们维护一个 `current_sum`，表示以当前元素结尾的最大子数组和。
当我们遍历到 `nums[i]` 时，有两种选择：
1.  **接着前面的加**：如果前面的 `current_sum` 是正数，那加上它肯定比单干强。
2.  **自己另起炉灶**：如果前面的 `current_sum` 是负数，那加上它只会拖累自己，不如直接从 `nums[i]` 重新开始。

公式：`dp[i] = max(nums[i], dp[i-1] + nums[i])`

在这个过程中，我们需要时刻记录出现过的最大值 `max_sum`。
