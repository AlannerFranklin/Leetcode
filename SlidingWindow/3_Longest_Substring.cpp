#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

// LeetCode 3: Longest Substring Without Repeating Characters
// Difficulty: Medium
// Tag: Sliding Window, Hash Table
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> window; 
        int left = 0;
        int max_length = 0;
        
        for(int right = 0; right < s.length(); right++) 
        {
            char ch = s[right];
            
            // While duplicate exists, shrink window from left
            while (window.find(ch) != window.end()) {
                window.erase(s[left]);
                left++;
            }
            
            // Add new character
            window.insert(ch);
            
            // Update max length
            max_length = std::max(right - left + 1, max_length);
        }
        return max_length;
    }
};
