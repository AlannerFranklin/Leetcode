#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int l_max = 0;
        int r_max = 0;
        int ans = 0;

        while (left < right) {
            // 每次更新左右两边的“已知最高”
            l_max = max(l_max, height[left]);
            r_max = max(r_max, height[right]);

            // 谁是短板，谁就结算
            if (l_max < r_max) {
                // 左边是短板，那 left 位置的水位就是 l_max
                ans += l_max - height[left];
                left++; // 结算完了，left 前进
            } else {
                // 右边是短板，那 right 位置的水位就是 r_max
                ans += r_max - height[right];
                right--; // 结算完了，right 后退
            }
        }
        return ans;
    }
};
