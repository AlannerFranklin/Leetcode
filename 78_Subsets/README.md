# 78. 子集 (Subsets)

[LeetCode 链接](https://leetcode.cn/problems/subsets/)

## 题目描述

给你一个整数数组 `nums` ，数组中的元素 互不相同 。返回该数组所有可能的（幂集）。
解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

## 你的代码错误分析

你的代码有几个关键问题导致逻辑混乱和结果错误（或者栈溢出/死循环）：

### 1. 递归参数传递错误 (Critical Error)

```cpp
// 你的代码
track.push_back(board[col]); 
backtrack(board, row + 1); // 错误！
track.pop_back(); 
```

*   **问题**：你在循环中选了第 `col` 个元素，但是递归调用时却传了 `row + 1`。
*   **后果**：假设 `row=0`，你选了 `nums[2]` (col=2)，你应该从 `nums[3]` 开始选下一个。但你传了 `row+1` (即 1)，导致下一层递归又从 `nums[1]` 开始选。这意味着你可以选 `[2, 1]`，这不仅导致重复子集（因为子集问题通常按顺序选，`[1, 2]` 和 `[2, 1]` 是一样的），甚至可能导致无限循环或栈溢出（如果逻辑没写对）。
*   **修正**：应该传 `col + 1`（或者代码里的 `i + 1`）。表示既然选了第 `i` 个数，下一个数只能从 `i + 1` 开始选。

### 2. `res.push_back(track)` 的位置

```cpp
// 你的代码
res.push_back(track); // 放这里是对的，但是逻辑要理顺
int n = board.size();
for(int col = row; col < n; col++) {
    track.push_back(board[col]);
    backtrack(board, row + 1); // 递归调用
    track.pop_back(); 
}
```

*   **问题**：你的 `backtrack` 函数内部的 `res.push_back` 和下面的循环逻辑有点打架。
*   **子集问题特点**：每个递归树的**节点**（不仅仅是叶子节点）都是一个合法的子集。
    *   刚进入函数（没选任何数），`track` 是空集 `[]`，加入结果。
    *   选了 `1`，进入递归，`track` 是 `[1]`，加入结果。
    *   选了 `2`，进入递归，`track` 是 `[1, 2]`，加入结果。
*   **修正**：`res.push_back(track)` 应该放在函数最开头，记录当前路径。

### 3. 变量命名建议

*   **`board` -> `nums`**：这不是棋盘问题，是一维数组，叫 `nums` 更直观。
*   **`row` -> `start`**：这不是行号，是当前可选元素的**起始索引**。
*   **`col` -> `i`**：这不是列号，是当前遍历到的元素索引。

## 正确代码

```cpp
class Solution {
    vector<vector<int>> res;
    vector<int> track;

public:
    vector<vector<int>> subsets(vector<int>& nums) {
        backtrack(nums, 0);
        return res;
    }

    void backtrack(vector<int>& nums, int start) {
        // 前序位置：每个节点都是一个子集
        res.push_back(track);

        // 从 start 开始遍历，避免重复选择之前的元素
        for (int i = start; i < nums.size(); i++) {
            // 做选择
            track.push_back(nums[i]);
            // 递归：下一个数从 i + 1 开始选
            backtrack(nums, i + 1);
            // 撤销选择
            track.pop_back();
        }
    }
};
```

## 复杂度分析

*   **时间复杂度**：$O(N \cdot 2^N)$。每个元素都有选或不选两种可能，共 $2^N$ 个子集，每个子集拷贝需要 $O(N)$。
*   **空间复杂度**：$O(N)$。递归栈深度为 N。
