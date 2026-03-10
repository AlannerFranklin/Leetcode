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
    // 206. 反转链表 (Reverse Linked List)
    // ==========================================
    // 方法 1: 迭代法 (Iterative) - 推荐
    // 核心思想：保存 prev, curr, next，逐个改变指针指向
    // 时间复杂度：O(N)
    // 空间复杂度：O(1)
    ListNode* reverseListIterative(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr != nullptr) {
            ListNode* nextTemp = curr->next; // 暂存后继节点
            curr->next = prev;               // 反转指针
            prev = curr;                     // 前移 prev
            curr = nextTemp;                 // 前移 curr
        }
        return prev; // prev 最终指向新的头节点
    }

    // 方法 2: 递归法 (Recursive)
    // 核心思想：假设后续链表已经反转，将当前节点挂到反转后的链表尾部
    // 时间复杂度：O(N)
    // 空间复杂度：O(N) (递归栈)
    ListNode* reverseListRecursive(ListNode* head) {
        // Base case: 空链表或只有一个节点
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        // 递归反转后续部分
        ListNode* p = reverseListRecursive(head->next);
        // 将当前节点 head 挂到 head->next 的后面
        head->next->next = head;
        // 断开当前节点的 next，防止成环
        head->next = nullptr;
        return p;
    }
};

// Helper function to print list
void printList(ListNode* head) {
    while (head) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "nullptr" << endl;
}

// Helper function to create list from vector
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
    
    // Test Iterative
    ListNode* head1 = createList({1, 2, 3, 4, 5});
    cout << "Original: "; printList(head1);
    ListNode* reversed1 = sol.reverseListIterative(head1);
    cout << "Reversed (Iterative): "; printList(reversed1);

    // Test Recursive
    ListNode* head2 = createList({1, 2, 3, 4, 5});
    ListNode* reversed2 = sol.reverseListRecursive(head2);
    cout << "Reversed (Recursive): "; printList(reversed2);

    return 0;
}
