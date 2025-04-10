# SimpleDB

**SimpleDB** is a lightweight, beginner-friendly in-memory database project that demonstrates key database concepts like:

- String key-value storage
- LRU (Least Recently Used) caching
- Write-Ahead Logging (WAL) for persistence
- Simple B+ Tree-like indexing
- Basic multi-threaded command execution

---

## How to Build

1. **Install CMake** (if not installed):
    ```bash
    sudo apt update
    sudo apt install cmake
    ```

2. **Build the project**:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

3. **Run SimpleDB**:
    ```bash
    ./simpledb
    ```

---

## Demonstration Commands

You can try the following commands after running:

| Command Example | Description |
|:---|:---|
| `SET name John` | Stores `"John"` at key `"name"`. |
| `GET name` | Retrieves and displays `"John"`. |
| `DEL name` | Deletes the key `"name"`. |
| `GET name` | Shows `(nil)` after deletion. |
| `exit` | Exits the app. |

Persistence is handled automatically via the Write-Ahead Log (WAL):  
**Data survives app restarts**.

---

## Video Demonstration


https://github.com/user-attachments/assets/07d91540-e817-438b-88a1-93e6ab41c0d3

## Technical Highlights

- **Write-Ahead Logging**: Ensures crash safety by logging before applying changes.
- **LRU Cache**: Hot keys are kept for fast retrieval.
- **Simple Indexing**: B+ tree-like structure for fast range queries.
- **ThreadPool**: Commands run in basic concurrent manner.
- **Recovery**: On restart, WAL log is replayed to restore last good state.

## Built With

- C++17
- CMake
- Standard STL libraries
