#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

/**
 * LeetCode 1. Two Sum (两数之和)
 * 
 * 题目描述：
 * 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出和为目标值 target  的那 两个 整数，并返回它们的数组下标。
 * 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
 * 
 * Example:
 * Input: nums = [2,7,11,15], target = 9
 * Output: [0,1] (Because nums[0] + nums[1] == 9)
 * 
 * 解题思路：
 * 1. 暴力解法 (Brute Force):
 *    - 使用双重循环，遍历所有可能的组合。
 *    - 时间复杂度: O(n^2)
 *    - 空间复杂度: O(1)
 * 
 * 2. 哈希表法 (Hash Map) - 推荐:
 *    - 我们需要寻找的是 `target - current_value` 是否存在于数组中。
 *    - 我们可以遍历数组，同时用哈希表记录已经遍历过的元素及其下标。
 *    - 对于每个元素 `num`，检查 `target - num` 是否在哈希表中。
 *      - 如果在，说明找到了，返回 `[map[target-num], current_index]`。
 *      - 如果不在，将 `num` 及其下标存入哈希表，继续遍历。
 *    - 时间复杂度: O(n) - 只需要遍历一次，哈希表查找平均 O(1)。
 *    - 空间复杂度: O(n) - 需要存储 n 个元素到哈希表中。
 */

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // key: 数值, value: 下标
        unordered_map<int, int> map;
        
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            
            // 检查差值是否在哈希表中
            if (map.find(complement) != map.end()) {
                return {map[complement], i};
            }
            
            // 将当前值存入哈希表
            map[nums[i]] = i;
        }
        
        return {}; // 如果没有找到解
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    
    vector<int> result = sol.twoSum(nums, target);
    
    if (result.size() == 2) {
        cout << "Index 1: " << result[0] << ", Index 2: " << result[1] << endl;
    } else {
        cout << "No solution found." << endl;
    }
    
    return 0;
}
