#include <iostream>

using namespace std;

// User's solution for reference
void user_solution(long long n, long long m) {
    if (n >= m * 3) {
        if ((n - m * 3) % 2 == 0) {
            cout << "User: " << m + (n - m * 3) / 2 << endl;
        } else {
            cout << "User: " << m + 1 + (n - 3 * m - 3) / 2 << endl;
        }
    } else {
        cout << "User: -1" << endl;
    }
}

// Correct solution
void correct_solution(long long n, long long m) {
    long long max_k = -1;
    
    // Try using m odd primes
    if (n >= 3 * m) {
        long long rem = n - 3 * m;
        if (rem % 2 == 0) {
            max_k = max(max_k, m + rem / 2);
        }
    }
    
    // Try using 2m odd primes (only if needed or better)
    // Actually, using more odd primes (2m vs m) always reduces the total count k
    // because we replace two 3s (sum 6, count 2) with three 2s (sum 6, count 3).
    // So we prefer smaller number of odd primes.
    // However, if using m odd primes is impossible due to parity, we must try 2m.
    
    if (max_k == -1) { // Only check if first attempt failed
        if (n >= 6 * m) {
            long long rem = n - 6 * m;
            if (rem % 2 == 0) {
                max_k = max(max_k, 2 * m + rem / 2);
            }
        }
    }
    
    cout << "Correct: " << max_k << endl;
}

int main() {
    long long n, m;
    // Test Case 1: n=10, m=2 (m odd primes work)
    cout << "Test 1 (n=10, m=2):" << endl;
    user_solution(10, 2);
    correct_solution(10, 2);
    
    // Test Case 2: n=11, m=2 (Impossible - parity mismatch for m=2)
    cout << "\nTest 2 (n=11, m=2):" << endl;
    user_solution(11, 2);
    correct_solution(11, 2);
    
    // Test Case 3: n=12, m=3 (m=3 fails parity, try 2m=6 impossible sum)
    cout << "\nTest 3 (n=12, m=3):" << endl;
    user_solution(12, 3);
    correct_solution(12, 3);
    
    // Test Case 4: n=20, m=3 (m=3 fails parity, 2m=6 works)
    cout << "\nTest 4 (n=20, m=3):" << endl;
    user_solution(20, 3);
    correct_solution(20, 3);
    
    // Test Case 5: n=20, m=1 (m=1 fails parity, 2m=2 works)
    cout << "\nTest 5 (n=20, m=1):" << endl;
    user_solution(20, 1);
    correct_solution(20, 1);

    return 0;
}
