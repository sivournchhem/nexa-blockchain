#include "exchange_api.h"
#include <iostream>

std::string ExchangeAPI::getBalance(const std::string& address) {
    std::cout << "[Exchange API] Checking balance for address: " << address << std::endl;
    return "1000 NXA";  // Placeholder
}

std::string ExchangeAPI::createTransaction(const std::string& sender, const std::string& receiver, double amount) {
    std::cout << "[Exchange API] Creating transaction from " << sender << " to " << receiver << " for " << amount << " NXA" << std::endl;
    return "Transaction ID: 123456";  // Placeholder
}
