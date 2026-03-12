#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_map>
#include <algorithm>

using namespace std;

// User's TLE/Buggy Solution (reproduced for testing)
long long user_solution(int n, vector<int>& nums) {
    if (n == 0) return 0;
    vector<long long> num_q(n);
    for(int i = 0; i < n; i++){
        if(i == 0) num_q[i] = nums[i];
        else num_q[i] = num_q[i-1] + nums[i];
    }
    vector<long long> num_h(n);
    for(int i = n-1; i >= 0; i--){
        if(i == n-1) num_h[i] = nums[i];
        else num_h[i] = num_h[i+1] + nums[i];
    }
    
    int left_count = 0;
    int right_count = 0;
    
    if(num_q[n - 1] % 2 != 0){
        return 0;
    }
    
    long long left_half_sum = num_q[n-1]/2;
    for(int i = n-1; i >= 0; i--){
        for(int j = i - 1; j >= 0; j--){
            if(left_half_sum == num_q[j]){
                left_count++;
                if(left_half_sum % 2 == 0) {
                    left_half_sum /= 2;
                    i = j;
                }
                else goto end_left; // break outer loop logic simulation
            }
        }
    }
    end_left:;

    long long right_half_sum = num_h[0]/2;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(right_half_sum == num_h[j]){
                right_count++;
                if(right_half_sum % 2 == 0) {
                    right_half_sum /= 2;
                    i = j;
                }
                else goto end_right;
            }
        }
    }
    end_right:;

    return max(0, left_count + right_count - 1);
}

// Optimized Correct Solution
// Use a map to store prefix sum indices for O(1) lookup
unordered_map<long long, vector<int>> prefix_map;
vector<long long> P;

int solve(int left, int right) {
    if (left >= right) return 0;
    
    long long total = P[right] - P[left];
    if (total == 0 || total % 2 != 0) return 0;
    
    long long target = P[left] + total / 2;
    
    // Check if target exists in prefix_map within range (left, right-1]
    if (prefix_map.find(target) == prefix_map.end()) return 0;
    
    const vector<int>& indices = prefix_map[target];
    
    // Find the first valid split point > left and < right
    // Using upper_bound to find first element > left
    // Since we store 1-based indices in P (P[i] is sum of first i elements),
    // P[k] corresponds to sum of nums[0...k-1].
    // Range [left, right) in P corresponds to nums[left...right-1].
    // Wait, let's align indices carefully.
    // P[0] = 0. P[i] = sum(nums[0]...nums[i-1]).
    // Range sum nums[i...j] = P[j+1] - P[i].
    // Current range is nums[L...R]. Indices in P are L and R+1.
    // We need split point k such that sum(nums[L...k]) == sum(nums[k+1...R]).
    // P[k+1] - P[L] == (P[R+1] - P[L]) / 2.
    // Target P value = P[L] + Total/2.
    // We need an index `idx` in P such that P[idx] == Target and L < idx <= R.
    // (Split happens after nums[idx-1], so left part is nums[L...idx-1], right is nums[idx...R]).
    // Length of left part = idx - L. Must be >= 1. So idx > L.
    // Length of right part = R+1 - idx. Must be >= 1. So idx <= R.
    
    auto it = upper_bound(indices.begin(), indices.end(), left);
    if (it == indices.end() || *it > right) return 0;
    
    int split_idx = *it; // This is the index in P
    
    // Recurse
    // Left part: nums[left ... split_idx-1]. P indices [left, split_idx].
    // Right part: nums[split_idx ... right]. P indices [split_idx, right+1].
    // Note: right argument in solve is exclusive upper bound of nums index?
    // Let's use P indices for recursion: solve(p_start, p_end)
    
    return 1 + solve(left, split_idx) + solve(split_idx, right);
}

long long correct_solution(int n, vector<int>& nums) {
    if (n <= 1) return 0;
    P.assign(n + 1, 0);
    prefix_map.clear();
    prefix_map[0].push_back(0);
    
    for (int i = 0; i < n; ++i) {
        P[i+1] = P[i] + nums[i];
        prefix_map[P[i+1]].push_back(i+1);
    }
    
    // Solve for range [0, n] in P indices (covering nums[0...n-1])
    return solve(0, n);
}

int main() {
    // Test Case 1: Simple [2, 2, 2, 2]
    // User: 3, Correct: 3
    vector<int> nums1 = {2, 2, 2, 2};
    cout << "Test 1 [2, 2, 2, 2]:" << endl;
    cout << "User: " << user_solution(4, nums1) << endl;
    cout << "Correct: " << correct_solution(4, nums1) << endl;
    
    // Test Case 2: [2, 2, 4]
    // User: 2, Correct: 2
    // 2,2 | 4 (Split 1)
    // 2|2 | 4 (Split 2)
    vector<int> nums2 = {2, 2, 4};
    cout << "\nTest 2 [2, 2, 4]:" << endl;
    cout << "User: " << user_solution(3, nums2) << endl;
    cout << "Correct: " << correct_solution(3, nums2) << endl;
    
    // Test Case 3: Counter-Example [2, 2, 2, 2, 4, 4] Sum=16
    // Split 8: [2,2,2,2] | [4,4] (1)
    // Left [2,2,2,2] -> [2,2]|[2,2] (2) -> [2]|[2] and [2]|[2] (4) -> Total Left 3 splits.
    // Right [4,4] -> [4]|[4] (1) -> Total Right 1 split.
    // Total = 1 + 3 + 1 = 5.
    // User logic: Left depth 3, Right depth 2. Result 3+2-1=4. WRONG.
    vector<int> nums3 = {2, 2, 2, 2, 4, 4};
    cout << "\nTest 3 [2, 2, 2, 2, 4, 4]:" << endl;
    cout << "User: " << user_solution(6, nums3) << endl;
    cout << "Correct: " << correct_solution(6, nums3) << endl;

    return 0;
}
