# 143. 重排链表

## 题目描述

[LeetCode 链接](https://leetcode.cn/problems/reorder-list/)

给定一个单链表 L 的头节点 head ，单链表 L 表示为：

`L0 → L1 → … → Ln - 1 → Ln`

请将其重新排列后变为：

`L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …`

不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

## 思路解析

这道题可以拆解为三个经典的链表操作步骤：

1.  **寻找链表中点**：
    *   使用快慢指针（slow/fast）。
    *   `fast` 每次走两步，`slow` 每次走一步。当 `fast` 到达末尾时，`slow` 刚好在中间。
2.  **反转后半部分链表**：
    *   从中点断开链表，分为 `l1`（前半段）和 `l2`（后半段）。
    *   将 `l2` 进行反转。
3.  **合并两个链表**：
    *   像拉链一样，将 `l1` 和反转后的 `l2` 交替合并。

## 代码实现

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;

        // 1. 找中点
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // 2. 断开并反转后半段
        ListNode* l2 = slow->next;
        slow->next = nullptr; // 断开前半段
        
        ListNode* prev = nullptr;
        ListNode* curr = l2;
        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        l2 = prev; // 反转后的头节点

        // 3. 合并两个链表
        ListNode* l1 = head;
        while (l1 && l2) {
            ListNode* n1 = l1->next;
            ListNode* n2 = l2->next;

            l1->next = l2;
            l2->next = n1;

            l1 = n1;
            l2 = n2;
        }
    }
};
```
