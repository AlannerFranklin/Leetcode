// Empty solution file for LeetCode 86. Partition List
// Write your solution here.
#include <iostream>
#include <vector>
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
        ListNode* partition(ListNode* head, int x) {
            ListNode* l1 = new ListNode(0, nullptr);
            ListNode* l2 = new ListNode(0, nullptr);
            ListNode* l3 = head;
            ListNode* l4 = l1;
            ListNode* l5 = l2;
            while(l3) {
                if (l3->val < x) {
                    l4->next = l3;
                    l3 = l3->next;
                    l4 = l4->next;
                } else if (l3->val >= x) {
                    l5->next = l3;
                    l3 = l3->next;
                    l5 = l5->next;
                }
            }
            l4->next = l2->next;
            l5->next = nullptr;
            return l1->next;
        }
};
int main() {
    Solution s;
    Solution::ListNode* head = new Solution::ListNode(0,nullptr);
    vector<int> nums = {1,4,3,2,5,2};
    Solution::ListNode* cur = head;
    for(int val : nums) {
        cur->next = new Solution::ListNode(val);
        cur = cur->next;
    }
    Solution::ListNode* res = s.partition(head->next, 3);
    while(res) {
        cout << res->val << " ";
        res = res->next;
    }
    cout<<endl;
    return 0;
}