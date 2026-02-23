#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 1. 终止条件：如果越过叶子节点，或者找到了 p 或 q
        if (root == nullptr || root == p || root == q) {
            return root;
        }
        
        // 2. 递归去左右子树找
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        
        // 3. 处理返回值
        if (left != nullptr && right != nullptr) {
            // p 和 q 分别在左右两边，当前节点就是最近公共祖先
            return root;
        }
        
        // 4. 谁不空回谁（都在一边）
        return left != nullptr ? left : right;
    }
};
