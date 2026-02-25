#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int compareVersion(string version1, string version2) {
        int n = version1.length();
        int m = version2.length();
        int i = 0, j = 0;
        
        // 双指针遍历，只要有一个没走完就继续
        while (i < n || j < m) {
            long long num1 = 0;
            long long num2 = 0;
            
            // 计算 version1 当前段的数值
            while (i < n && version1[i] != '.') {
                num1 = num1 * 10 + (version1[i] - '0');
                i++;
            }
            
            // 计算 version2 当前段的数值
            while (j < m && version2[j] != '.') {
                num2 = num2 * 10 + (version2[j] - '0');
                j++;
            }
            
            // 比较当前段
            if (num1 > num2) return 1;
            if (num1 < num2) return -1;
            
            // 跳过点号
            i++;
            j++;
        }
        
        return 0;
    }
};
