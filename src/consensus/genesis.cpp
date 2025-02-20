#include <iostream>
#include "consensus.h"

struct GenesisBlock {
    uint64_t totalSupply;
    std::string genesisHash;
};

// Define total supply
const uint64_t TOTAL_SUPPLY = 23000000 * 100000000; // 23M NXA in smallest units

// Function to generate the Genesis Block
GenesisBlock createGenesisBlock() {
    GenesisBlock genesisBlock;
    genesisBlock.totalSupply = TOTAL_SUPPLY;
    genesisBlock.genesisHash = "00000abc12345..."; // Placeholder hash

    std::cout << "Genesis Block Created - Total Supply: " << genesisBlock.totalSupply << " NXA" << std::endl;
    return genesisBlock;
}
