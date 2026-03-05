# 698. 划分为k个相等的子集 (Partition to K Equal Sum Subsets)

[LeetCode 链接](https://leetcode.cn/problems/partition-to-k-equal-sum-subsets/)

## 题目描述

给定一个整数数组 `nums` 和一个正整数 `k`，找出是否有可能把这个数组分成 `k` 个非空子集，其总和都相等。

## 解法分析

这道题是经典的 **NP-Complete** 问题（子集和问题的变种），没有多项式时间复杂度的解法，只能通过回溯（Backtracking）来穷举。但是，穷举的策略和剪枝技巧对运行时间影响巨大。

### 方法一：基于桶的视角 (Bucket Perspective)
**思路**：
我们有 `k` 个桶，每个桶的目标和是 `sum / k`。
对于 `nums` 中的每个数字，我们尝试把它放入 `k` 个桶中的某一个。

**复杂度**：
每个数字有 `k` 种选择，共有 `n` 个数字。时间复杂度约为 $O(k^n)$。
这在 `k` 较大时非常慢。

**代码片段**：
```cpp
// 尝试把 nums[index] 放入 bucket[i]
for (int i = 0; i < k; i++) {
    if (bucket[i] + nums[index] <= target) {
        bucket[i] += nums[index];
        backtrack(index + 1);
        bucket[i] -= nums[index];
    }
}
```

### 方法二：基于数字的视角 (Number Perspective)
**思路**：
我们需要填满 `k` 个桶。
我们一个桶一个桶地填。对于当前桶，我们遍历 `nums`，尝试选择一些数字把它填满。填满后，再填下一个桶。

**复杂度**：
这仍然是指数级，但比方法一稍微好控制一些，因为我们可以用 `used` 数组来标记数字是否被使用。

### 方法三：状态压缩 + 记忆化搜索 (Bitmask + Memoization) - **推荐解法**
这是基于方法二的优化。
既然我们是一个桶一个桶填，那么“当前桶已经装了多少”以及“哪些数字已经被用过了”就构成了我们的状态。
*   `used`：一个整数，第 `i` 位为 1 表示 `nums[i]` 已被使用。
*   `bucket`：当前桶已装的重量。实际上 `bucket` 可以由 `used` 推导出来：`sum(used) % target`。

**关键优化**：
我们只需要记录 `used` 状态即可。当 `bucket == target`（填满一个桶）时，我们将剩下的 `used` 状态记入 `memo`。如果以后再次遇到这个 `used` 状态，直接返回结果。

**复杂度**：
状态数量是 $2^n$（`used` 的所有可能）。每次状态转移需要遍历 `n` 个数字。
总时间复杂度：$O(n \cdot 2^n)$。
对于 $n=16$，这是一个完全可以接受的复杂度。

**代码核心**：
```cpp
bool backtrack(int k, int bucket, ..., int used, int target) {
    if (k == 0) return true;
    if (bucket == target) {
        // 填满一个桶，记下来，开始填下一个
        if (memo.count(used)) return memo[used];
        bool res = backtrack(k-1, 0, ..., used, target);
        memo[used] = res;
        return res;
    }
    // ... 尝试装入数字 ...
}
```

### 为什么位运算比 vector<bool> 快？
1.  **空间**：`int` 只有 4 字节，`vector<bool>` 需要动态分配内存且占用更多空间。
2.  **哈希**：`int` 可以直接作为 `unordered_map` 的 key，而 `vector<bool>` 不能直接做 key（需要转 string 或自定义 hash），转换过程非常耗时。
3.  **操作**：位运算（与、或、异或）是 CPU 指令级的，极其快速。

## 总结
*   对于 $N \le 16$ 这种小数据范围的集合问题，**状态压缩 (Bitmask)** 是标准解法。
*   它将 $O(N!)$ 或 $O(K^N)$ 的复杂度降低到了 $O(N \cdot 2^N)$。
