#include <iostream>
#include <vector>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // ==========================================
    // 19. 删除链表的倒数第 N 个结点
    // ==========================================
    // 核心思想：双指针 (Two Pointers) / 快慢指针
    // 1. 让 fast 指针先走 n 步。
    // 2. 然后 fast 和 slow 同时走，直到 fast 到达链表末尾。
    // 3. 此时 slow 刚好在倒数第 n+1 个节点（待删除节点的前驱）。
    // 注意：使用 dummy 节点可以简化删除头节点的情况。
    // 时间复杂度：O(N)
    // 空间复杂度：O(1)
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0, head);
        ListNode* fast = dummy;
        ListNode* slow = dummy;

        // fast 先走 n+1 步 (为了让 slow 停在被删除节点的前一个)
        for (int i = 0; i <= n; ++i) {
            if (fast == nullptr) return head; // 异常处理
            fast = fast->next;
        }

        // 同时移动
        while (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }

        // 删除 slow->next
        ListNode* toDelete = slow->next;
        slow->next = slow->next->next;
        delete toDelete; // 释放内存

        ListNode* newHead = dummy->next;
        delete dummy; // 释放 dummy
        return newHead;
    }
};

// Helper functions
void printList(ListNode* head) {
    while (head) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "nullptr" << endl;
}

ListNode* createList(const vector<int>& vals) {
    if (vals.empty()) return nullptr;
    ListNode* head = new ListNode(vals[0]);
    ListNode* curr = head;
    for (size_t i = 1; i < vals.size(); ++i) {
        curr->next = new ListNode(vals[i]);
        curr = curr->next;
    }
    return head;
}

int main() {
    Solution sol;
    ListNode* head = createList({1, 2, 3, 4, 5});
    int n = 2;
    cout << "Original: "; printList(head);
    
    ListNode* res = sol.removeNthFromEnd(head, n);
    cout << "After removing " << n << "-th from end: "; printList(res);

    return 0;
}
