#include <string>
#include <vector>
#include <unordered_set>
#include <cmath>

using namespace std;

class Solution {
public:
    bool hasAllCodes(string s, int k) {
        // 1. 剪枝：如果 s 的长度连凑齐 2^k 个子串都不够，直接返回 false
        // 1 << k 等于 2^k
        if (s.size() < k || s.size() - k + 1 < (1 << k)) {
            return false;
        }

        // 2. 用 Set 存所有见过的长度为 k 的子串
        unordered_set<string> seen;
        int target = 1 << k; // 需要找到这么多不同的串
        
        for (int i = 0; i <= s.size() - k; i++) {
            // 取出从 i 开始长度为 k 的子串
            string sub = s.substr(i, k);
            seen.insert(sub);
            
            // 3. 提速：如果已经找齐了，就不用继续遍历了
            if (seen.size() == target) {
                return true;
            }
        }
        
        return seen.size() == target;
    }
};
