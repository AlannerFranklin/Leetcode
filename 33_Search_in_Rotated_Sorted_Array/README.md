# 33. 搜索旋转排序数组

## 题目链接
[LeetCode Link](https://leetcode.cn/problems/search-in-rotated-sorted-array/)

## 解题思路
### 旋转数组二分查找
这道题是二分查找的变种。核心难点在于：**如何确定 target 在哪一边？**

因为数组被旋转过（例如 `[4, 5, 6, 7, 0, 1, 2]`），我们不能简单地用 `mid` 和 `target` 的大小关系来判断。
但是，**无论在哪里切一刀，肯定有一半是有序的**。

### 算法步骤
1.  **判断有序区间**：
    *   如果 `nums[left] <= nums[mid]`，说明左半边 `[left, mid]` 是有序的。
    *   否则，说明右半边 `[mid, right]` 是有序的。
2.  **缩小查找范围**：
    *   如果左边有序，且 `target` 在 `[nums[left], nums[mid]]` 之间，那就在左边找（`right = mid - 1`），否则去右边。
    *   如果右边有序，且 `target` 在 `[nums[mid], nums[right]]` 之间，那就在右边找（`left = mid + 1`），否则去左边。

这样我们依然可以保持 O(log N) 的时间复杂度。
