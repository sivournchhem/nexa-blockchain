#include "mempool.h"
#include <iostream>

// Adds a transaction to the mempool
void Mempool::addTransaction(const std::shared_ptr<Transaction>& tx) {
    std::lock_guard<std::mutex> lock(mempoolMutex);
    pool[tx->txid] = tx;
    std::cout << "[Mempool] Transaction " << tx->txid << " added." << std::endl;
}

// Processes transactions in the mempool
void Mempool::processTransactions() {
    std::lock_guard<std::mutex> lock(mempoolMutex);
    for (auto& pair : pool) {
        std::cout << "[Mempool] Processing transaction: " << pair.first << std::endl;
    }
}
