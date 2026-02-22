#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<int> fun(int n) {
        std::vector<int> nums;
        // User's code: while (n > 1)
        while (n > 1) {
            nums.push_back(n % 2);
            n = n - n % 2;
            n /= 2;
        }
        // Note: The user's code stops when n reaches 1, so the last '1' is not added.
        return nums;
    }

    int binaryGap(int n) {
        std::vector<int> nums = fun(n);
        int left = 0;
        int count = 0;
        // User's code logic
        for(int i = 0;i < nums.size();i++)
        {
            if(nums[i] == 1) { // Issue: vector<int> stores bits.
                // Logic: calculate distance from 'left'
                // Issue: If this is the first '1', 'left' is 0 by default.
                // If first '1' is at index 2, distance = 2 - 0 = 2. Wrong.
                // Should ignore distance calculation for the first '1'.
                
                // Original code:
                 count = std::max(i - left, count);
                 left = i;
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
