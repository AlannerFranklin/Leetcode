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
