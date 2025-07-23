// include/node.hpp
#pragma once
#include <string>
#include <vector>
#include <memory>

enum class NodeType { FILE, DIRECTORY };

struct Node {
    std::string name;
    NodeType type;
    std::weak_ptr<Node> parent;
    std::vector<std::shared_ptr<Node>> children;

    Node(const std::string& name, NodeType type);
    std::shared_ptr<Node> getChild(const std::string& childName);
    std::string content;
    // Add inside Node struct
    std::vector<int> block_indices;

};
