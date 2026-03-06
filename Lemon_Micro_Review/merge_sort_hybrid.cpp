#include <iostream>
#include <vector>

using namespace std;

// 题目4：Merge Sort with Class Inheritance (Strict Version)
// 题目描述：根据提供的class和派生类补充归并排序需要的所有函数和操作。
// 结构可能如下：
// 一个基类 SortAlgorithm，定义了 sort 接口
// 一个派生类 MergeSort，包含数据成员（可能是一个 struct 数组？）

// 假设的数据结构
struct Data {
    int value;
    // 可能还有其他成员
};

// 基类
class SortAlgorithm {
public:
    virtual void sort(vector<Data>& data) = 0;
    virtual ~SortAlgorithm() {}
};

// 派生类 - 归并排序
class MergeSort : public SortAlgorithm {
public:
    void sort(vector<Data>& data) override {
        if (data.size() <= 1) return;
        mergeSort(data, 0, data.size() - 1);
    }

private:
    // 递归分割
    void mergeSort(vector<Data>& data, int left, int right) {
        if (left >= right) return;
        
        int mid = left + (right - left) / 2;
        mergeSort(data, left, mid);
        mergeSort(data, mid + 1, right);
        merge(data, left, mid, right);
    }

    // 合并两个有序区间 [left, mid] 和 [mid+1, right]
    void merge(vector<Data>& data, int left, int mid, int right) {
        // 创建临时数组
        // 注意：这里需要 O(N) 的额外空间
        vector<Data> temp;
        temp.reserve(right - left + 1);
        
        int i = left;
        int j = mid + 1;
        
        while (i <= mid && j <= right) {
            if (data[i].value <= data[j].value) {
                temp.push_back(data[i++]);
            } else {
                temp.push_back(data[j++]);
            }
        }
        
        while (i <= mid) temp.push_back(data[i++]);
        while (j <= right) temp.push_back(data[j++]);
        
        // 拷回原数组
        for (int k = 0; k < temp.size(); ++k) {
            data[left + k] = temp[k];
        }
    }
};

int main() {
    vector<Data> arr = {{5}, {2}, {9}, {1}, {5}, {6}};
    MergeSort sorter;
    sorter.sort(arr);
    
    for (const auto& d : arr) {
        cout << d.value << " ";
    }
    cout << endl;
    return 0;
}
