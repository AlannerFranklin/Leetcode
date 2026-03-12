# Shopee 笔试题：最短子序列 (Shortest Window Subsequence)

## 题目分析

题目要求在 `source` 字符串中找到一个**最短的子串**，使得 `target` 是这个子串的**子序列**。这对应 LeetCode 727. Minimum Window Subsequence (Hard)。

## 你的代码 Bug 分析 (从 30% 到 10% 的原因)

你的代码主要问题在于逻辑变量 `right` 的维护不当，以及对“最大/最小”逻辑的混淆。

### 1. 为什么原代码 (30%) 能过一些？
*   原代码逻辑是 `if (max_len < right - left + 1)`，这是在找**最长**的符合条件的子串。这本身是错的。
*   但因为 `right` 是在循环外定义的，且没有在每次内层循环开始时重置：
    *   如果第一次匹配成功，`right` 被赋值。
    *   如果第二次匹配失败（没找到完整的 `target`），`right` **依然保持上一次的值**。
*   原代码计算 `len = right - left + 1`。如果 `left` 变大了（向右移），而 `right` 还是旧的（小的），`len` 会变成负数或很小的值。
*   因为你写的是 `max_len < ...`，负数肯定比 `max_len` 小，所以不会更新 `max_len`，也不会执行 `substr`。
*   **结论**：原代码虽然逻辑错（求最长），但因为“负数长度”被 `if` 挡住了，没有崩溃。它可能只输出了第一个找到的解（或者运气好输出了正确的），所以拿了 30% 分。

### 2. 为什么修改后 (10%) 分数更低？
*   你把条件改成了 `if (max_len > right - left + 1)`（求最短），并且 `max_len` 初始为 `INT_MAX`。
*   **致命 Bug**：当 `right` 没有更新（即当前 `i` 开头没找到解）时，`right` 还是旧值。
*   此时 `len = right - left + 1` 是一个**负数**（或者极小值）。
*   `INT_MAX > 负数` 是成立的！
*   代码执行 `s = source.substr(left, len)`。
*   `substr` 接收负数长度会抛出异常（Runtime Error），或者行为未定义。
*   **结论**：这就导致了程序崩溃，得分为 0（或者只有第一次匹配正确的 Case 能过），所以总分掉到了 10%。

## 解决方案

### 1. 修复你的 O(N^2) 逻辑 (`solution_fix.cpp`)
核心改动：
*   在内层循环前重置 `right = -1`。
*   只有当 `right != -1`（即找到了完整解）时，才计算长度并更新。

### 2. 优化解法：双指针/滑动窗口 (`solution_optimized.cpp`)
对于 $N, M$ 较大的情况，$O(N^2)$ 会超时。标准解法是 $O(S \times T)$ 或 $O(S)$ 的双指针法：
1.  **正向匹配**：在 S 中找到 T 的子序列，记录结束位置 `end`。
2.  **反向优化**：从 `end` 开始倒着匹配 T，找到最晚的开始位置 `start`。
3.  这样 `[start, end]` 就是一个局部最优解。
4.  下一次搜索从 `start + 1` 开始。

这个解法可以解决 LeetCode 727 (Hard)，是面试中的满分回答。

---

# Shopee 笔试题：将数组划分为 k 个相等的子集 (Max Partition into Equal Sum Subsets)

## 题目描述

给定一个整数数组 `nums`，将其划分为尽可能多的非空子集（组），使得每个子集的和相等。
求最大的分组数 `k`。
题目保证至少可以划分为 1 个分组（即原数组本身）。

## 你的代码问题 (`回溯算法.cpp` -> `max_partition_groups.cpp`)

你的原始代码尝试使用回溯法寻找一个和为 `S/k` 的子集，存在以下严重问题导致只过了 30%：
1.  **逻辑错误**：`sum_track * index == sum` 这个判断试图用乘法来验证子集和，这完全是错误的逻辑。
2.  **只找一个子集**：代码只验证了能否找到 *一个* 子集，而没有验证剩余元素是否也能被划分。
3.  **缺少 Pruning (剪枝)**：回溯法在没有强剪枝的情况下，对于 $N=16$ 左右的数据就会超时 (TLE)。
4.  **语法错误**：`fun` 函数缺少闭合括号，且 logic 混乱。

