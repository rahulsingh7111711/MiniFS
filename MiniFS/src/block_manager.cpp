#include "block_manager.hpp"
#include <iostream>

BlockManager::BlockManager() {
    blocks.resize(TOTAL_BLOCKS, "");
    is_free.resize(TOTAL_BLOCKS, true);
}

std::vector<int> BlockManager::allocate(const std::string& data) {
    std::vector<int> indices;
    int total = (data.size() + BLOCK_SIZE - 1) / BLOCK_SIZE;
    int count = 0;

    for (int i = 0; i < TOTAL_BLOCKS && count < total; ++i) {
        if (is_free[i]) {
            int start = count * BLOCK_SIZE;
            blocks[i] = data.substr(start, BLOCK_SIZE);
            is_free[i] = false;
            indices.push_back(i);
            ++count;
        }
    }

    if (count < total) {
        std::cerr << "❌ Not enough memory blocks\n";
        // Free any partial allocation
        for (int i : indices) {
            is_free[i] = true;
            blocks[i].clear();
        }
        return {};
    }

    return indices;
}

std::string BlockManager::read(const std::vector<int>& block_indices) const {
    std::string result;
    for (int i : block_indices) {
        result += blocks[i];
    }
    return result;
}

void BlockManager::free(const std::vector<int>& block_indices) {
    for (int i : block_indices) {
        blocks[i].clear();
        is_free[i] = true;
    }
}
