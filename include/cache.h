#ifndef SIMPLEDB_CACHE_H
#define SIMPLEDB_CACHE_H

#include <unordered_map>
#include <list>

template<typename K, typename V>
class LRUCache {
private:
    size_t capacity;
    std::list<std::pair<K, V>> lruList;
    std::unordered_map<K, typename std::list<std::pair<K, V>>::iterator> cache;
public:
    explicit LRUCache(size_t cap) : capacity(cap) {}

    bool get(const K& key, V& value) {
        auto it = cache.find(key);
        if (it == cache.end()) return false;
        lruList.splice(lruList.begin(), lruList, it->second);
        value = it->second->second;
        return true;
    }

    void put(const K& key, const V& value) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            it->second->second = value;
            lruList.splice(lruList.begin(), lruList, it->second);
            return;
        }
        if (lruList.size() == capacity) {
            auto last = lruList.back();
            cache.erase(last.first);
            lruList.pop_back();
        }
        lruList.emplace_front(key, value);
        cache[key] = lruList.begin();
    }

    void remove(const K& key) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            lruList.erase(it->second);
            cache.erase(it);
        }
    }

    void clear() {
        lruList.clear();
        cache.clear();
    }

    size_t size() const {
        return cache.size();
    }
};

#endif // SIMPLEDB_CACHE_H
