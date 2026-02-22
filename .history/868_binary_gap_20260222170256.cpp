#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<int> fun(int n) {
        std::vector<int> nums;
        while (n > 0) { // Fix: Loop while n > 0 to capture all bits
            nums.push_back(n % 2);
            n /= 2; // Simplified
        }
        return nums;
    }

    int binaryGap(int n) {
        std::vector<int> nums = fun(n);
        int left = -1; // Fix: Initialize to -1 to indicate no 1 found yet
        int count = 0;
        for(int i = 0;i < nums.size();i++)
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

int main() {
    Solution sol;
    
    // Test Case 1: n = 22 (10110) -> Expected: 2
    int res1 = sol.binaryGap(22);
    std::cout << "n=22 (Expected 2): " << res1 << std::endl;
    
    // Test Case 2: n = 8 (1000) -> Expected: 0
    int res2 = sol.binaryGap(8);
    std::cout << "n=8 (Expected 0): " << res2 << std::endl;

    // Test Case 3: n = 5 (101) -> Expected: 2
    int res3 = sol.binaryGap(5);
    std::cout << "n=5 (Expected 2): " << res3 << std::endl;
    
    return 0;
}
