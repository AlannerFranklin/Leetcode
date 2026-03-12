#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> res;
    vector<int> track;
    int sum = 0;
    int sum_track = 0;
    void backtrack(vector<int>& nums, int index, int sum, int sum_track) {
        if (sum_track * index == sum) {
            res.push_back(track);
            return;
        }
        if (sum_track * index > sum) return;
        for (int i = index;i < nums.size();i++) {
            if (nums[i] + sum_track <= sum) {
                track.push_back(nums[i]);
                sum_track += nums[i];
                backtrack(nums, i + 1, sum, sum_track);
                track.pop_back();
                sum_track -= nums[i];
            }
        }
    }
    int fun(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i = 0;i < nums.size();i++) {
            sum += nums[i];
        }
    }
    backtrack(nums, 1, sum, sum_track);
    return res.size();
}