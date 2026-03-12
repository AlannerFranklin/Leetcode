#include <iostream>
#include <vector>
#include <queue>

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
    // 199. 二叉树的右视图 (Binary Tree Right Side View)
    // ==========================================
    // 方法 1: BFS (层序遍历)
    // 核心思想：每一层的最后一个节点就是右视图看到的节点。
    // 时间复杂度：O(N)
    // 空间复杂度：O(N) (队列最大宽度)
    vector<int> rightSideViewBFS(TreeNode* root) {
        vector<int> res;
        if (!root) return res;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                
                // 如果是该层最后一个节点，加入结果
                if (i == size - 1) {
                    res.push_back(node->val);
                }

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return res;
    }

    // 方法 2: DFS (深度优先遍历)
    // 核心思想：优先遍历右子树 (Root -> Right -> Left)。
    // 每一层只记录第一个遇到的节点。
    // 时间复杂度：O(N)
    // 空间复杂度：O(H) (递归深度)
    void dfs(TreeNode* node, int depth, vector<int>& res) {
        if (!node) return;
        
        // 如果当前深度还没有记录过节点，说明这个节点是该层最右边的
        if (depth == res.size()) {
            res.push_back(node->val);
        }
        
        dfs(node->right, depth + 1, res); // 先右
        dfs(node->left, depth + 1, res);  // 后左
    }

    vector<int> rightSideViewDFS(TreeNode* root) {
        vector<int> res;
        dfs(root, 0, res);
        return res;
    }
};

int main() {
    Solution sol;
    
    // Construct tree: [1, 2, 3, null, 5, null, 4]
    //    1
    //   / \
    //  2   3
    //   \   \
    //    5   4
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(4);

    vector<int> res = sol.rightSideViewBFS(root);
    cout << "Right Side View (BFS): ";
    for (int x : res) cout << x << " ";
    cout << endl;

    vector<int> res2 = sol.rightSideViewDFS(root);
    cout << "Right Side View (DFS): ";
    for (int x : res2) cout << x << " ";
    cout << endl;

    return 0;
}
