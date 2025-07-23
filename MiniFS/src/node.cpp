// src/node.cpp
#include "node.hpp"

Node::Node(const std::string& name, NodeType type)
    : name(name), type(type) {}

std::shared_ptr<Node> Node::getChild(const std::string& childName) {
    for (const auto& child : children) {
        if (child->name == childName) {
            return child;
        }
    }
    return nullptr;
}
