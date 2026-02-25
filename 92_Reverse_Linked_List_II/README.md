# 92. 反转链表 II

## 题目描述

[LeetCode 链接](https://leetcode.cn/problems/reverse-linked-list-ii/)

给你单链表的头指针 `head` 和两个整数 `left` 和 `right` ，其中 `left <= right` 。请你反转从位置 `left` 到位置 `right` 的链表节点，返回 **反转后的链表** 。

## 思路解析

本题推荐使用 **一次遍历 + 头插法**。

1.  **虚拟头节点 (Dummy Node)**：
    *   因为 `left` 可能是 1（即反转头节点），为了统一处理逻辑，我们需要创建一个 `dummy` 节点指向 `head`。
2.  **定位前驱节点 (Pre)**：
    *   从 `dummy` 开始走 `left - 1` 步，到达需要反转区间的前一个节点 `pre`。
3.  **头插法反转**：
    *   `curr` 指向 `pre->next`（这是反转区间的第一个节点，反转后会变成最后一个）。
    *   在 `left` 到 `right` 的区间内，不断把 `curr` 后面的节点 `next` 拿出来，插到 `pre` 的后面。
    *   重复 `right - left` 次。

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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (!head || left == right) return head;

        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* pre = dummy;

        // 1. 走到 left 的前一个节点
        for (int i = 0; i < left - 1; i++) {
            pre = pre->next;
        }

        // 2. 开始反转 (头插法)
        ListNode* curr = pre->next;
        ListNode* next;
        
        for (int i = 0; i < right - left; i++) {
            next = curr->next;
            
            curr->next = next->next;
            next->next = pre->next;
            pre->next = next;
        }

        return dummy->next;
    }
};
```
