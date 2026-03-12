#include <iostream>
#include <vector>
using namespace std;

int main() {
    string source, target;
    cin>>source>>target;
    int left = 0, right = 0;
    int max_len = 0;
    string s = "";
    for (int i = 0;i < source.size();i++) {
        s = "";
        if (source[i] == target[0]) {
            left = i;
            int k = 1;
            for (int j = i + 1;j < source.size();j++) {
                if (source[j] == target[k]) {
                    k++;
                }
                if (k == target.size()) {
                    right = j;
                    break;
                }
            }
            if (max_len < right - left + 1) {
                max_len = right - left + 1;
                s = source.substr(left, max_len);
            }
        }
    }
    cout<<s<<endl;
    return 0;
}