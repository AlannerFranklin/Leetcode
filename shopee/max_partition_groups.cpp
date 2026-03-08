#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>

using namespace std;

class Solution {
public:
    // Main function to solve the problem
    int maxGroups(vector<int>& nums) {
        long long sum = 0;
        for (int num : nums) sum += num;
        int n = nums.size();

        // Sort in descending order to optimize backtracking
        sort(nums.rbegin(), nums.rend());

        // Try k from n down to 1
        for (int k = n; k >= 1; --k) {
            // Pruning 1: Total sum must be divisible by k
            if (sum % k != 0) continue;

            long long target = sum / k;
            
            // Pruning 2: Largest element must not exceed target
            if (nums[0] > target) continue;

            // Use a visited array to track used elements
            vector<bool> visited(n, false);
            
            // Check if we can partition into k subsets of sum 'target'
            if (canPartition(nums, visited, 0, k, 0, target)) {
                return k;
            }
        }
        return 1; // Should not reach here as k=1 is always possible
    }

private:
    // Backtracking function
    // index: current index in nums we are considering
    // k: number of subsets remaining to be filled
    // currentSum: current sum of the subset being built
    // target: target sum for each subset
    bool canPartition(const vector<int>& nums, vector<bool>& visited, int index, int k, long long currentSum, long long target) {
        // Base case: If k=1, the last subset is automatically valid if all previous were valid
        // (because total sum is correct). Or we can check k=0 if we prefer.
        // Here we use k=1 optimization.
        if (k == 1) return true;

        // If current subset is full, start the next one
        if (currentSum == target) {
            return canPartition(nums, visited, 0, k - 1, 0, target);
        }

        // Try to add elements to the current subset
        for (int i = index; i < nums.size(); ++i) {
            // Skip used elements
            if (visited[i]) continue;

            // Pruning 3: Skip duplicates to avoid redundant work
            // If current number is same as previous and previous was not used in this recursion level (skipped),
            // then using current is same as using previous, which we already tried and failed (or skipped).
            // Note: !visited[i-1] check is subtle. It means i-1 was available but we didn't use it.
            if (i > 0 && nums[i] == nums[i-1] && !visited[i-1]) continue;

            // Pruning 4: If adding this number exceeds target, stop (since nums is sorted descending)
            // Wait, nums is sorted descending. If nums[i] + currentSum > target, then for all j > i, nums[j] might be smaller and fit.
            // So we can only break if nums[i] itself is too big? No, nums[i] is <= nums[i-1].
            // If nums[i] + currentSum > target, we just continue. We can't break because smaller numbers later might fit.
            if (currentSum + nums[i] > target) continue;

            // Choose nums[i]
            visited[i] = true;
            if (canPartition(nums, visited, i + 1, k, currentSum + nums[i], target)) {
                return true;
            }
            // Backtrack
            visited[i] = false;

            // Pruning 5: If we failed to fill the subset with nums[i] as the first element (currentSum == 0),
            // then nums[i] can never be part of any valid partition because it must be in *some* subset,
            // and if it fails here (as the first element of a subset), it will fail everywhere else due to symmetry.
            if (currentSum == 0) return false;
            
            // Pruning 6: If nums[i] perfectly completed the subset (currentSum + nums[i] == target) but the recursion failed,
            // then no other combination will work for this specific subset requirement.
            // (Wait, this logic holds because we sort descending? Yes, roughly.)
            // Actually, if we just filled the bucket and it failed, trying a smaller element won't help if the larger one was optimal?
            // Not necessarily optimal, but for partition problems, this is a known strong pruning.
            if (currentSum + nums[i] == target) return false;
        }

        return false;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: Standard case
    vector<int> nums1 = {4, 3, 2, 3, 5, 2, 1};
    // Sum = 20. 
    // k=4, target=5 -> {5}, {4,1}, {3,2}, {3,2} - Possible.
    cout << "Test Case 1: " << sol.maxGroups(nums1) << " (Expected: 4)" << endl;

    // Test Case 2: Cannot be divided evenly except 1 group
    vector<int> nums2 = {1, 2, 3, 4, 7}; // Sum = 17 (Prime)
    cout << "Test Case 2: " << sol.maxGroups(nums2) << " (Expected: 1)" << endl;

    // Test Case 3: Duplicates
    vector<int> nums3 = {1, 1, 1, 1, 1, 1}; // Sum = 6
    // k=6, target=1 -> {1}, {1}, ...
    cout << "Test Case 3: " << sol.maxGroups(nums3) << " (Expected: 6)" << endl;
    
    // Test Case 4: Larger numbers
    vector<int> nums4 = {10, 10, 10, 20, 20, 20}; // Sum = 90
    // k=3, target=30 -> {10, 20}, {10, 20}, {10, 20}
    cout << "Test Case 4: " << sol.maxGroups(nums4) << " (Expected: 3)" << endl;

    return 0;
}
