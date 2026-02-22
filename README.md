# LeetCode Practice Journal 🚀

This repository documents my journey of solving LeetCode problems for Spring Recruitment (春招). 
Instead of just storing code, I focus on capturing the **core logic**, **pitfalls**, and **patterns** for future review.

## 📂 Structure
- Solutions are grouped by topic/pattern (e.g., `SlidingWindow`, `BitManipulation`).
- Each file contains the solution and brief comments on the "Aha!" moments or bugs encountered.

## 📝 Problem List & Notes

### [868. Binary Gap (二进制间距)](https://leetcode.cn/problems/binary-gap/)
- **Tag**: Bit Manipulation
- **Key Insight**: 
  - Iterate through bits. 
  - **Pitfall**: Don't assume the first `1` is at index 0. Initialize `last_position = -1` to handle the start correctly.
  - **Logic**: Only calculate distance when `last_position != -1`.

### [3. Longest Substring Without Repeating Characters (无重复字符的最长子串)](https://leetcode.cn/problems/longest-substring-without-repeating-characters/)
- **Tag**: Sliding Window, Hash Set
- **Key Insight**: 
  - Maintain a window `[left, right]` and a `set` for checking duplicates.
  - **Core Logic**: When a duplicate `c` is found, **keep shrinking** the window from the left (`window.erase(s[left]), left++`) until the duplicate is removed.
  - **Pitfall**: Don't just `erase` once; use `while` loop.

---
*Created by [Your Name/Username]*
