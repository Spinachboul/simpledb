#ifndef SIMPLEDB_VALUE_H
#define SIMPLEDB_VALUE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

enum class ValueType {
    STRING,
    LIST,
    HASH,
    NONE
};

class Value {
public:
    virtual ~Value() = default;
    virtual ValueType getType() const = 0;
};

class StringValue : public Value {
private:
    std::string data;
public:
    explicit StringValue(const std::string& val) : data(val) {}
    ValueType getType() const override { return ValueType::STRING; }
    const std::string& get() const { return data; }
    void set(const std::string& val) { data = val; }
};

class ListValue : public Value {
private:
    std::vector<std::string> elements;
public:
    ValueType getType() const override { return ValueType::LIST; }
    void pushBack(const std::string& val) { elements.push_back(val); }
    void pushFront(const std::string& val) { elements.insert(elements.begin(), val); }
    bool popBack(std::string& val);
    bool popFront(std::string& val);
    const std::vector<std::string>& getAll() const { return elements; }
};

class HashValue : public Value {
private:
    std::unordered_map<std::string, std::string> fields;
public:
    ValueType getType() const override { return ValueType::HASH; }
    void set(const std::string& field, const std::string& val) { fields[field] = val; }
    bool get(const std::string& field, std::string& val) const;
    bool remove(const std::string& field);
    const std::unordered_map<std::string, std::string>& getAll() const { return fields; }
};

#endif // SIMPLEDB_VALUE_H
