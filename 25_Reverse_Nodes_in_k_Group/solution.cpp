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
    // 翻转链表辅助函数
    // 输入：链表头
    // 输出：翻转后的链表头
    ListNode* reverseGroup(ListNode* head) {
        ListNode* curr = head;
        ListNode* prev = nullptr;
        while (curr) {
            ListNode* nextTemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        }
        return prev;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        
        ListNode* pre = dummy; // 上一组的尾巴
        ListNode* end = dummy; // 本组的尾巴 (用来试探够不够k个)

        while (end->next != nullptr) {
            // 1. 试探：先让 end 往后跑 k 步
            for (int i = 0; i < k && end != nullptr; i++) {
                end = end->next;
            }
            // 如果跑不到 k 步（不够一组），直接结束，不用翻转
            if (end == nullptr) break;

            // 2. 记录断点
            ListNode* start = pre->next;     // 本组开始
            ListNode* nextGroup = end->next; // 下一组开始

            // 3. 断开链表 (为了让 reverseGroup 知道在哪里停)
            end->next = nullptr;

            // 4. 翻转本组
            pre->next = reverseGroup(start); 
            // 这里的 pre->next 就是让上一组连上翻转后的新头

            // 5. 重连下一组
            start->next = nextGroup; // 翻转后的尾巴 (start) 指向下一组

            // 6. 更新指针，准备下一轮
            pre = start; // 本组的尾巴变成了下一轮的 pre
            end = pre;   // end 重置，准备下一轮跑 k 步
        }
        
        return dummy->next;
    }
};
