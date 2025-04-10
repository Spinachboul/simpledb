#include <iostream>
#include <sstream>
#include <string>

#include "simpledb.h"
#include "threadpool.h"

int main() {
    SimpleDB db("./simpledb.log", 1000);
    ThreadPool pool(4);

    std::cout << "SimpleDB started!\n";
    std::cout << "Type 'help' for commands.\n";

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "quit" || line == "exit") break;
        if (line == "help") {
            std::cout << "Commands:\n"
                      << "  SET key value\n"
                      << "  GET key\n"
                      << "  DEL key\n"
                      << "  EXIT\n";
            continue;
        }

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "SET") {
            std::string key, value;
            iss >> key;
            std::getline(iss, value);
            if (!value.empty() && value[0] == ' ') {
                value = value.substr(1);
            }
            pool.enqueue([&db, key, value] {
                if (db.setString(key, value)) {
                    std::cout << "OK\n";
                } else {
                    std::cout << "ERROR\n";
                }
            });
        } else if (cmd == "GET") {
            std::string key;
            iss >> key;
            pool.enqueue([&db, key] {
                std::string val;
                if (db.getString(key, val)) {
                    std::cout << val << "\n";
                } else {
                    std::cout << "(nil)\n";
                }
            });
        } else if (cmd == "DEL") {
            std::string key;
            iss >> key;
            pool.enqueue([&db, key] {
                if (db.deleteKey(key)) {
                    std::cout << "Deleted\n";
                } else {
                    std::cout << "Not found\n";
                }
            });
        } else {
            std::cout << "Unknown command\n";
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}
