#include <iostream>
#include "../mempool/mempool.h"

// Validate transaction before adding to the mempool
bool validateTransaction(const Transaction& tx) {
    if (tx.fee <= 0) {
        std::cerr << "[ERROR] Invalid transaction: Fee must be greater than zero." << std::endl;
        return false;
    }
    if (tx.size > 1000000) { // Limit transaction size to 1MB
        std::cerr << "[ERROR] Invalid transaction: Size exceeds 1MB limit." << std::endl;
        return false;
    }
    return true;
}
