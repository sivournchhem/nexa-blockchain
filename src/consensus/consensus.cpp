#include <iostream>  // Fix missing iostream
#include "../consensus/consensus.h"
#include "../mempool/transaction.h"

bool validateTransaction(const Transaction& tx) {
    if (tx.fee <= 0) {
        std::cerr << "[ERROR] Invalid transaction: Fee must be greater than zero." << std::endl;
        return false;
    }
    if (tx.size > 1000000) {  // 1MB transaction limit
        std::cerr << "[ERROR] Invalid transaction: Size exceeds 1MB." << std::endl;
        return false;
    }
    return true;
}
