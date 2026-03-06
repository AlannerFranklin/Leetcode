#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 题目1：双向链表升序排序（严格限制版）
// 限制：
// 1. 不准造新节点（意味着不能用 Node dummy(0) 这种栈上对象，因为 Node 构造函数不可见或被禁止）
// 2. 只能使用给定的接口：get_data(), get_next(), get_prev(), set_next(Node*), set_prev(Node*)

// 模拟题目提供的纯虚基类接口
class ListNode {
public:
    virtual int get_data() = 0;
    virtual ListNode* get_next() = 0;
    virtual ListNode* get_prev() = 0;
    virtual void set_next(ListNode* n) = 0;
    virtual void set_prev(ListNode* p) = 0;
    virtual ~ListNode() {}
};

// 模拟具体的节点实现（考试时不可见）
class NodeImpl : public ListNode {
    int val;
    ListNode* next;
    ListNode* prev;
public:
    NodeImpl(int v) : val(v), next(nullptr), prev(nullptr) {}
    int get_data() override { return val; }
    ListNode* get_next() override { return next; }
    ListNode* get_prev() override { return prev; }
    void set_next(ListNode* n) override { next = n; }
    void set_prev(ListNode* p) override { prev = p; }
};

class ListSorter {
public:
    // 归并排序主函数
    ListNode* sortList(ListNode* head) {
        if (!head || !head->get_next()) return head;
        
        // 1. 快慢指针找中点
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->get_next() && fast->get_next()->get_next()) {
            slow = slow->get_next();
            fast = fast->get_next()->get_next();
        }
        
        // 2. 断开链表
        ListNode* mid = slow->get_next();
        slow->set_next(nullptr);
        if (mid) mid->set_prev(nullptr); // 断开后半段的 prev
        
        // 3. 递归排序
        ListNode* l1 = sortList(head);
        ListNode* l2 = sortList(mid);
        
        // 4. 合并
        return merge(l1, l2);
    }
    
    // 合并两个有序链表（不使用 dummy 节点）
    ListNode* merge(ListNode* l1, ListNode* l2) {
        if (!l1) return l2;
        if (!l2) return l1;
        
        ListNode* head = nullptr;
        ListNode* tail = nullptr;
        
        // 确定头节点
        if (l1->get_data() <= l2->get_data()) {
            head = l1;
            l1 = l1->get_next();
        } else {
            head = l2;
            l2 = l2->get_next();
        }
        head->set_prev(nullptr); // 新的头节点 prev 置空
        tail = head;
        
        // 循环合并
        while (l1 && l2) {
            if (l1->get_data() <= l2->get_data()) {
                tail->set_next(l1);
                l1->set_prev(tail);
                l1 = l1->get_next();
            } else {
                tail->set_next(l2);
                l2->set_prev(tail);
                l2 = l2->get_next();
            }
            tail = tail->get_next();
        }
        
        // 接上剩余部分
        if (l1) {
            tail->set_next(l1);
            l1->set_prev(tail);
        } else if (l2) {
            tail->set_next(l2);
            l2->set_prev(tail);
        }
        
        return head;
    }
};

int main() {
    // 构造测试链表 4 <-> 2 <-> 1 <-> 3
    NodeImpl* n1 = new NodeImpl(4);
    NodeImpl* n2 = new NodeImpl(2);
    NodeImpl* n3 = new NodeImpl(1);
    NodeImpl* n4 = new NodeImpl(3);
    
    n1->set_next(n2); n2->set_prev(n1);
    n2->set_next(n3); n3->set_prev(n2);
    n3->set_next(n4); n4->set_prev(n3);
    
    ListSorter sorter;
    ListNode* head = sorter.sortList(n1);
    
    while (head) {
        cout << head->get_data() << " ";
        head = head->get_next();
    }
    
    // 清理内存略
    return 0;
}
