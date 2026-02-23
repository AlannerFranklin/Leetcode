#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // 1. 初始化
        int current_sum = nums[0];
        int max_sum = nums[0];
        
        // 2. 从第 1 个数开始遍历
        for (int i = 1; i < nums.size(); i++) {
            // 决策：是接着前面的子数组续上，还是自立门户？
            // 如果 current_sum < 0，那加上它还不如不加，直接从 nums[i] 开始
            // 如果 current_sum > 0，那加上它肯定更好
            if (current_sum < 0) {
                current_sum = nums[i];
            } else {
                current_sum += nums[i];
            }
            
            // 3. 更新全局最大值
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
        }
        
        return max_sum;
    }
};
