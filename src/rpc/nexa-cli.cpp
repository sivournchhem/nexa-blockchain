#include <iostream>
#include <cstdlib>
#include <cstdio>

void executeRPC(const std::string& command) {
    std::string fullCommand = "curl --user nexa:securepassword --data-binary '{\"jsonrpc\": \"1.0\", \"id\":\"test\", \"method\": \"" + command + "\", \"params\": [] }' -H 'content-type: text/plain;' http://127.0.0.1:8332/";
    
    FILE* pipe = popen(fullCommand.c_str(), "r");
    if (!pipe) {
        std::cerr << "Error executing RPC command!" << std::endl;
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        std::cout << buffer;
    }
    pclose(pipe);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: nexa-cli <command>" << std::endl;
        return 1;
    }

    executeRPC(argv[1]);
    return 0;
}
