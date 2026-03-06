#include <iostream>
#include <vector>

using namespace std;

// 题目4：Merge Sort with Class Inheritance
// 题目描述：根据提供的class和派生类补充归并排序需要的所有函数和操作。
// 这是一道典型的 C++ OOP 题目，考察虚函数、继承以及归并排序的实现。

// 假设基类
class Sortable {
public:
    virtual void sort() = 0;
    virtual ~Sortable() {}
};

// 假设具体类
class MergeSort : public Sortable {
private:
    vector<int> nums;

public:
    MergeSort(vector<int> input) : nums(input) {}

    void sort() override {
        if (nums.empty()) return;
        mergeSort(0, nums.size() - 1);
    }

    void print() {
        for (int n : nums) cout << n << " ";
        cout << endl;
    }

private:
    // 核心实现：递归归并排序
    void mergeSort(int left, int right) {
        if (left >= right) return;
        
        int mid = left + (right - left) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }

    // 核心实现：合并两个有序数组
    void merge(int left, int mid, int right) {
        // 创建临时数组
        vector<int> temp(right - left + 1);
        int i = left;      // 左边部分的指针
        int j = mid + 1;   // 右边部分的指针
        int k = 0;         // 临时数组的指针

        while (i <= mid && j <= right) {
            if (nums[i] <= nums[j]) {
                temp[k++] = nums[i++];
            } else {
                temp[k++] = nums[j++];
            }
        }

        while (i <= mid) {
            temp[k++] = nums[i++];
        }

        while (j <= right) {
            temp[k++] = nums[j++];
        }

        // 将临时数组拷贝回原数组
        for (int p = 0; p < temp.size(); ++p) {
            nums[left + p] = temp[p];
        }
    }
};

int main() {
    vector<int> arr = {5, 2, 9, 1, 5, 6};
    MergeSort sorter(arr);
    sorter.sort();
    sorter.print();
    return 0;
}