## 正确思路 (LeetCode 698 变种)

这是一个经典的 NP-Complete 问题（划分问题），但通常 $N$ 较小（如 $N \le 20$）。
我们需要找到最大的 $k$（从 $N$ 递减到 1），使得：
1.  总和 `Sum` 能被 $k$ 整除。
2.  数组能被划分为 $k$ 个和为 `Target = Sum / k` 的子集。

### 核心算法：回溯 + 剪枝 (Backtracking with Pruning)

我们从 $k=N$ 开始尝试，如果成功直接返回 $k$（因为要求最大）。
为了让回溯跑得快，必须加入以下 **强力剪枝**（这是通过的关键）：

1.  **降序排序** (`sort(rbegin, rend)`)：
    *   **原理**：先填大数，再填小数。
    *   **为什么有效？** 大数就像“大石头”，小数像“沙子”。先放石头容易卡住（快速发现无解），如果先放沙子，怎么放都行，会导致搜索树极其庞大。**尽早失败 = 剪枝**。

2.  **大数检查**：
    *   如果最大的数 `nums[0]` 比目标和 `target` 还大，那肯定分不出来，直接跳过。

3.  **组内去重** (`i > 0 && nums[i] == nums[i-1] && !visited[i-1]`)：
    *   **原理**：如果手里有两个 `5`（`5_a` 和 `5_b`），刚才试了 `5_a` 发现不行，那现在试 `5_b` 肯定也不行。
    *   **为什么有效？** 避免了大量重复计算。

4.  **首个元素失败剪枝** (`currentSum == 0` 时 return false)：
    *   **原理**：现在是一个新桶（空桶）。我尝试把 `nums[i]` 放到这个新桶里，结果递归下去发现**无解**。
    *   **结论**：那 `nums[i]` 还能放哪呢？所有桶都是一样的（对称的）。如果它不能作为新桶的第一个元素，那它就永远没地方放了。所以整个方案直接失败，**不需要尝试把它留给下一个桶**。

5.  **完美匹配失败剪枝** (`currentSum + nums[i] == target` 时 return false)：
    *   **原理**：如果 `nums[i]` 刚好能填满当前桶，那就填进去。如果填进去后，剩下的数字怎么拼都拼不出来，那说明这个 `nums[i]` **不应该** 在这里填满？
    *   **结论**：其实这是一种贪心策略。对于“刚好填满”的情况，通常优先满足。如果这都行不通，换个更小的数来填满通常也没用（或者效率极低）。

### 代码实现

请参考 `max_partition_groups.cpp`。

```cpp
// 核心回溯函数
bool canPartition(vector<int>& nums, vector<bool>& visited, int index, int k, int currentSum, int target) {
    if (k == 1) return true; // 剩下一组不用验，肯定满足
    if (currentSum == target) return canPartition(nums, visited, 0, k - 1, 0, target); // 填满一组，找下一组
    
    for (int i = index; i < nums.size(); ++i) {
        if (visited[i]) continue;
        // 剪枝：去重
        if (i > 0 && nums[i] == nums[i-1] && !visited[i-1]) continue;
        if (currentSum + nums[i] > target) continue;

        visited[i] = true;
        if (canPartition(nums, visited, i + 1, k, currentSum + nums[i], target)) return true;
        visited[i] = false;

        // 强力剪枝
        if (currentSum == 0) return false;
        if (currentSum + nums[i] == target) return false;
    }
    return false;
}
```

---

# Shopee 笔试题：分割数组的最大值最小化 (Split Array Largest Sum)

## 题目描述

给定一个长度为 `n` ($1 \le n \le 10^6$) 的数组，将其按顺序分割成 `m` ($1 \le m \le n$) 个非空子数组。
要求最小化这些子数组中的**最大和**。
求这个最小的最大和 `k`。

## 算法分析

你猜这道题是动态规划 (DP)，**直觉很敏锐，但对于这道题的数据范围来说，DP 并不是最优解，甚至会超时**。

