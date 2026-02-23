#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Partition 函数：双向扫描 + 随机化 pivot
    // 返回 pivot 最终所在的下标
    int partition(vector<int>& nums, int l, int r) {
        // 1. 随机化 pivot，防止有序数组最坏情况 O(N^2)
        int randIdx = l + rand() % (r - l + 1);
        swap(nums[l], nums[randIdx]);
        
        int pivot = nums[l];
        int i = l + 1; // 左指针
        int j = r;     // 右指针
        
        while (true) {
            // 2. 双向扫描
            // 注意：这里 nums[i] < pivot (不带等号)，意味着 >= pivot 就停下
            // 同理，nums[j] > pivot (不带等号)，意味着 <= pivot 就停下
            // 这样遇到大量重复元素时，指针会频繁停下交换，让重复元素均匀分布在两边
            while (i <= j && nums[i] < pivot) i++;
            while (i <= j && nums[j] > pivot) j--;
            
            if (i >= j) break;
            
            swap(nums[i], nums[j]);
            i++;
            j--;
        }
        
        // 3. 把 pivot 放回中间 (j 的位置)
        swap(nums[l], nums[j]);
        return j;
    }

    // 快速选择主逻辑
    // 在 nums[l...r] 中找下标为 k 的元素
    int quickSelect(vector<int>& nums, int l, int r, int k) {
        if (l == r) return nums[l];
        
        int p = partition(nums, l, r);
        
        if (p == k) return nums[p]; // 找到了！
        else if (p < k) return quickSelect(nums, p + 1, r, k); // 在右边找
        else return quickSelect(nums, l, p - 1, k); // 在左边找
    }

    int findKthLargest(vector<int>& nums, int k) {
        srand(time(0)); // 初始化随机种子
        // 第 K 大 = 排序后第 N-K 小 (下标 N-K)
        return quickSelect(nums, 0, nums.size() - 1, nums.size() - k);
    }
};
