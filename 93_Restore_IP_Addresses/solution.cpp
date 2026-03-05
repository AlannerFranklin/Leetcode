#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        if (s.empty()) return res;
        backtrack(s, 0);
        return res;
    }

private:
    vector<string> res;
    vector<string> track;

    void backtrack(const string& s, int start) {
        // Base Case: 字符串遍历完毕
        if (start == s.size()) {
            // 错误点1：必须正好是 4 段才算有效
            // 你的代码只检查了 start == s.size()，如果只有 3 段也会被加入结果（如 "1.1.1"）
            if (track.size() == 4) {
                res.push_back(join(track, "."));
            }
            return;
        }

        // 剪枝：如果已经有 4 段了，但还没遍历完字符串，说明方案无效
        // 放在这里或者循环里都可以，但更早剪枝更好
        if (track.size() == 4) return;

        for (int i = start; i < s.size(); i++) {
            // 剪枝：如果当前剩余的字符太多，后面怎么分都不够，也可以剪枝（可选优化）
            // if (s.size() - start > (4 - track.size()) * 3) return;

            // 注意：substr 第二个参数是长度
            // 你的代码 track.push_back(s.substr(start, i - start + 1)); 这里是对的
            
            // isValid 传入的是索引范围 [start, i]
            if (!isValid(s, start, i)) continue;
            
            track.push_back(s.substr(start, i - start + 1));
            backtrack(s, i + 1);
            track.pop_back();
        }
    }

    bool isValid(const string& s, int left, int right) {
        int length = right - left + 1;
        if (length == 0 || length > 3) {
            return false;
        }
        // "0" 是合法的，但 "01" 不合法
        if (length > 1 && s[left] == '0') return false;
        
        // 错误点2：stoi 的 substr 参数
        // s.substr(pos, len)
        // 你写的是 s.substr(left, right)，right 是索引，不是长度
        // 应该是 s.substr(left, length) 或者 s.substr(left, right - left + 1)
        if (stoi(s.substr(left, length)) > 255) return false;
        
        return true;
    }

    string join(const vector<string>& vec, const string& delim) {
        string result;
        for (size_t i = 0; i < vec.size(); ++i) {
            result += vec[i];
            if (i < vec.size() - 1) {
                result += delim;
            }
        }
        return result;
    }
};
