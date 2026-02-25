#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        if (n == 0) return 0;

        // 1. 排序
        // 宽度 w 按升序排列
        // 如果 w 相同，高度 h 按降序排列
        // 原因：w 相同时，我们不希望 [3, 3] 能套进 [3, 4]（因为宽度必须严格大于），
        // 逆序排列后，h 变成了 [4, 3]，在求 LIS 时 4 后面接不了 3，避免了错误计算。
        sort(envelopes.begin(), envelopes.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] == b[0] ? b[1] < a[1] : a[0] < b[0];
        });

        // 2. 提取高度数组
        vector<int> height(n);
        for (int i = 0; i < n; i++) {
            height[i] = envelopes[i][1];
        }

        // 3. 求高度数组的最长递增子序列 (LIS)
        return lengthOfLIS(height);
    }

    int lengthOfLIS(vector<int>& nums) {
        // piles 表示当前牌堆的数量，也就是 LIS 的长度
        // dp[k] 存储的是长度为 k+1 的递增子序列的最小结尾元素
        // 注意：这里用 dp 数组来模拟 piles 堆顶元素
        vector<int> top(nums.size());
        int piles = 0;

        for (int i = 0; i < nums.size(); i++) {
            // 在 top[0...piles-1] 中二分查找第一个 >= nums[i] 的元素
            int left = 0, right = piles;
            while (left < right) {
                int mid = left + (right - left) / 2;
                if (top[mid] >= nums[i]) {
                    right = mid;
                } else {
                    left = mid + 1;
                }
            }

            // 如果没找到（所有堆顶都比 nums[i] 小），说明可以新建一堆
            if (left == piles) {
                piles++;
            }
            
            // 把这张牌放到堆顶（覆盖掉原来的，或者放在新堆上）
            // 贪心策略：让堆顶元素尽可能小，这样后面更容易接上
            top[left] = nums[i];
        }

        return piles;
    }
};
