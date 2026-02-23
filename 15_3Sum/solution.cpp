#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        int n = nums.size();
        if (n < 3) return result; // 安全检查
        
        // 1. 排序：这是双指针和去重的基础
        sort(nums.begin(), nums.end()); 
        
        for (int i = 0; i < n - 2; i++) {
            // 2. 外层去重：如果当前数和前一个一样，跳过
            // 否则会产生重复的三元组，例如 [-1, -1, 2] 会被计算两次
            if (i > 0 && nums[i] == nums[i-1]) continue;
            
            int left = i + 1;
            int right = n - 1;
            
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                
                if (sum == 0) {
                    // 找到了！直接加入结果
                    result.push_back({nums[i], nums[left], nums[right]});
                    
                    // 3. 内层去重：跳过重复的 left 和 right
                    // 例如找到 [-1, 0, 1] 后，如果后面还是 0，那就不用再看了
                    while (left < right && nums[left] == nums[left+1]) left++;
                    while (left < right && nums[right] == nums[right-1]) right--;
                    
                    // 找到解后，两个指针都要动，继续找下一组可能的解
                    left++;
                    right--;
                } 
                else if (sum < 0) {
                    left++; // 太小了，变大点
                } 
                else {
                    right--; // 太大了，变小点
                }
            }
        }
        return result;
    }
};
