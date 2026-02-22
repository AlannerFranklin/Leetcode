#include <iostream>
#include <list>
#include <unordered_map>

class LRUCache {
public:
    // 定义双向链表的节点结构
    // 为什么需要存 key？因为当缓存满淘汰链表尾部节点时，需要通过 key 去删除哈希表中的记录
    struct Node {
        int key, value;
    };

    // 缓存容量
    int capacity;
    
    // 双向链表：存储实际的 (key, value) 数据
    // 链表头部 (begin) 是最近使用的数据 (Hot)
    // 链表尾部 (back) 是最久未使用的数据 (Cold)
    std::list<Node> cacheList;
    
    // 哈希表：存储 key 到 链表节点迭代器 的映射
    // 作用：实现 O(1) 的快速查找
    std::unordered_map<int, std::list<Node>::iterator> cacheMap;

    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        // 1. 在哈希表中查找 key
        auto it = cacheMap.find(key);
        
        // 2. 如果没找到，返回 -1
        if (it == cacheMap.end()) return -1;

        // 3. 如果找到了，说明这个 key 被使用了
        // 需要把它移动到链表头部 (变成最近使用)
        // splice(目标位置, 源链表, 源节点迭代器) 可以 O(1) 地移动节点
        cacheList.splice(cacheList.begin(), cacheList, it->second);
        
        // 4. 返回节点的值
        // it->second 是链表迭代器，it->second->value 才是节点的值
        return it->second->value;
    }
    
    void put(int key, int value) {
        auto it = cacheMap.find(key);
        
        if (it != cacheMap.end()) {
            // Case 1: Key 已存在 -> 更新值
            it->second->value = value;
            // 既然被更新了，也算是被使用了，移动到链表头部
            cacheList.splice(cacheList.begin(), cacheList, it->second);
        } else {
            // Case 2: Key 不存在 -> 插入新数据
            
            // 2.1 检查容量，如果满了要淘汰最久未使用的 (链表尾部)
            if (cacheList.size() == capacity) {
                // 获取链表最后一个节点
                Node& last = cacheList.back();
                // 先从哈希表中删除 (必须在从链表删除之前，因为要用到 last.key)
                cacheMap.erase(last.key); 
                // 再从链表中删除
                cacheList.pop_back();
            }
            
            // 2.2 在链表头部插入新节点
            cacheList.push_front({key, value});
            
            // 2.3 在哈希表中记录 key -> 新节点的迭代器
            cacheMap[key] = cacheList.begin();
        }
    }
};
