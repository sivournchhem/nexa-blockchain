#ifndef EXCHANGE_API_H
#define EXCHANGE_API_H

#include <string>

class ExchangeAPI {
public:
    static std::string getBalance(const std::string& address);
    static std::string createTransaction(const std::string& sender, const std::string& receiver, double amount);
};

#endif // EXCHANGE_API_H
