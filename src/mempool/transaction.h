#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
public:
    std::string txid;
    double fee;
    uint64_t size;

    Transaction() : txid(""), fee(0.0), size(0) {} // Default Constructor
    Transaction(const std::string& id, double f, uint64_t s) : txid(id), fee(f), size(s) {}
};

#endif // TRANSACTION_H
