#include <iostream>
#include <vector>

using namespace std;

class Solution {
    vector<vector<int>> res;
    vector<int> track;

public:
    vector<vector<int>> combine(int n, int k) {
        // 不需要创建 board 数组，直接用数字 1..n 即可
        // 你的错误在于 board 没有初始化大小就直接 board[i] 赋值
        backtrack(n, k, 1);
        return res;
    }

private:
    // start 表示当前从哪个数字开始选 (范围 1 到 n)
    void backtrack(int n, int k, int start) {
        // 结束条件：找到 k 个数
        if (track.size() == k) {
            res.push_back(track);
            return;
        }

        // 剪枝优化：如果剩下的数不够凑满 k 个，直接结束
        // track.size() 已经选了的个数
        // k - track.size() 还需要选的个数
        // [start, n] 区间内剩下的数有 n - start + 1 个
        // 如果 n - start + 1 < k - track.size()，则不可能凑齐
        // 所以 i 最多遍历到 n - (k - track.size()) + 1
        
        for (int i = start; i <= n; i++) {
            // 做选择
            track.push_back(i);
            
            // 递归进入下一层，从 i + 1 开始选
            backtrack(n, k, i + 1);
            
            // 撤销选择
            track.pop_back();
        }
    }
};
