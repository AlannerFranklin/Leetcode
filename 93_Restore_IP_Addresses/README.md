# LeetCode 93. Restore IP Addresses

## 题目描述

给定一个只包含数字的字符串 `s`，用以表示一个 IP 地址，返回所有可能的有效 IP 地址。

## 你的代码错误分析

你提供的代码相比第一次已经有很大进步，修复了 `substr` 的部分长度问题，但仍有**两个关键错误**：

### 1. Base Case 缺少段数检查

*   **你的代码**：
    ```cpp
    if (start == s.size()) { 
        res.push_back(join(track, ".")); 
    }
    ```
*   **问题**：你只检查了字符串是否用完。如果字符串用完了，但 `track` 里只有 3 段（例如输入 "111"，切分成 "1.1.1"），你的代码会把它当做正确答案加入结果。
*   **修正**：必须同时检查 `track.size() == 4`。
    ```cpp
    if (start == s.size()) { 
        if (track.size() == 4) { // 必须正好 4 段
            res.push_back(join(track, ".")); 
        }
        return; // 记得 return，别让它继续往下跑
    }
    ```

### 2. `stoi` 的 `substr` 参数误用

*   **你的代码**：
    ```cpp
    if (stoi(s.substr(left, right)) > 255) return false;
    ```
*   **问题**：`substr(pos, len)` 的第二个参数是**长度**。
    *   你传入的是 `right`（当前子串的结束索引）。
    *   假设 `left=3`, `right=5` (长度为3)。`s.substr(3, 5)` 会从索引 3 开始截取 **5** 个字符，而不是截取到索引 5。这会导致截取的内容比你预期的多，甚至越界。
*   **修正**：应该传入长度。
    ```cpp
    int length = right - left + 1;
    if (stoi(s.substr(left, length)) > 255) return false;
    ```

### 3. 其他小建议

*   **参数传递**：`backtrack(string s, ...)` 会发生字符串拷贝。建议改为 `backtrack(const string& s, ...)` 引用传递，效率更高。
*   **前导 0 判断**：你提到的 `if (length == 1) return true;` 加上 `if (s[left] == '0') return false;` 的逻辑是**完全正确**的。我之前的分析有误，误以为你直接判断了首位是0。你的写法能正确处理 "0" 合法但 "01" 非法的情况。在 `solution.cpp` 中，为了逻辑紧凑，我将其合并写为 `if (length > 1 && s[left] == '0')`。

详细修正后的代码请参考 `solution.cpp`。
