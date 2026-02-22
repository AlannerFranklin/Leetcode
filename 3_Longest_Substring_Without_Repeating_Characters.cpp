#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> window; 
        int left = 0;
        int max_length = 0;
        
        for(int right = 0; right < s.length(); right++) 
        {
            char ch = s[right];
            
            // 核心逻辑：如果有重复，必须一直删，直到把那个重复的字符删掉为止
            while (window.find(ch) != window.end()) {
                // 删除窗口最左边的字符
                window.erase(s[left]);
                // 左边界右移
                left++;
            }
            
            // 现在窗口没有重复了，把新字符放进去
            window.insert(ch);
            
            // 更新最大长度
            max_length = std::max(right - left + 1, max_length);
        }
        return max_length;
    }
};
