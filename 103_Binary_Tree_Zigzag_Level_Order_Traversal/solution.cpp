#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        // 1. 边界检查
        if (!root) return {}; 
        
        vector<vector<int>> result; // 存最终的大结果
        queue<TreeNode*> q;
        q.push(root);
        
        // 标记方向：true=左到右，false=右到左
        bool isLeftToRight = true;
        
        while (!q.empty()) {
            int size = q.size(); // 这一层有多少个节点
            vector<int> levelRes; // 存这一层的小结果
            
            // 处理这一层的所有节点
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                // 收集值
                levelRes.push_back(node->val);
                
                // 孩子入队（这里永远是先左后右，顺序不变！）
                // 无论是否翻转，下一层的构建顺序是固定的
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            // 这一层收集完了，看看要不要翻转？
            if (!isLeftToRight) {
                reverse(levelRes.begin(), levelRes.end());
            }
            
            // 把这一层的结果加入最终结果
            result.push_back(levelRes);
            
            // 下一层方向取反
            isLeftToRight = !isLeftToRight;
        }
        
        return result;
    }
};
