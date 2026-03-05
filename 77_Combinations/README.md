# 77. 组合 (Combinations)

[LeetCode 链接](https://leetcode.cn/problems/combinations/)

## 题目描述

给定两个整数 `n` 和 `k`，返回范围 `[1, n]` 中所有可能的 `k` 个数的组合。
你可以按 任何顺序 返回答案。

## 你的代码错误分析

你的代码主要问题在于 **C++ `vector` 的使用错误 (Runtime Error)**，而不是算法逻辑错误。

### 1. `vector` 未初始化大小直接访问 (Critical Error)

```cpp
// 你的代码
vector<int> board; // 这里 board 是空的，size 为 0
for(int i = 0; i < n; i++) {
    board[i] = i + 1; // 错误！访问越界
}
```

*   **问题**：`board` 声明时是空的，你直接用 `board[i]` 赋值会导致**越界访问**（Segmentation Fault 或 Undefined Behavior）。
*   **修正**：应该用 `vector<int> board(n);` 初始化大小，或者用 `board.push_back(i + 1)`。
*   **更好的修正**：其实这道题**根本不需要 `board` 数组**！题目就是求 `1` 到 `n` 的组合，直接在回溯时用 `int` 变量遍历即可。

### 2. 回溯参数冗余

```cpp
void backtrack(vector<int>& board, int row, int k)
```
*   `board` 是多余的，直接传 `n` 即可。
*   `row` 建议改名为 `start`，表示从哪个数字开始选。

## 正确代码

```cpp
class Solution {
    vector<vector<int>> res;
    vector<int> track;

public:
    vector<vector<int>> combine(int n, int k) {
        // 直接从 1 开始回溯
        backtrack(n, k, 1);
        return res;
    }

    void backtrack(int n, int k, int start) {
        // 结束条件：选够了 k 个数
        if (track.size() == k) {
            res.push_back(track);
            return;
        }

        // 剪枝优化：
        // 如果剩下的数不够凑满 k 个，就不需要继续遍历了
        // 还需要选 k - track.size() 个数
        // 所以 i 最多只能到 n - (k - track.size()) + 1
        
        for (int i = start; i <= n; i++) {
            track.push_back(i);
            backtrack(n, k, i + 1);
            track.pop_back();
        }
    }
};
```

## 复杂度分析

*   **时间复杂度**：$O(C(N, K) \cdot K)$。组合数 $C(N, K)$ 种结果，每个结果拷贝耗时 $O(K)$。
*   **空间复杂度**：$O(K)$。递归栈深度为 K。
