#include<iostream>
using namespace std;

class Solution {
    public:
        struct ListNode {
            int val;
            ListNode* next;
            ListNode(int val, ListNode* next = nullptr) : val(val), next(next) {}
            ~ListNode() {
                if (next) delete next;
            }
        };
        ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
            ListNode* dummy = new ListNode(0, nullptr);
            ListNode* cur = dummy;
            ListNode* l1 = list1;
            ListNode* l2 = list2;
            while(l1 && l2) {
                if (l1->val < l2->val) {
                    cur->next = l1;
                    l1 = l1->next;
                }
                else if (l1->val >= l2->val) {
                    cur->next = l2;
                    l2 = l2->next;
                }
                cur = cur->next;
            }
            if (l1) cur->next = l1;
            if (l2) cur->next = l2;
            return dummy->next;
        }
};
int main() {
    Solution s;
    Solution::ListNode* list1 = new Solution::ListNode(1, new Solution::ListNode(2, new Solution::ListNode(4, nullptr)));
    Solution::ListNode* list2 = new Solution::ListNode(1, new Solution::ListNode(3, new Solution::ListNode(4, nullptr)));
    Solution::ListNode* res = s.mergeTwoLists(list1, list2);
    while(res) {
        cout << res->val << endl;
        res = res->next;
    }
}