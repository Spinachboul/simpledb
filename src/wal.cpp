#include "wal.h"
#include <fstream>
#include <sstream>

WriteAheadLog::WriteAheadLog(const std::string& file) : filename(file) {
    writer.open(filename, std::ios::app);
}

WriteAheadLog::~WriteAheadLog() {
    if (writer.is_open()) {
        writer.close();
    }
}

void WriteAheadLog::append(OperationType op, const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(mtx);
    if (op == OperationType::SET) {
        writer << "SET " << key << " " << value << "\n";
    } else if (op == OperationType::DELETE) {
        writer << "DEL " << key << "\n";
    }
    writer.flush();
}

std::vector<LogRecord> WriteAheadLog::readAll() {
    std::lock_guard<std::mutex> lock(mtx);
    std::vector<LogRecord> records;
    std::ifstream reader(filename);
    std::string line;
    while (std::getline(reader, line)) {
        std::istringstream iss(line);
        std::string cmd, key, value;
        iss >> cmd >> key;
        if (cmd == "SET") {
            std::getline(iss, value);
            if (!value.empty() && value[0] == ' ') {
                value = value.substr(1);
            }
            records.push_back(LogRecord{OperationType::SET, key, value});
        } else if (cmd == "DEL") {
            records.push_back(LogRecord{OperationType::DELETE, key, ""});
        }
    }
    return records;
}
