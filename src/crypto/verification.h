#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <string>

bool verifySignature(const std::string& signature, const std::string& message, const std::string& publicKey);

#endif // VERIFICATION_H
