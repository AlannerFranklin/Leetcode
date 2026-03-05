# LeetCode 526. Beautiful Arrangement

## 题目描述

假设有从 1 到 N 的 N 个整数，如果从 1 到 N 的排列中满足如下条件，则称为优美排列：

*   第 `i` 位的数字能被 `i` 整除
*   `i` 能被第 `i` 位的数字整除

给定 N，返回优美排列的数量。

## 你的代码问题分析

你遇到的问题**不是**因为返回 `res.size()`（虽然直接计数更高效），**而是**因为回溯中的剪枝逻辑写错了。

### 1. 逻辑错误：`||` (OR) vs `&&` (AND)

你的代码中写的是：

```cpp
if (index % i != 0 || i % index != 0) continue;
```

这段代码的意思是：**只要有一个条件不满足，就跳过**。

让我们看一个反例：
假设 `index = 2` (第2个位置)，我们要放入数字 `i = 4`。
*   `index % i` => `2 % 4 != 0` (True，不满足被整除)
*   `i % index` => `4 % 2 == 0` (False，满足被整除)

你的逻辑判断：`True || False` 结果为 `True`。于是代码执行 `continue`，**跳过了这个合法的组合**。

但实际上，题目要求的是**只要满足其中一个条件即可**。
所以我们应该在**两个条件都不满足**的时候才跳过。

根据德摩根定律 (De Morgan's laws)：
`!(A || B)` 等价于 `!A && !B`。

所以正确的逻辑应该是：

```cpp
// 只有当两个条件都不满足时，才跳过
if (index % i != 0 && i % index != 0) continue;
```

或者写成正向逻辑：

```cpp
// 只要满足其中一个条件，就继续处理
if (index % i == 0 || i % index == 0) {
    used[i] = true;
    backtrack(...);
    used[i] = false;
}
```

### 2. 关于 `res.size()`

你提到的 `res.size()` 本身逻辑上是对的。如果你修复了上面的 `if` 条件，返回 `res.size()` 也能通过测试。

但是，从性能角度来看：
*   题目只要求返回数量，不需要具体的排列。
*   当 N=15 时，虽然优美排列只有 24679 个，但在递归过程中频繁创建和销毁 `vector<int> track` 以及向 `res` 中添加元素，会增加不必要的内存开销和时间开销。
*   使用一个简单的 `int count` 变量是最优解。

## 修正后的代码

```cpp
class Solution {
public:
    int countArrangement(int n) {
        this->visited = vector<bool>(n + 1, false);
        this->count = 0;
        backtrack(n, 1);
        return count;
    }

private:
    vector<bool> visited;
    int count;

    void backtrack(int n, int index) {
        if (index > n) {
            count++;
            return;
        }

        for (int i = 1; i <= n; ++i) {
            if (visited[i]) continue;
            
            // 修复点：逻辑运算符从 || 改为 &&
            // 只有当 i 不能被 index 整除 且 index 不能被 i 整除时，才跳过
            if (index % i != 0 && i % index != 0) {
                continue;
            }

            visited[i] = true;
            backtrack(n, index + 1);
            visited[i] = false;
        }
    }
};
```