### 1. 为什么 DP 会超时？
*   DP 状态通常定义为 `dp[i][j]`：前 `i` 个数分成 `j` 组的最小最大和。
*   时间复杂度通常是 $O(n^2 \cdot m)$ 或优化后 $O(n \cdot m)$。
*   题目给定 $n \le 10^6$，这意味着 $O(n \cdot m)$ 可能会达到 $10^{12}$ 级别，肯定会 **Time Limit Exceeded (TLE)**。

### 2. 正确解法：二分查找答案 (Binary Search on Answer)

这是一种非常强大的解题模式，通常用于“求最大值中的最小值”或“求最小值中的最大值”这类 Min-Max 问题。

#### 核心思想：猜答案 + 验证

与其直接计算“最小的最大和是多少”，不如反过来想：
> **如果给你一个最大容量限制 $X$，你能判断它是否可行吗？**

*   **验证 (Check Function)**：
    *   如果我们规定每个袋子最多只能装 $X$ 的重量。
    *   我们可以用贪心的方法：从头开始装，装不下就换个新袋子。
    *   如果最后用的袋子数量 $\le m$，说明 $X$ 这个容量**太大了**（或者刚好），我们可以尝试**更小**的容量。
    *   如果用的袋子数量 $> m$，说明 $X$ 这个容量**太小了**，必须**增大**容量。

*   **单调性 (Monotonicity)**：
    *   如果容量 $X$ 可行，那么 $X+1, X+2 \dots$ 肯定都可行（袋子只会用得更少）。
    *   如果容量 $X$ 不可行，那么 $X-1, X-2 \dots$ 肯定都不可行（袋子只会用得更多）。
    *   这就是二分查找的基础：答案在一个有序的区间内。

*   **复杂度**：
    *   验证一次需要遍历数组，耗时 $O(N)$。
    *   二分查找的范围是 $[\max(nums), \text{sum}(nums)]$。假设总和是 $S$，二分次数是 $\log S$。
    *   总复杂度：$O(N \cdot \log S)$。
    *   对于 $N=10^6, S \approx 10^9$，计算量约为 $10^6 \times 30 \approx 3 \times 10^7$，非常快。

### LeetCode 难度评级与复盘

| 题目 | LeetCode 对应 | 难度 | 评价 |
| :--- | :--- | :--- | :--- |
| **最短子序列** | [727. Minimum Window Subsequence](https://leetcode.cn/problems/minimum-window-subsequence/) | **Hard -> Medium** | **逻辑其实不难**。$O(N^2)$ 的暴力解法在 $N \le 2000$ 时是完全可行的。你的思路是对的，只是少了一个重置变量的操作。 |
| **最大分组数** | [698. Partition to K Equal Sum Subsets](https://leetcode.cn/problems/partition-to-k-equal-sum-subsets/) | **Hard** | **剪枝是核心**。这道题如果不背剪枝策略，临场很难写出不超时的代码。属于“背诵题”。 |
| **分割数组** | [410. Split Array Largest Sum](https://leetcode.cn/problems/split-array-largest-sum/) | **Hard** | **思维题**。想不到“二分答案”这个点就做不出来，想到了就是 Easy。 |

### 回溯剪枝速记表 (Cheat Sheet)

觉得剪枝太麻烦？只记这 **3 条核心** 就够了：

1.  **先大后小** (`sort desc`)：
    *   *口诀*：先装大石头，后填细沙子。
2.  **去重** (`nums[i] == nums[i-1]`)：
    *   *口诀*：这个不行，那长得一样的肯定也不行。
3.  **首项定生死** (`currentSum == 0`)：
    *   *口诀*：如果这个数连空桶的第一位都做不了，那它就废了，直接 Return。

### 代码实现

请参考 `split_array_min_max.cpp`。

```cpp
bool check(const vector<int>& nums, int m, long long max_capacity) {
    int bags = 1;
    long long current_sum = 0;
    for (int num : nums) {
        if (current_sum + num > max_capacity) {
            bags++;
            current_sum = num;
            if (bags > m) return false;
        } else {
            current_sum += num;
        }
    }
    return true;
}

// 主函数使用二分查找
long long left = max_element;
long long right = total_sum;
while (left <= right) {
    long long mid = left + (right - left) / 2;
    if (check(nums, m, mid)) {
        ans = mid;
        right = mid - 1; // 尝试更小的
    } else {
        left = mid + 1; // 容量不够，需要更大
    }
}
```
