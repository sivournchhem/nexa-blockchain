#include <iostream>
#include <stdexcept>

// Define total fixed supply
const uint64_t TOTAL_SUPPLY = 23000000ULL * 100000000ULL;

// Function to return max supply
uint64_t getMaxSupply() {
    return TOTAL_SUPPLY;
}

// Prevent minting beyond 23M NXA
bool validateSupply(uint64_t currentSupply) {
    if (currentSupply >= TOTAL_SUPPLY) {
        throw std::runtime_error("Error: Supply limit of 23,000,000 NXA reached. No additional coins can be minted.");
    }
    return true;
}
