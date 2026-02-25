#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        
        // 第一次遍历：原地哈希 (In-place Hashing)
        // 尝试把每个数 nums[i] 放到它正确的位置 nums[i] - 1 上
        for (int i = 0; i < n; i++) {
            // 条件：
            // 1. 是正数 (nums[i] > 0)
            // 2. 没有越界 (nums[i] <= n)
            // 3. 当前位置不对 (nums[i] != nums[nums[i] - 1])
            while (nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i] - 1]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        
        // 第二次遍历：找第一个位置不对的数
        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        
        // 如果所有数都对上了（比如 [1, 2, 3]），那缺失的就是 n + 1
        return n + 1;
    }
};
