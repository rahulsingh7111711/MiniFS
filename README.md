# 🗂️ MiniFS - A Minimal In-Memory File System in C++

MiniFS is a simplified virtual file system simulator written in C++. It replicates basic filesystem operations like creating directories and files, navigating the structure, and reading/writing data using a simulated block-based memory manager.

---

## 🚀 Features

- 📁 Create directories and navigate (`mkdir`, `cd`, `pwd`, `ls`)
- 📄 Create and manage files (`touch`, `write`, `read`, `rm`)
- 🧱 Block-based memory management for file storage
- 🧹 Directory deletion with child check (`rmdir`)
- ❌ Error handling for invalid commands and paths

---

## 🧱 Architecture Overview

- **Node System:** Represents files and folders using a tree structure.
- **BlockManager:** Simulates disk blocks with allocation/free tracking.
- **VFS Class:** Handles file system logic and operations.
- **CLI Interface:** Processes user input and dispatches commands.

---

## 🛠️ Build Instructions

### Prerequisites

- C++17 compiler (e.g., `g++`, `clang++`)
- Linux/WSL/MacOS or any POSIX-compatible terminal

### Build

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o MiniFS

Run
./MiniFS

## Sample Use
$ ./MiniFS
MiniFS > mkdir projects
MiniFS > cd projects
MiniFS > touch notes.txt
MiniFS > write notes.txt "Virtual FS working!"
MiniFS > read notes.txt
Virtual FS working!
MiniFS > pwd
/projects/
MiniFS > ls
notes.txt
