#ifndef MEMPOOL_H
#define MEMPOOL_H

#include <unordered_map>
#include "transaction.h"

class Mempool {
private:
    std::unordered_map<std::string, Transaction> pool;

public:
    void addTransaction(const Transaction& tx);
    void removeTransaction(const std::string& txid);
    size_t getMempoolSize();
    void prioritizeTransactions();
};

extern Mempool mempool;

#endif // MEMPOOL_H
