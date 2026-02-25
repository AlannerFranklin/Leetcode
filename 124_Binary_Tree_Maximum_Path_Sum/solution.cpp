#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

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
