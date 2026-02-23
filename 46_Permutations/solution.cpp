#include <vector>

using namespace std;

class Solution {
    vector<vector<int>> res;
    
    void backtrack(vector<int>& nums, vector<int>& track, vector<bool>& used) {
        // 1. 结束条件：路径长度等于数组长度（选完了）
        if (track.size() == nums.size()) {
            res.push_back(track);
            return;
        }

        // 2. 遍历决策树的每个分支
        for (int i = 0; i < nums.size(); i++) {
            // 剪枝：如果这个数字已经选过了，跳过
            if (used[i]) continue;
            
            // 做选择
            track.push_back(nums[i]);
            used[i] = true;
            
            // 进入下一层
            backtrack(nums, track, used);
            
            // 撤销选择 (回溯的核心！)
            track.pop_back();
            used[i] = false;
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> track;
        vector<bool> used(nums.size(), false);
        backtrack(nums, track, used);
        return res;
    }
};
