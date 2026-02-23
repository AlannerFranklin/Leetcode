#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == nullptr || headB == nullptr) return nullptr;
        
        ListNode* pA = headA;
        ListNode* pB = headB;
        
        // 只要没相遇，就一直跑
        // 就算不相交，最后它们也会同时走到 NULL，循环结束返回 NULL，逻辑完美自洽
        while (pA != pB) {
            // pA 走完了 A，就去走 B；否则继续走 A
            pA = (pA == nullptr) ? headB : pA->next;
            
            // pB 走完了 B，就去走 A；否则继续走 B
            pB = (pB == nullptr) ? headA : pB->next;
        }
        
        return pA; // 相遇点，或者 NULL（如果不相交）
    }
};
