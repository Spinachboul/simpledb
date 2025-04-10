#include "simpledb.h"

SimpleDB::SimpleDB(const std::string& walFile, size_t cacheSize)
    : cache(cacheSize), wal(walFile) {
    recover();
}

bool SimpleDB::setString(const std::string& key, const std::string& value) {
    std::unique_lock lock(dataMutex);
    auto strVal = std::make_shared<StringValue>(value);
    data[key] = strVal;
    cache.put(key, strVal);
    index.insert(key, value);
    wal.append(OperationType::SET, key, value);
    return true;
}

bool SimpleDB::getString(const std::string& key, std::string& value) {
    std::shared_ptr<Value> val;
    if (cache.get(key, val)) {
        if (val->getType() == ValueType::STRING) {
            value = std::static_pointer_cast<StringValue>(val)->get();
            return true;
        }
        return false;
    }
    std::shared_lock lock(dataMutex);
    auto it = data.find(key);
    if (it == data.end()) return false;
    if (it->second->getType() != ValueType::STRING) return false;
    value = std::static_pointer_cast<StringValue>(it->second)->get();
    cache.put(key, it->second);
    return true;
}

bool SimpleDB::deleteKey(const std::string& key) {
    std::unique_lock lock(dataMutex);
    bool removed = data.erase(key) > 0;
    cache.remove(key);
    if (removed) {
        wal.append(OperationType::DELETE, key);
    }
    return removed;
}

void SimpleDB::recover() {
    auto logs = wal.readAll();
    for (const auto& record : logs) {
        if (record.op == OperationType::SET) {
            data[record.key] = std::make_shared<StringValue>(record.value);
            index.insert(record.key, record.value);
        } else if (record.op == OperationType::DELETE) {
            data.erase(record.key);
        }
    }
}
