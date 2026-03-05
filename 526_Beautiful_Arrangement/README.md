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

## 拓展：回溯算法中的 return 问题

你问到：“为什么有些回溯算法，第一个判断是否停止的时候有 return; 有些则没有呢？”

这是一个非常经典的问题，核心在于**“当前的节点是最终答案，还是中间状态？”**

### 第一类：寻找特定长度/特定目标的解（需要 return）

比如这道题（优美排列）、全排列（Permutations）、N皇后（N-Queens）。
*   **特点**：只有当递归深度达到 `n`（叶子节点）时，才是一个有效的解。
*   **逻辑**：如果已经填满了 `n` 个位置，继续往下填是没有意义的，甚至是错误的。
*   **代码模式**：
    ```cpp
    if (index > n) {
        res.push_back(track); // 记录答案
        return; // 必须返回，不能再往下走了
    }
    ```

### 第二类：收集所有可能的子集/组合（不需要 return）

比如子集（Subsets）、组合总和（Combination Sum）。
*   **特点**：递归树上的**每一个节点**（不仅是叶子节点）都可能是一个合法的解。
*   **逻辑**：比如找子集 `[1, 2, 3]`。
    *   刚进入函数，`track` 是空 `[]`，这是一个解。
    *   加入 1，`track` 是 `[1]`，这也是一个解。我们**记录它**，但**不应该返回**，因为我们还想试试 `[1, 2]`。
*   **代码模式**：
    ```cpp
    // 每次进入函数都记录当前状态
    res.push_back(track); 
    
    // 没有 return！因为还要继续尝试添加元素
    for (int i = start; i < nums.size(); i++) {
        track.push_back(nums[i]);
        backtrack(...);
        track.pop_back();
    }
    ```

**总结**：
*   如果你的目标在**树的底部**（叶子），到了底部就 `return`。
*   如果你的目标散落在**树的节点**上（所有路径节点），记录后不要急着 `return`，除非遇到边界条件（如数组遍历完了）。
