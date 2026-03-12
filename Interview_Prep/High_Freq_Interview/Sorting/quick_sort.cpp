#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// ==========================================
// 1. 递归版快速排序 (Recursive Quick Sort)
// ==========================================
// 核心思想：分治法 (Divide and Conquer)
// 时间复杂度：平均 O(N log N)，最坏 O(N^2)
// 空间复杂度：O(log N) (递归栈)

// Partition 函数：选取 pivot，将小于 pivot 的放左边，大于 pivot 的放右边
int partition(vector<int>& nums, int low, int high) {
    // 优化：随机选取 pivot 避免最坏情况
    int pivotIdx = low + rand() % (high - low + 1);
    swap(nums[low], nums[pivotIdx]);
    
    int pivot = nums[low];
    int i = low;
    int j = high;

    while (i < j) {
        // 从右向左找第一个小于 pivot 的数
        while (i < j && nums[j] >= pivot) {
            j--;
        }
        // 从左向右找第一个大于 pivot 的数
        while (i < j && nums[i] <= pivot) {
            i++;
        }
        // 交换
        if (i < j) {
            swap(nums[i], nums[j]);
        }
    }
    // 将 pivot 放到正确的位置 (i == j)
    swap(nums[low], nums[i]);
    return i;
}

void quickSortRecursive(vector<int>& nums, int low, int high) {
    if (low < high) {
        int pi = partition(nums, low, high);
        quickSortRecursive(nums, low, pi - 1);
        quickSortRecursive(nums, pi + 1, high);
    }
}

// ==========================================
// 2. 非递归版快速排序 (Iterative Quick Sort)
// ==========================================
// 核心思想：使用栈 (Stack) 模拟递归调用
// 每次将需要排序的区间 [low, high] 入栈

void quickSortIterative(vector<int>& nums) {
    if (nums.empty()) return;

    stack<pair<int, int>> s;
    s.push({0, nums.size() - 1});

    while (!s.empty()) {
        auto [low, high] = s.top();
        s.pop();

        if (low < high) {
            int pi = partition(nums, low, high);

            // 将左右子区间入栈
            // 注意：为了模拟递归，先压入右边，再压入左边（这样出栈时先处理左边，和递归顺序一致）
            // 其实顺序不影响正确性
            if (pi + 1 < high) {
                s.push({pi + 1, high});
            }
            if (low < pi - 1) {
                s.push({low, pi - 1});
            }
        }
    }
}

// 辅助函数：打印数组
void printArray(const vector<int>& nums) {
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    vector<int> data1 = {10, 7, 8, 9, 1, 5};
    vector<int> data2 = data1;

    cout << "Original array: ";
    printArray(data1);

    // 测试递归版
    quickSortRecursive(data1, 0, data1.size() - 1);
    cout << "Recursive Sorted: ";
    printArray(data1);

    // 测试非递归版
    quickSortIterative(data2);
    cout << "Iterative Sorted: ";
    printArray(data2);

    return 0;
}
