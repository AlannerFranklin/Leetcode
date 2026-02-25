# 124. 二叉树中的最大路径和

## 题目描述

[LeetCode 链接](https://leetcode.cn/problems/binary-tree-maximum-path-sum/)

二叉树中的 **路径** 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。同一个节点在一条路径序列中 **至多出现一次** 。该路径 **至少包含一个** 节点，且不一定经过根节点。

**路径和** 是路径中各节点值的总和。

给你一个二叉树的根节点 `root` ，返回其 **最大路径和** 。

## 思路解析

这道题是经典的 **树形 DP** 问题，通常使用 **后序遍历（DFS）** 来解决。

### 核心思想

对于任意一个节点 `node`，经过它的最大路径有两种情况：

1.  **作为“拐点”（Root of Path）**：
    *   路径形态：`左子树路径 -> node -> 右子树路径`。
    *   路径和：`node->val + leftGain + rightGain`。
    *   这种情况下的路径**不能**再继续向上延伸（因为路径不能分叉），所以这种路径和只用来更新全局最大值 `maxSum`。

2.  **作为“贡献者”（Branch）**：
    *   路径形态：`node -> 左子树路径` 或 `node -> 右子树路径`（只能选一条最大的）。
    *   路径和：`node->val + max(leftGain, rightGain)`。
    *   这种情况下的路径可以继续向上延伸，连接到父节点，所以这是 `dfs` 函数的**返回值**。

### 关键细节

1.  **处理负数贡献**：
    *   如果子树计算出的最大路径和是负数，那么对于父节点来说，不如不走这条路（相当于断开）。
    *   所以 `leftGain = max(dfs(node->left), 0)`。

2.  **全局变量更新**：
    *   我们需要一个全局变量 `maxSum` 来记录遍历过程中出现过的最大路径和（即上面的情况 1）。
    *   初始化为 `INT_MIN`。

3.  **递归函数返回值**：
    *   返回给父节点的必须是**单向**的最大路径和（即上面的情况 2）。

## 代码实现

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    int maxSum = INT_MIN; // 全局最大值，初始化为最小值

    // 函数定义：返回以当前节点为起点的最大单向路径和
    int maxGain(TreeNode* node) {
        if (!node) return 0;

        // 1. 递归计算左右子树的最大单向贡献
        // 如果子树贡献是负数，直接取 0（相当于剪枝，不走那条路）
        int leftGain = max(maxGain(node->left), 0);
        int rightGain = max(maxGain(node->right), 0);

        // 2. 更新全局最大路径和 (作为“拐点”)
        // 当前节点 + 左边最好 + 右边最好
        // 这是一条完整的倒V型路径，不能再往上走了，所以只用来更新全局答案
        int priceNewpath = node->val + leftGain + rightGain;
        maxSum = max(maxSum, priceNewpath);

        // 3. 返回给父节点 (作为“分支”)
        // 只能选一边走：当前节点 + max(左边, 右边)
        // 这是一条直路，可以继续往上延伸
        return node->val + max(leftGain, rightGain);
    }

public:
    int maxPathSum(TreeNode* root) {
        maxGain(root);
        return maxSum;
    }
};
```
