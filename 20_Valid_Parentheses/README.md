# 20. 有效的括号

## 题目描述

[LeetCode 链接](https://leetcode.cn/problems/valid-parentheses/)

给定一个只包括 `'('`，`')'`，`'{'`，`'}'`，`'['`，`']'` 的字符串 `s` ，判断字符串是否有效。

有效字符串需满足：
1.  左括号必须用相同类型的右括号闭合。
2.  左括号必须以正确的顺序闭合。
3.  每个右括号都有一个对应的相同类型的左括号。

## 思路解析

使用 **栈 (Stack)** 数据结构来解决。

1.  **遍历字符串**：
    *   遇到左括号 `(`, `[`, `{`，将其对应的**右括号**压入栈中。这样做的好处是后续匹配时只需判断相等，代码更简洁。
    *   遇到右括号 `)`, `]`, `}`，判断栈是否为空，或者栈顶元素是否与当前字符相等。
        *   如果不相等或栈为空，说明不匹配，返回 `false`。
        *   如果相等，弹出栈顶元素。
2.  **最终判断**：
    *   遍历结束后，如果栈为空，说明所有括号都正确闭合，返回 `true`。
    *   如果栈不为空，说明有未闭合的左括号，返回 `false`。

## 代码实现

```cpp
class Solution {
public:
    bool isValid(string s) {
        if (s.size() % 2 != 0) return false; // 奇数长度肯定无效
        
        stack<char> stack;
        for (char c : s) {
            if (c == '(') stack.push(')');
            else if (c == '[') stack.push(']');
            else if (c == '{') stack.push('}');
            else if (stack.empty() || stack.top() != c) {
                return false; // 栈空了或者不匹配
            } else {
                stack.pop(); // 匹配成功
            }
        }
        return stack.empty(); // 必须全消完才算对
    }
};
```
