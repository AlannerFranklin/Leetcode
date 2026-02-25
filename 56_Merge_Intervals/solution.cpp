#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};
        
        // 1. 按照区间的起始位置排序
        sort(intervals.begin(), intervals.end());
        
        vector<vector<int>> merged;
        
        for (const auto& interval : intervals) {
            // 如果结果集为空，或者当前区间的起始位置 > 结果集最后一个区间的结束位置
            // 说明没有重叠，直接添加
            if (merged.empty() || interval[0] > merged.back()[1]) {
                merged.push_back(interval);
            } else {
                // 有重叠，合并区间（更新结果集最后一个区间的结束位置）
                merged.back()[1] = max(merged.back()[1], interval[1]);
            }
        }
        
        return merged;
    }
};
