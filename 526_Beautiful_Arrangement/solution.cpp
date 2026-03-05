#include <vector>

using namespace std;

class Solution {
public:
    int countArrangement(int n) {
        // 初始化 visited 数组，大小为 n + 1
        this->visited = vector<bool>(n + 1, false);
        this->count = 0;
        backtrack(n, 1);
        return count;
    }

private:
    vector<bool> visited;
    int count;

    void backtrack(int n, int index) {
        // Base Case: 如果 index > n，说明找到了一个优美排列
        if (index > n) {
            count++;
            return;
        }

        // 尝试在这个位置放入 1 到 n 的每一个数字
        for (int i = 1; i <= n; ++i) {
            // 如果数字 i 已经被使用，跳过
            if (visited[i]) continue;

            // 优美排列的条件：
            // perm[index] (即这里的 i) 能被 index 整除
            // 或者 index 能被 perm[index] (即这里的 i) 整除
            // 只要满足其中一个条件即可。
            
            // 你的原始代码错误在于逻辑判断：
            // 你写的是：if (index % i != 0 || i % index != 0) continue;
            // 这意味着：只要有一个条件不满足，就跳过。
            // 例如：index=2, i=4。 2%4!=0 (True) || 4%2!=0 (False) -> True -> continue。
            // 但实际上 4%2==0，是满足优美排列条件的，不应该跳过。
            
            // 正确的逻辑是：如果两个条件都不满足，才跳过。
            // !(A || B) 等价于 !A && !B
            if (index % i != 0 && i % index != 0) {
                continue;
            }

            // 标记 i 已使用
            visited[i] = true;
            
            // 递归下一个位置
            backtrack(n, index + 1);
            
            // 回溯
            visited[i] = false;
        }
    }
};
