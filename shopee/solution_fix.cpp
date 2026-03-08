#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

// 修复后的 O(N^2) 解法
// 你的原代码主要问题在于：没有正确处理 inner loop 未找到的情况
// 以及 right 变量没有在每次循环中重置

int main() {
    string source, target;
    cin >> source >> target;
    
    int min_len = INT_MAX;
    string result = "";
    
    // 遍历每一个可能的起点
    for (int i = 0; i < source.size(); i++) {
        // 只有当当前字符匹配 target[0] 时才开始搜索
        if (source[i] == target[0]) {
            int k = 1; // target 的索引，从 1 开始匹配
            int right = -1; // 标记是否找到完整的 target
            
            // 在 i 后面继续寻找 target[1...end]
            for (int j = i + 1; j < source.size(); j++) {
                if (k < target.size() && source[j] == target[k]) {
                    k++;
                }
                // 如果 target 全部匹配完了
                if (k == target.size()) {
                    right = j;
                    break; // 找到了最短的结束位置 j（对于当前的 i 来说）
                }
            }
            
            // 只有当完整找到了 target，才计算长度
            if (right != -1) {
                int current_len = right - i + 1;
                // 更新全局最小值
                if (current_len < min_len) {
                    min_len = current_len;
                    result = source.substr(i, min_len);
                }
            }
        }
    }
    
    cout << result << endl;
    return 0;
}
