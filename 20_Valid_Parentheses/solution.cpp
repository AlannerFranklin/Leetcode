#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        if (s.size() % 2 != 0) return false; // 奇数长度肯定无效
        
        stack<char> stack;
        for (char c : s) {
            if (c == '(') stack.push(')');
            else if (c == '[') stack.push(']');
            else if (c == '{') stack.push('}');
            else if (stack.empty() || stack.top() != c) {
                return false; // 栈空了或者不匹配
            } else {
                stack.pop(); // 匹配成功
            }
        }
        return stack.empty(); // 必须全消完才算对
    }
};
