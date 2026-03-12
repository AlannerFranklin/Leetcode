#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

// 题目2：IPv4转十六进制
// 输入：字符串
// 输出：合法则输出十六进制字符串（如 C0A80101），非法输出 "X"
// 你的得分：75% -> 可能漏了特殊非法情况

string solveIPv4(string s) {
    vector<string> parts;
    string segment;
    stringstream ss(s);
    
    // 1. 检查是否包含非法字符（只能是数字和.）
    for (char c : s) {
        if (!isdigit(c) && c != '.') return "X";
    }

    // 2. 分割字符串
    while (getline(ss, segment, '.')) {
        parts.push_back(segment);
    }
    
    // 3. 检查分割后的段数
    // 注意：如果字符串以.结尾，stringstream可能不会分割出最后一个空串，需要特判
    if (s.back() == '.') return "X"; 
    if (parts.size() != 4) return "X";

    stringstream hexOut;
    hexOut << uppercase << hex << setfill('0');

    for (const string& part : parts) {
        // 4. 检查每段是否为空
        if (part.empty()) return "X";
        
        // 5. 检查前导0 (题目如果严格要求IPv4，"01"通常是非法的，除非是0)
        // 你的75%很可能挂在这里或者空串上
        if (part.size() > 1 && part[0] == '0') return "X";
        
        // 6. 检查长度（防止stoi越界）
        if (part.size() > 3) return "X";
        
        // 7. 转换数值并检查范围
        int val = stoi(part);
        if (val < 0 || val > 255) return "X";
        
        // 8. 转十六进制，宽度为2
        hexOut << setw(2) << val;
    }
    
    return hexOut.str();
}

int main() {
    // 测试用例
    vector<string> tests = {
        "192.168.1.1",   // C0A80101
        "255.0.0.0",     // FF000000
        "256.1.1.1",     // X (越界)
        "1.1.1",         // X (缺段)
        "1.1.1.1.",      // X (尾部点)
        "1..1.1",        // X (空段)
        "192.168.01.1",  // X (前导0?) - 这一点最存疑，看题目要求
        "a.b.c.d"        // X (非数字)
    };

    for (const auto& t : tests) {
        cout << t << " -> " << solveIPv4(t) << endl;
    }
    return 0;
}
