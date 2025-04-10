#include "value.h"

bool ListValue::popBack(std::string& val) {
    if (elements.empty()) return false;
    val = elements.back();
    elements.pop_back();
    return true;
}

bool ListValue::popFront(std::string& val) {
    if (elements.empty()) return false;
    val = elements.front();
    elements.erase(elements.begin());
    return true;
}

bool HashValue::get(const std::string& field, std::string& val) const {
    auto it = fields.find(field);
    if (it == fields.end()) return false;
    val = it->second;
    return true;
}

bool HashValue::remove(const std::string& field) {
    return fields.erase(field) > 0;
}
