#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * Problem: Split array into m subarrays such that the maximum sum of any subarray is minimized.
     * This is a classic "Minimize the Maximum" problem, solvable by Binary Search on Answer.
     * 
     * Constraints:
     * n <= 10^6
     * m <= n
     * 
     * Why not DP?
     * DP solution would be O(n * m), which is too slow for n = 10^6.
     * Binary Search solution is O(n * log(sum)), which is very efficient.
     */
    long long splitArray(vector<int>& nums, int m) {
        long long left = 0;
        long long right = 0;
        
        // The lower bound is the maximum single element (must fit in a bag)
        // The upper bound is the sum of all elements (one bag holds everything)
        for (int num : nums) {
            left = max(left, (long long)num);
            right += num;
        }

        long long ans = right;

        while (left <= right) {
            long long mid = left + (right - left) / 2;
            
            if (check(nums, m, mid)) {
                // If mid is feasible, try to find a smaller maximum sum
                ans = mid;
                right = mid - 1;
            } else {
                // If mid is not feasible (need more than m bags), we need a larger capacity
                left = mid + 1;
            }
        }
        
        return ans;
    }

private:
    // Check if it's possible to split nums into <= m subarrays such that
    // no subarray sum exceeds max_capacity.
    bool check(const vector<int>& nums, int m, long long max_capacity) {
        int bags_needed = 1;
        long long current_bag_sum = 0;

        for (int num : nums) {
            if (current_bag_sum + num > max_capacity) {
                // Need a new bag
                bags_needed++;
                current_bag_sum = num;
                if (bags_needed > m) {
                    return false;
                }
            } else {
                current_bag_sum += num;
            }
        }
        
        return true;
    }
};

int main() {
    Solution sol;

    // Test Case 1: Standard case
    vector<int> nums1 = {7, 2, 5, 10, 8};
    int m1 = 2;
    // Expected: 18. Split: [7, 2, 5], [10, 8] -> Sums: 14, 18. Max: 18.
    // Or [7, 2, 5, 10], [8] -> Sums: 24, 8. Max: 24.
    cout << "Test Case 1: " << sol.splitArray(nums1, m1) << " (Expected: 18)" << endl;

    // Test Case 2: m = n (Each element is a bag)
    vector<int> nums2 = {1, 2, 3, 4, 5};
    int m2 = 5;
    // Expected: 5 (Max element)
    cout << "Test Case 2: " << sol.splitArray(nums2, m2) << " (Expected: 5)" << endl;

    // Test Case 3: m = 1 (One bag for all)
    vector<int> nums3 = {1, 2, 3, 4, 5};
    int m3 = 1;
    // Expected: 15 (Sum)
    cout << "Test Case 3: " << sol.splitArray(nums3, m3) << " (Expected: 15)" << endl;
    
    // Test Case 4: Large numbers (Simulating constraints)
    vector<int> nums4 = {1000000, 1000000, 1000000};
    int m4 = 2;
    // Expected: 2000000. Split: [1000000, 1000000], [1000000]
    cout << "Test Case 4: " << sol.splitArray(nums4, m4) << " (Expected: 2000000)" << endl;

    return 0;
}
