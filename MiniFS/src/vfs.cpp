#include "vfs.hpp"
#include "block_manager.hpp"

#include <iostream>
#include <sstream>
#include <vector>

BlockManager blockManager;

VFS::VFS() {
    root = std::make_shared<Node>("/", NodeType::DIRECTORY);
    current = root;
}

void VFS::mkdir(const std::string& name) {
    if (current->getChild(name)) {
        std::cout << "Directory already exists: " << name << "\n";
        return;
    }

    auto dir = std::make_shared<Node>(name, NodeType::DIRECTORY);
    dir->parent = current;
    current->children.push_back(dir);
}

void VFS::ls() const {
    for (const auto& child : current->children) {
        std::cout << child->name << (child->type == NodeType::DIRECTORY ? "/" : "") << " ";
    }
    std::cout << "\n";
}

void VFS::cd(const std::string& path) {
    if (path == "/") {
        current = root;
        return;
    }

    std::shared_ptr<Node> temp = current;
    std::istringstream iss(path);
    std::string token;

    while (std::getline(iss, token, '/')) {
        if (token.empty() || token == ".") continue;
        if (token == "..") {
            if (auto parent = temp->parent.lock()) {
                temp = parent;
            }
        } else {
            auto next = temp->getChild(token);
            if (!next || next->type != NodeType::DIRECTORY) {
                std::cout << "Directory not found: " << token << "\n";
                return;
            }
            temp = next;
        }
    }

    current = temp;
}

void VFS::pwd() const {
    std::vector<std::string> pathParts;
    std::shared_ptr<Node> temp = current;

    while (temp && temp != root) {
        pathParts.push_back(temp->name);
        temp = temp->parent.lock();
    }

    std::cout << "/";
    for (auto it = pathParts.rbegin(); it != pathParts.rend(); ++it) {
        std::cout << *it << "/";
    }
    std::cout << "\n";
}

void VFS::touch(const std::string& name) {
    if (current->getChild(name)) {
        std::cout << "File already exists: " << name << "\n";
        return;
    }

    auto file = std::make_shared<Node>(name, NodeType::FILE);
    file->parent = current;
    current->children.push_back(file);
}

void VFS::write(const std::string& filename, const std::string& data) {
    for (auto& child : current->children) {
        if (child->name == filename && child->type == NodeType::FILE) {
            if (!child->block_indices.empty()) {
                blockManager.free(child->block_indices);
            }

            auto indices = blockManager.allocate(data);
            if (indices.empty()) {
                std::cout << "❌ Not enough space to write file\n";
                return;
            }

            child->block_indices = indices;
            std::cout << "✅ Written to " << filename << " in blocks\n";
            return;
        }
    }

    std::cout << "❌ File not found: " << filename << "\n";
}

void VFS::read(const std::string& filename) const {
    for (const auto& child : current->children) {
        if (child->name == filename && child->type == NodeType::FILE) {
            if (child->block_indices.empty()) {
                std::cout << "(empty file)\n";
                return;
            }

            std::string content = blockManager.read(child->block_indices);
            std::cout << content << "\n";
            return;
        }
    }

    std::cout << "❌ File not found: " << filename << "\n";
}

void VFS::rm(const std::string& name) {
    auto& children = current->children;

    for (auto it = children.begin(); it != children.end(); ++it) {
        if ((*it)->name == name && (*it)->type == NodeType::FILE) {
            blockManager.free((*it)->block_indices);
            children.erase(it);
            std::cout << "🗑️ Deleted file: " << name << "\n";
            return;
        }
    }

    std::cout << "❌ File not found: " << name << "\n";
}

void VFS::rmdir(const std::string& name) {
    auto& children = current->children;

    for (auto it = children.begin(); it != children.end(); ++it) {
        if ((*it)->name == name && (*it)->type == NodeType::DIRECTORY) {
            if (!(*it)->children.empty()) {
                std::cout << "❌ Directory not empty: " << name << "\n";
                return;
            }

            children.erase(it);
            std::cout << "🗑️ Deleted directory: " << name << "\n";
            return;
        }
    }

    std::cout << "❌ Directory not found: " << name << "\n";
}
