#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> window; // 窗口内的字符集合
        int left = 0; // 窗口左边界
        int max_length = 0;
        
        // right 指针从 0 开始向右移动
        for(int right = 0; right < s.length(); right++) 
        {
            char ch = s[right];
            
            // 核心逻辑：如果新字符已经在窗口中，说明有重复
            // 需要一直移动左边界，直到把重复的字符移除
            while (window.find(ch) != window.end()) {
                window.erase(s[left]);
                left++;
            }
            
            // 窗口现在干净了，加入新字符
            window.insert(ch);
            
            // 更新最大长度
            max_length = std::max(right - left + 1, max_length);
        }
        return max_length;
    }
};
