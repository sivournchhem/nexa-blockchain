#ifndef MEMPOOL_TRANSACTION_H
#define MEMPOOL_TRANSACTION_H

#include <vector>
#include <cstdint>
#include <string>

class Transaction {
public:
    uint32_t version;
    std::vector<uint8_t> inputs;
    std::vector<uint8_t> outputs;
    uint32_t locktime;
    uint64_t fee;     // Added missing fee
    uint32_t size;    // Added missing size
    std::string txid; // Added missing txid

    Transaction() : version(1), locktime(0), fee(0), size(0), txid("") {}

    void Serialize();
    void Deserialize();
};

#endif // MEMPOOL_TRANSACTION_H
