# High Frequency Interview Questions & Solutions

This directory contains solutions and explanations for frequently asked interview questions.

## Progress Tracking

### Sorting Algorithms
- [x] **Quick Sort (Recursive & Iterative)** - `Sorting/quick_sort.cpp`
- [x] **Merge Sort** - `Sorting/merge_sort.cpp`
- [ ] **Heap Sort**
- [ ] **Theory: Quick Sort Complexity & Optimization**

### Data Structures
- [x] **Bloom Filter (Principle & Implementation)** - `BloomFilter/bloom_filter.cpp`
- [ ] **LRU Cache (LeetCode 146)** - See `leetcode/146_LRU_Cache`
- [ ] **Theory: AVL vs Red-Black Tree**

### Linked List
- [x] **206. Reverse Linked List** - `LinkedList/206_Reverse_List.cpp`
- [x] **19. Remove Nth Node From End of List** - `LinkedList/19_Remove_Nth_Node.cpp`

### Tree & Graph
- [ ] **94. Binary Tree Inorder Traversal**
- [x] **199. Binary Tree Right Side View** - `Tree/199_Right_Side_View.cpp`
- [x] **617. Merge Two Binary Trees** - `Tree/617_Merge_Trees.cpp`
- [ ] **236. Lowest Common Ancestor** - See `leetcode/236_Lowest_Common_Ancestor_of_a_Binary_Tree`

### Dynamic Programming (DP)
- [x] **1143. Longest Common Subsequence** - `DP/1143_LCS.cpp`
- [ ] **70. Climbing Stairs / Jump Floor**

### Others
- [ ] **15. 3Sum** - See `leetcode/15_3Sum`
- [ ] **81. Search in Rotated Sorted Array II**
- [ ] **Binary Search Implementation**
- [ ] **Palindrome Substrings**

---

## Quick Reference

### Quick Sort
*   **Time**: Avg $O(N \log N)$, Worst $O(N^2)$.
*   **Space**: $O(\log N)$.
*   **Optimization**: Random Pivot, Median-of-Three, Insertion Sort for small arrays.

### Merge Sort
*   **Time**: $O(N \log N)$ always.
*   **Space**: $O(N)$.
*   **Stable**: Yes.

### Bloom Filter
*   **Use**: Check if element *might* exist or *definitely does not* exist.
*   **False Positive**: Possible (element not in set but filter says yes).
*   **False Negative**: Impossible.
