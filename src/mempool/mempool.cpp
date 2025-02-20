#include <iostream>
#include <vector>
#include <unordered_map>

struct Transaction {
    std::string txid;
    double fee;
};

class Mempool {
private:
    std::unordered_map<std::string, Transaction> pool;

public:
    void addTransaction(const Transaction& tx) {
        pool[tx.txid] = tx;
        std::cout << "[Mempool] Transaction " << tx.txid << " added." << std::endl;
    }

    void removeTransaction(const std::string& txid) {
        if (pool.find(txid) != pool.end()) {
            pool.erase(txid);
            std::cout << "[Mempool] Transaction " << txid << " removed." << std::endl;
        }
    }

    size_t getMempoolSize() {
        return pool.size();
    }

    void printMempool() {
        std::cout << "[Mempool] Current transactions: " << std::endl;
        for (const auto& pair : pool) {
            std::cout << " - " << pair.first << " (Fee: " << pair.second.fee << ")" << std::endl;
        }
    }
};

// Initialize Mempool globally
Mempool mempool;
