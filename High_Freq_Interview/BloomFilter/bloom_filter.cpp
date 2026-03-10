#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <functional>

using namespace std;

// ==========================================
// 布隆过滤器 (Bloom Filter)
// ==========================================
// 核心原理：
// 1. 使用一个大型位数组 (BitSet/Bitmap)，初始全为 0。
// 2. 使用 k 个不同的哈希函数。
// 3. 添加元素：将元素通过 k 个哈希函数映射到位数组的 k 个位置，并将这些位置置为 1。
// 4. 查询元素：将元素通过 k 个哈希函数映射到位数组的 k 个位置。
//    - 如果所有位置都为 1，则元素 *可能* 存在 (False Positive)。
//    - 如果任意一个位置为 0，则元素 *一定不* 存在。
//
// 优点：空间效率极高，查询速度快。
// 缺点：有误判率 (False Positive)，不支持删除操作（除非使用计数布隆过滤器）。
//
// 使用场景：
// 1. 网页黑名单系统（防止访问恶意网站）。
// 2. 垃圾邮件过滤。
// 3. 缓存穿透保护（Redis 前置过滤）。
// 4. 区块链/分布式系统中的快速成员检测。

class BloomFilter {
private:
    bitset<100000> bits; // 位数组大小，实际应用中根据 n 和 p 计算
    // 哈希函数种子
    vector<int> seeds = {3, 7, 11, 13, 31, 37, 61}; 

    // 简单的字符串哈希函数
    size_t hash(const string& s, int seed) {
        size_t result = 0;
        for (char c : s) {
            result = result * seed + c;
        }
        return result % bits.size();
    }

public:
    void add(const string& s) {
        for (int seed : seeds) {
            size_t pos = hash(s, seed);
            bits[pos] = 1;
        }
    }

    bool contains(const string& s) {
        for (int seed : seeds) {
            size_t pos = hash(s, seed);
            if (!bits[pos]) {
                return false; // 一定不存在
            }
        }
        return true; // 可能存在
    }
};

int main() {
    BloomFilter bf;
    
    // 添加 URL
    bf.add("www.google.com");
    bf.add("www.github.com");
    bf.add("www.stackoverflow.com");

    // 查询
    cout << "Contains google? " << bf.contains("www.google.com") << " (Expected: 1)" << endl;
    cout << "Contains baidu? " << bf.contains("www.baidu.com") << " (Expected: 0)" << endl;
    
    // 误判测试 (False Positive)
    // 实际应用中，如果位数组太小或哈希函数不够好，可能会出现误判。
    
    return 0;
}
