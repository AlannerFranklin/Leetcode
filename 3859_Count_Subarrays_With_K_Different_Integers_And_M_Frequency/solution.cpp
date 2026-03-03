#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k, int m) {
        // 使用 lambda 表达式定义一个辅助函数，用于计算：
        // 满足 "不同整数个数 >= k" 且 "每个不同整数出现次数 >= m" 的子数组数量？
        // 不，这里的逻辑是：
        // 统计满足特定条件的子数组数量。
        
        // 注意：原题解的逻辑可能是有特定背景的。
        // 根据你提供的代码：
        // calc(k) 计算的是什么？
        // 循环中：while (cnt.size() >= distinct_limit && ge_m >= k)
        // 这意味着：当窗口内不同整数个数 >= k 且 满足频次要求的数个数 >= k 时，收缩左边界。
        // 收缩出来的每一个 left，都意味着 [0...right], [1...right], ... [left-1...right] 是满足某种“过度”条件的？
        // ans += left 表示以当前 right 结尾，有多少个合法的左端点。
        
        // 让我们仔细分析这个逻辑：
        // 这是一个 "atLeast K" 的逻辑。
        // 当窗口满足条件（比如 >= k 个满足频次的数）时，我们可以收缩 left。
        // left 左边的所有位置作为起点，到 right 的子数组，都满足条件（因为窗口只会更大）。
        // 所以 ans += left 是累加“满足条件的子数组数量”。
        
        // 最终结果是 calc(k) - calc(k + 1)。
        // calc(k)   = 统计 "满足频次的数个数 >= k" 的子数组数量。
        // calc(k+1) = 统计 "满足频次的数个数 >= k+1" 的子数组数量。
        // 相减得到 "满足频次的数个数 恰好 == k"。
        
        // 这里的关键假设是：题目要求的 "恰好 k 个不同整数"，实际上是指 "恰好 k 个满足频次 >= m 的不同整数"？
        // 如果题目原意是 "子数组里恰好有 k 个不同整数，且这 k 个数频次都 >= m"，那么这个解法是对的。
        // 因为如果子数组里还有其他频次 < m 的数，它们不被计入 ge_m，但会被计入 cnt.size()。
        // 你的代码里 while 条件是 `cnt.size() >= distinct_limit` 吗？
        // 不，你的代码逻辑是 `cnt.size() >= distinct_limit` 这个条件有点奇怪，通常应该是 ge_m >= k。
        
        // 让我们照着你的代码实现。
        
        auto calc = [&](int target_k) -> long long {
            unordered_map<int, int> cnt;
            int ge_m = 0;  // 窗口中出现次数 >= m 的元素个数
            int left = 0;
            long long ans = 0;
            
            for (int x : nums) {
                // 1. 入窗口
                cnt[x]++;
                if (cnt[x] == m) {
                    ge_m++;
                }
                
                // 2. 出窗口 (收缩左边界)
                // 条件：只要窗口内满足条件的数 >= target_k，就尝试收缩
                // 注意：这里可能还需要保证 cnt.size() 的限制？
                // 原代码：while (cnt.size() >= distinct_limit && ge_m >= k) 
                // 你给的代码里 distinct_limit 就是传入的 k。
                // 也就是说：当窗口内不同整数 >= k 且 满足频次的数 >= k 时，收缩。
                // 这实际上是在统计 "At Least K" 的逻辑。
                
                while (ge_m >= target_k) {
                    int out = nums[left];
                    if (cnt[out] == m) {
                        ge_m--;
                    }
                    cnt[out]--;
                    if (cnt[out] == 0) {
                        cnt.erase(out);
                    }
                    left++;
                }
                
                // 3. 更新答案
                // 这里的 left 是第一个 *不满足* ge_m >= target_k 的位置。
                // 也就是说 [0...right], [1...right], ... [left-1...right] 都是满足 ge_m >= target_k 的。
                // 共有 left 个。
                ans += left;
            }
            return ans;
        };
        
        return calc(k) - calc(k + 1);
    }
};
