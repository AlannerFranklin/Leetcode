#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        
        while (left <= right) { // 注意是 <=，否则可能漏掉最后一个元素
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) return mid;
            
            // 关键：先判断哪边有序
            if (nums[left] <= nums[mid]) {
                // 左半边有序 [left, mid]
                // 既然有序，就能判断 target 在不在里面
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1; // 在左边
                } else {
                    left = mid + 1;  // 去右边
                }
            } else {
                // 右半边有序 [mid, right]
                // 既然有序，也能判断 target 在不在里面
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;  // 在右边
                } else {
                    right = mid - 1; // 去左边
                }
            }
        }
        
        return -1;
    }
};
