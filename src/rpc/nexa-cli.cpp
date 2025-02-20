#include <iostream>
#include <cstdlib>
#include <cstdio>

void executeCommand(const char* command) {
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        std::cerr << "Error executing command!" << std::endl;
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

    std::string command = argv[1];

    std::string fullCommand = "./src/nexad -rpccommand " + command;
    executeCommand(fullCommand.c_str());

    return 0;
}
