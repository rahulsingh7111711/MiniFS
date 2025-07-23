#include "vfs.hpp"
#include <iostream>
#include <sstream>

int main() {
    VFS fs;
    std::string input;

    std::cout << "📂 MiniFS Virtual File System\nType 'exit' to quit\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        std::istringstream iss(input);
        std::string cmd, arg1, arg2;
        iss >> cmd >> arg1;
        std::getline(iss, arg2); // get rest of line for write
        if (!arg2.empty() && arg2[0] == ' ') arg2 = arg2.substr(1); // remove space

        if (cmd == "exit") break;
        else if (cmd == "mkdir") fs.mkdir(arg1);
        else if (cmd == "cd") fs.cd(arg1);
        else if (cmd == "ls") fs.ls();
        else if (cmd == "pwd") fs.pwd();
        else if (cmd == "touch") fs.touch(arg1);
        else if (cmd == "write") fs.write(arg1, arg2);
        else if (cmd == "read") fs.read(arg1);
        else if (cmd == "rm") fs.rm(arg1);
        else if (cmd == "rmdir") fs.rmdir(arg1);
        else std::cout << "❌ Unknown command\n";
    }

    return 0;
}
