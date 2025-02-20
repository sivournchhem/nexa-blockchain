#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "transaction.h"

class Mempool {
private:
    std::unordered_map<std::string, Transaction> pool;

public:
    void addTransaction(const Transaction& tx) {
        pool[tx.txid] = tx;
        std::cout << "[Mempool] Transaction " << tx.txid << " added." << std::endl;
    }

    void removeTransaction(const std::string& txid) {
        pool.erase(txid);
        std::cout << "[Mempool] Transaction " << txid << " removed." << std::endl;
    }

    size_t getMempoolSize() const {
        return pool.size();
    }

    void prioritizeTransactions() {
        // Sort transactions based on fee per byte
        std::vector<Transaction> sortedTxs;
        for (const auto& pair : pool) {
            sortedTxs.push_back(pair.second);
        }
        std::sort(sortedTxs.begin(), sortedTxs.end(), [](const Transaction& a, const Transaction& b) {
            return (a.fee / a.size) > (b.fee / b.size);
        });

        std::cout << "[Mempool] Transactions sorted by priority." << std::endl;
    }
};

// Initialize Mempool globally
Mempool mempool;
