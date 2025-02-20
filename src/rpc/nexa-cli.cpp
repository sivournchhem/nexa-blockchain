#include <iostream>
#include <cstdlib>
#include <cstdio>

// Function to validate user input before executing RPC commands
bool validateInput(const std::string& input) {
    if (input.empty()) {
        std::cerr << "[ERROR] Input cannot be empty!" << std::endl;
        return false;
    }
    if (input.find(";") != std::string::npos || input.find("&") != std::string::npos || 
        input.find("|") != std::string::npos || input.find("`") != std::string::npos) {
        std::cerr << "[SECURITY] Potential command injection detected!" << std::endl;
        return false;
    }
    return true;
}

// Function to execute RPC commands securely
void executeRPC(const std::string& command) {
    if (!validateInput(command)) {
        return;
    }

    std::string fullCommand = "curl --user nexa:securepassword --data-binary '{\"jsonrpc\": \"1.0\", \"id\":\"test\", \"method\": \"" 
        + command + "\", \"params\": [] }' -H 'content-type: text/plain;' http://127.0.0.1:8332/";

    FILE* pipe = popen(fullCommand.c_str(), "r");
    if (!pipe) {
        std::cerr << "[ERROR] Failed to execute RPC command: " << command << std::endl;
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        std::cout << buffer;
    }

    int exitCode = pclose(pipe);
    if (exitCode != 0) {
        std::cerr << "[ERROR] RPC command failed with exit code " << exitCode << std::endl;
    }
}

// Main function to process user RPC command input
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: nexa-cli <command>" << std::endl;
        return 1;
    }

    executeRPC(argv[1]);
    return 0;
}
