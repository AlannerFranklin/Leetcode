#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        backtrack(nums, 0);
        return res;
    }

private:
    vector<vector<int>> res;
    vector<int> track;

    void backtrack(vector<int>& nums, int start) {
        // 子集问题不需要显式的结束条件
        // 因为我们会在进入 backtrack 时就把当前的 track 加入结果
        // 这意味着每个节点（包括根节点空集）都是一个子集
        res.push_back(track);

        // 这里的循环变量 i 表示从 start 开始选择
        // 注意：不是 row，这里的一维数组，我们只需要保证不回头选就行
        for (int i = start; i < nums.size(); i++) {
            // 做选择
            track.push_back(nums[i]);
            
            // 递归进入下一层
            // 关键错误修正：这里应该是 backtrack(nums, i + 1)
            // 而不是 backtrack(nums, row + 1)
            // 因为我们选了 nums[i]，下一个要从 i+1 开始选
            backtrack(nums, i + 1);
            
            // 撤销选择
            track.pop_back();
        }
    }
};
