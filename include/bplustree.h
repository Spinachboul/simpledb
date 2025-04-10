#ifndef SIMPLEDB_BPLUSTREE_H
#define SIMPLEDB_BPLUSTREE_H

#include <map>
#include <vector>

template<typename K, typename V>
class BPlusTree {
private:
    std::map<K, V> tree;
public:
    void insert(const K& key, const V& value) {
        tree[key] = value;
    }

    bool find(const K& key, V& value) const {
        auto it = tree.find(key);
        if (it == tree.end()) return false;
        value = it->second;
        return true;
    }

    std::vector<std::pair<K, V>> range(const K& startKey, const K& endKey) const {
        std::vector<std::pair<K, V>> result;
        for (auto it = tree.lower_bound(startKey); it != tree.end() && it->first <= endKey; ++it) {
            result.push_back(*it);
        }
        return result;
    }
};

#endif // SIMPLEDB_BPLUSTREE_H
