#include <iostream>
#include <vector>
#include <algorithm>

// LeetCode 868: Binary Gap
// Difficulty: Easy
// Tag: Bit Manipulation
class Solution {
public:
    std::vector<int> fun(int n) {
        std::vector<int> nums;
        // Fix: Loop while n > 0 to capture all bits
        while (n > 0) {
            nums.push_back(n % 2);
            n /= 2;
        }
        return nums;
    }

    int binaryGap(int n) {
        std::vector<int> nums = fun(n);
        // Fix: Initialize to -1 to indicate no 1 found yet
        int left = -1;
        int count = 0;
        for(int i = 0; i < nums.size(); i++)
        {
            if(nums[i] == 1) { 
                if (left != -1) { // Only calculate distance if we have a previous 1
                    count = std::max(i - left, count); 
                }
                left = i; // Update position of the last seen 1
            }
        }
        return count;
    }
};
