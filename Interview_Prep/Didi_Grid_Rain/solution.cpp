#include <iostream>
#include <map>

using namespace std;

// 题目分析：
// 1. 数据范围：n 可达 10^9，数组开不下 -> 必须用 map 或离散化。
// 2. 操作：区间加法 [l, r] += d -> 典型差分数组应用。
// 3. 目标：求 f(x) 的不同取值个数。f(x) = 高度 >= x 的方格堆数量。

int main() {
    // 优化 IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // 差分数组 diff
    // diff[pos] 表示在 pos 位置高度的变化量
    // 使得 height[i] = height[i-1] + diff[i]
    // 区间 [l, r] 增加 d 等价于：diff[l] += d, diff[r+1] -= d
    map<int, long long> diff;
    
    for (int i = 0; i < m; ++i) {
        int l, r, d;
        cin >> l >> r >> d;
        diff[l] += d;
        // 注意：这里 r+1 可能会超过 n，但 map 会自动处理，且我们在最后统计时只关心 <= n 的部分
        diff[r + 1] -= d;
    }

    // cnt[h] = 拥有高度 h 的方格堆的数量
    // 这里的 h 指的是最终的高度
    map<long long, long long> cnt;
    
    long long cur = 0; // 当前高度
    int prev = 1;      // 上一个有变化的位置
    
    for (auto const& [pos, delta] : diff) {
        // 如果当前位置超过了 n，我们只需要处理到 n 为止
        if (pos > n) {
            break;
        }

        // 统计 [prev, pos-1] 这一段的高度
        // 这一段的高度都是 cur
        long long len = pos - prev;
        if (len > 0) {
            if (cur > 0) { // 只统计高度 > 0 的，虽然题目没明说初始高度0算不算，但通常f(x)关注正高度
                           // 题目问的是 f(1)...f(10^100)，所以高度0其实不影响 f(x>=1)
                cnt[cur] += len;
            }
        }

        // 更新当前高度
        cur += delta;
        // 更新上一个位置
        prev = pos;
    }

    // 处理最后一段：从 map 中最后一个 pos 到 n
    // 如果 diff 中的位置都 <= n，那么 diff[r+1] 会产生一个 > n 的 key
    // 但如果 diff 中所有 r+1 都 <= n，或者 map 遍历完了 prev 还在 n 里面
    if (prev <= n) {
        long long len = n - prev + 1;
        if (cur > 0) {
            cnt[cur] += len;
        }
    }

    // 核心逻辑：f(x) 的不同取值个数
    // f(x) = count(height >= x)
    // 随着 x 增大，f(x) 的值只会在 x 越过某个实际存在的高度时发生变化。
    // 比如有高度 10, 20, 30。
    // x 在 [1, 10] 时，f(x) 不变。
    // x 变成 11 时，f(x) 减少了 count(height=10)。
    // 所以，每一种非零高度都会导致 f(x) 的值发生一次“台阶式”下降。
    // 加上 x 很大时 f(x) = 0 这种情况。
    // 总取值数 = 非零高度的种类数 + 1 (对应 f(x)=0)
    int ans = cnt.size() + 1;
    
    cout << ans << endl;

    return 0;
}
