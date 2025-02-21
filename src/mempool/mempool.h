#ifndef MEMPOOL_H
#define MEMPOOL_H

#include <unordered_map>
#include <memory>
#include <mutex>
#include "transaction.h"

class Mempool {
public:
    void addTransaction(const std::shared_ptr<Transaction>& tx);
    void processTransactions();

private:
    std::unordered_map<std::string, std::shared_ptr<Transaction>> pool;
    std::mutex mempoolMutex;
};

#endif // MEMPOOL_H
