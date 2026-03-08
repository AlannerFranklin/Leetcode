#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

// 检查是否存在一个高度 h，使得我们可以构造出满足条件的 a' 和 b'
// 条件：
// 1. a'[i] + b'[i] = h
// 2. 0 <= a'[i] <= a[i]
// 3. 0 <= b'[i] <= b[i]  =>  0 <= h - a'[i] <= b[i]  =>  h - b[i] <= a'[i] <= h
// 4. |a'[i] - a'[i-1]| <= k
bool check(int h, int n, int k, const vector<int>& a, const vector<int>& b) {
    // 第一个位置 a'[0] 的可行区间 [low, high]
    // 必须满足: h - b[0] <= a'[0] <= a[0] 且 a'[0] <= h
    // 所以 low = max(0, h - b[0]), high = min(a[0], h)
    ll low = max(0LL, (ll)h - b[0]);
    ll high = min((ll)a[0], (ll)h);
    
    if (low > high) return false;

    // 当前 valid a'[i-1] 的范围
    ll cur_l = low, cur_r = high;

    for (int i = 1; i < n; ++i) {
        // 当前位置 i 本身的限制
        low = max(0LL, (ll)h - b[i]);
        high = min((ll)a[i], (ll)h);
        
        if (low > high) return false;

        // 结合前一个位置传递过来的限制: |a'[i] - a'[i-1]| <= k
        // 即 a'[i-1] - k <= a'[i] <= a'[i-1] + k
        // 也就是 cur_l - k <= a'[i] <= cur_r + k
        ll new_l = max(low, cur_l - k);
        ll new_r = min(high, cur_r + k);

        if (new_l > new_r) return false;

        cur_l = new_l;
        cur_r = new_r;
    }
    return true;
}

int main() {
    // 优化 I/O 速度，避免大数据量 TLE
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n), b(n);
        ll total = 0;
        int up = 2000000000; // 2e9，足够覆盖 a[i]+b[i] 的最大值

        for (int i = 0; i < n; ++i) {
            cin >> a[i] >> b[i];
            total += (ll)a[i] + b[i];
            // 显然最终的高度 h 不能超过任意一组 a[i]+b[i]
            // 因为 a'[i] <= a[i], b'[i] <= b[i] => a'[i]+b'[i] <= a[i]+b[i]
            up = min(up, a[i] + b[i]);
        }

        // 二分查找最大的可行高度 h
        // 我们希望磨掉的部分最少 => 也就是保留的部分 (n * h) 最大 => h 最大
        int lo = 0, hi = up, best = 0;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (check(mid, n, k, a, b)) {
                best = mid;
                lo = mid + 1; // 尝试更大的 h
            } else {
                hi = mid - 1; // 减小 h
            }
        }

        // 最小磨掉的高度 = 总高度 - 保留的总高度
        ll ans = total - (ll)n * best;
        cout << ans << "\n";
    }
    return 0;
}
