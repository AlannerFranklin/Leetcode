#include <iostream>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // ==========================================
    // 617. 合并二叉树 (Merge Two Binary Trees)
    // ==========================================
    // 核心思想：递归 (DFS)
    // 1. 如果两个节点都为空，返回空。
    // 2. 如果其中一个为空，返回另一个。
    // 3. 如果都不为空，创建新节点（或复用 root1），值为 val1 + val2。
    // 4. 递归合并左子树和右子树。
    // 时间复杂度：O(min(N, M))
    // 空间复杂度：O(min(H1, H2))
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (!root1) return root2;
        if (!root2) return root1;

        // 复用 root1 节点
        root1->val += root2->val;
        
        root1->left = mergeTrees(root1->left, root2->left);
        root1->right = mergeTrees(root1->right, root2->right);
        
        return root1;
    }
};

// Helper: Pre-order traversal print
void printTree(TreeNode* root) {
    if (!root) {
        cout << "null ";
        return;
    }
    cout << root->val << " ";
    printTree(root->left);
    printTree(root->right);
}

int main() {
    Solution sol;
    
    // Tree 1: 1 (left: 3 (left: 5), right: 2)
    TreeNode* t1 = new TreeNode(1);
    t1->left = new TreeNode(3);
    t1->right = new TreeNode(2);
    t1->left->left = new TreeNode(5);

    // Tree 2: 2 (left: 1 (right: 4), right: 3 (right: 7))
    TreeNode* t2 = new TreeNode(2);
    t2->left = new TreeNode(1);
    t2->right = new TreeNode(3);
    t2->left->right = new TreeNode(4);
    t2->right->right = new TreeNode(7);

    TreeNode* merged = sol.mergeTrees(t1, t2);
    cout << "Merged Tree (Pre-order): ";
    printTree(merged);
    cout << endl;

    return 0;
}
