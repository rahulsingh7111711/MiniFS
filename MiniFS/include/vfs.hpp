#pragma once
#include "node.hpp"
#include <memory>
#include <string>

class VFS {
private:
    std::shared_ptr<Node> root;
    std::shared_ptr<Node> current;

public:
    VFS();
    void mkdir(const std::string& name);
    void ls() const;
    void cd(const std::string& path);
    void pwd() const;
    void touch(const std::string& name);
    void write(const std::string& filename, const std::string& data);  // ✅ final write
    void read(const std::string& name) const;                           // ✅ fixed: added const
    void rm(const std::string& name);
    void rmdir(const std::string& name);
};
