#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // ERROR 1: Type name is unordered_set, not unordered
        unordered_set<char> window; 
        int left = 0;
        int max_length = 0;
        
        for(int i = 0; i < s.length(); i++) 
        {
            char ch = s[i];
            
            // ERROR 2: .find() returns iterator, not boolean. Should compare with .end()
            // if(window.find(ch)) { 
            if (window.find(ch) != window.end()) {
                
                // ERROR 3: Logic error in handling duplicates
                // Current logic: only removes ONE element (begin), which might not be the duplicate
                // And only updates max_length when duplicate is found (misses non-duplicate updates)
                
                // window.erase(window.begin()); // Removes arbitrary element!
                // max_length = std::max(i - left, max_length);
                
                // Correct logic needs a while loop to remove elements from left until duplicate is gone
            } else {
                window.insert(ch);
                // ERROR 4: max_length should be updated here too (or in every iteration)
            }
        }
        return max_length;
    }
};

// Simplified version for demonstration of the logic error
void test_logic(string s) {
    cout << "Testing string: \"" << s << "\"" << endl;
    unordered_set<char> window;
    int left = 0;
    int max_length = 0;
    
    cout << "Step-by-step execution:" << endl;
    for(int i = 0; i < s.length(); i++) {
        char ch = s[i];
        cout << "Index " << i << ", Char '" << ch << "': ";
        
        if(window.find(ch) != window.end()) {
            cout << "Duplicate found! ";
            // User's logic: just erase begin() (undefined order in hash set!)
            if (!window.empty()) {
                char removed = *window.begin();
                window.erase(window.begin());
                cout << "Removed arbitrary '" << removed << "'. ";
            }
            max_length = max(i - left, max_length);
            cout << "Max len updated to " << max_length << endl;
        } else {
            window.insert(ch);
            cout << "Inserted. Window size: " << window.size() << endl;
        }
    }
    cout << "Final Result: " << max_length << endl;
    cout << "----------------------------------------" << endl;
}

int main() {
    test_logic("abcabcbb"); // Expected: 3
    test_logic("pwwkew");   // Expected: 3
    return 0;
}
