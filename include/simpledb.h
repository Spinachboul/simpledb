#ifndef SIMPLEDB_SIMPLEDB_H
#define SIMPLEDB_SIMPLEDB_H

#include "value.h"
#include "cache.h"
#include "bplustree.h"
#include "wal.h"

#include <unordered_map>
#include <shared_mutex>
#include <memory>
#include <string>

class SimpleDB {
private:
    std::unordered_map<std::string, std::shared_ptr<Value>> data;
    mutable std::shared_mutex dataMutex;
    LRUCache<std::string, std::shared_ptr<Value>> cache;
    WriteAheadLog wal;
    BPlusTree<std::string, std::string> index;
public:
    explicit SimpleDB(const std::string& walFile, size_t cacheSize = 1000);

    // String operations
    bool setString(const std::string& key, const std::string& value);
    bool getString(const std::string& key, std::string& value);

    // Delete
    bool deleteKey(const std::string& key);

    // Recovery
    void recover();
};

#endif // SIMPLEDB_SIMPLEDB_H
