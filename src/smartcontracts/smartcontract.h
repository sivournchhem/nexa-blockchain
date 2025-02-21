#ifndef SMARTCONTRACT_H
#define SMARTCONTRACT_H

#include <string>
#include <vector>

class SmartContract {
public:
    static void deployContract(const std::string& contractCode);
    static std::string executeContract(const std::string& function, const std::vector<std::string>& args);
};

#endif // SMARTCONTRACT_H
