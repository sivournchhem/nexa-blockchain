#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>  // For smart pointers
#include "transaction.h"

class Mempool {
private:
    std::unordered_map<std::string, std::shared_ptr<Transaction>> pool;

public:
    // Destructor to clean up memory
    ~Mempool() {
        pool.clear();
        std::cout << "[Mempool] Cleared all transactions." << std::endl;
    }

    void addTransaction(const std::shared_ptr<Transaction>& tx) {
        pool[tx->txid] = tx;
        std::cout << "[Mempool] Transaction " << tx->txid << " added." << std::endl;
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
        std::vector<std::shared_ptr<Transaction>> sortedTxs;
	std::transform(pool.begin(), pool.end(), std::back_inserter(sortedTxs),
    	[](const auto& pair) { return pair.second; });
        std::sort(sortedTxs.begin(), sortedTxs.end(), [](const std::shared_ptr<Transaction>& a, const std::shared_ptr<Transaction>& b) {
            return (a->fee / a->size) > (b->fee / b->size);
        });

        std::cout << "[Mempool] Transactions sorted by priority." << std::endl;
    }
};

// Initialize Mempool globally
Mempool mempool;
