#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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
