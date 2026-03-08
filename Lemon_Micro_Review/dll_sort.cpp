#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 题目1：双向链表升序排序
// 限制：通过提供的虚函数调用，不准造新节点，对双向链表进行升序排序。
// 这通常意味着：In-place Sort (原地排序)，且不能只是交换值，可能需要交换指针。

// 模拟题目提供的节点结构和接口
struct Node {
    int val;
    Node* prev;
    Node* next;
    Node(int v) : val(v), prev(nullptr), next(nullptr) {}
};

class ListSorter {
public:
    // 假设题目提供了这样的虚函数接口用于比较和交换
    // 或者题目本身就是一个抽象基类，让你实现 sort
    virtual int compare(Node* a, Node* b) {
        return a->val - b->val;
    }
    
    // 关键点：原地链表排序，最适合的是归并排序 (Merge Sort)
    // 因为归并排序对链表是 O(N log N) 且不需要额外空间 (除了递归栈)
    
    Node* sortList(Node* head) {
        if (!head || !head->next) return head;
        
        // 1. 快慢指针找中点
        Node* slow = head;
        Node* fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // 2. 断开链表
        Node* mid = slow->next;
        slow->next = nullptr;
        if (mid) mid->prev = nullptr; // 双向链表记得断 prev
        
        // 3. 递归排序
        Node* l1 = sortList(head);
        Node* l2 = sortList(mid);
        
        // 4. 合并
        return merge(l1, l2);
    }
    
    Node* merge(Node* l1, Node* l2) {
        Node dummy(0);
        Node* tail = &dummy;
        
        while (l1 && l2) {
            if (compare(l1, l2) <= 0) {
                tail->next = l1;
                l1->prev = tail;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2->prev = tail;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        
        if (l1) {
            tail->next = l1;
            l1->prev = tail;
        }
        if (l2) {
            tail->next = l2;
            l2->prev = tail;
        }
        
        // 处理头节点的 prev
        dummy.next->prev = nullptr;
        return dummy.next;
    }
};

// 另一种可能是题目限制只能用 swap 节点？
// 如果题目要求通过虚函数操作，可能是这样的：
// virtual void swap(Node* a, Node* b); 
// 这种情况下，简单的冒泡/选择排序虽然 O(N^2) 但实现简单，如果 N 小的话可以过。
// 但通常大厂笔试 N 都在 10^5 级别，必须 N log N。

int main() {
    // 构造链表 4 <-> 2 <-> 1 <-> 3
    Node* n1 = new Node(4);
    Node* n2 = new Node(2);
    Node* n3 = new Node(1);
    Node* n4 = new Node(3);
    
    n1->next = n2; n2->prev = n1;
    n2->next = n3; n3->prev = n2;
    n3->next = n4; n4->prev = n3;
    
    ListSorter sorter;
    Node* head = sorter.sortList(n1);
    
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    return 0;
}
