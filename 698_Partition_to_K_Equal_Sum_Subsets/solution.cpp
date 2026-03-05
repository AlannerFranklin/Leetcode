#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_map>
#include <functional>

using namespace std;

// 方法 3：状态压缩 + 记忆化回溯 (最优解)
class Solution {
    unordered_map<int, bool> memo;

public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        if (k > nums.size()) return false;
        int sum = 0;
        for (int v : nums) sum += v;
        if (sum % k != 0) return false;
        
        int target = sum / k;
        int used = 0; // 状态压缩，记录哪些数字被使用了
        
        // 排序有助于剪枝，大的数字先放，如果放不下能更早发现
        // 注意：这里其实不需要排序，因为我们是遍历所有数字
        // 但是对于方法1和2，排序非常重要
        
        return backtrack(k, 0, nums, 0, used, target);
    }

    // k: 还需要填满几个桶
    // bucket: 当前桶已经装了多少
    // start: 从 nums 的哪个索引开始尝试装入当前桶
    // used: 位掩码，记录哪些数字已经被用过了
    // target: 每个桶的目标和
    bool backtrack(int k, int bucket, vector<int>& nums, int start, int used, int target) {
        // base case: 所有桶都填满了
        if (k == 0) return true;
        
        // 当前桶装满了，开始装下一个桶
        // 下一个桶从 nums[0] 开始尝试（start 重置为 0）
        // 这里的 bucket 重置为 0
        if (bucket == target) {
            // 记忆化：如果当前 used 状态已经计算过，直接返回
            // 注意：我们只需要记录“当 bucket==0 时的 used 状态”
            // 因为 bucket != 0 时的中间状态太多了，且对结果影响不如 bucket==0 时直接
            if (memo.count(used)) return memo[used];
            
            bool res = backtrack(k - 1, 0, nums, 0, used, target);
            memo[used] = res;
            return res;
        }
        
        // 尝试装入数字
        for (int i = start; i < nums.size(); i++) {
            // 剪枝 1：如果第 i 位已经被用过
            if (((used >> i) & 1) == 1) continue;
            
            // 剪枝 2：如果装入 nums[i] 超过目标和
            if (bucket + nums[i] > target) continue;
            
            // 做选择
            used |= (1 << i);
            bucket += nums[i];
            
            // 递归
            if (backtrack(k, bucket, nums, i + 1, used, target)) return true;
            
            // 撤销选择
            used ^= (1 << i);
            bucket -= nums[i];
        }
        
        return false;
    }
};

/*
// 方法 1：基于桶的视角 (回溯) - 复杂度较高 O(k^N)
// 每个数字选择进入哪个桶
class Solution1 {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k != 0) return false;
        int target = sum / k;
        vector<int> bucket(k, 0);
        sort(nums.begin(), nums.end(), greater<int>()); // 优化：大的先放
        return backtrack(nums, 0, bucket, target);
    }
    
    bool backtrack(vector<int>& nums, int index, vector<int>& bucket, int target) {
        if (index == nums.size()) return true;
        for (int i = 0; i < bucket.size(); i++) {
            // 剪枝：如果当前桶和上一个桶一样（且上一个桶没放进去），那就没必要试当前桶了
            if (i > 0 && bucket[i] == bucket[i-1]) continue;
            
            if (bucket[i] + nums[index] <= target) {
                bucket[i] += nums[index];
                if (backtrack(nums, index + 1, bucket, target)) return true;
                bucket[i] -= nums[index];
            }
        }
        return false;
    }
};
*/
