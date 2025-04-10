#ifndef SIMPLEDB_WAL_H
#define SIMPLEDB_WAL_H

#include <fstream>
#include <mutex>
#include <string>
#include <vector>

enum class OperationType {
    SET,
    DELETE
};

struct LogRecord {
    OperationType op;
    std::string key;
    std::string value; // Only used for SET
};

class WriteAheadLog {
private:
    std::string filename;
    std::ofstream writer;
    std::mutex mtx;
public:
    explicit WriteAheadLog(const std::string& file);

    ~WriteAheadLog();

    void append(OperationType op, const std::string& key, const std::string& value = "");

    std::vector<LogRecord> readAll();
};

#endif // SIMPLEDB_WAL_H
