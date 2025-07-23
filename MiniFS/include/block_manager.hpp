#ifndef BLOCK_MANAGER_HPP
#define BLOCK_MANAGER_HPP

#include <vector>
#include <string>

class BlockManager {
    static const int BLOCK_SIZE = 64;
    static const int TOTAL_BLOCKS = 256;

    std::vector<std::string> blocks;
    std::vector<bool> is_free;

public:
    BlockManager();

    std::vector<int> allocate(const std::string& data); // stores and returns block indices
    std::string read(const std::vector<int>& block_indices) const;
    void free(const std::vector<int>& block_indices);
};

#endif
