#include "wasm_executor.h"  // Corrected include path
#include <iostream>
#include <cstdlib>

bool WASMExecutor::executeContract(const std::string& wasmFile) {
    if (wasmFile.empty()) {
        std::cerr << "[WASM] Error: No contract file specified!" << std::endl;
        return false;
    }

    std::string command = "wasmtime " + wasmFile;
    int result = system(command.c_str());

    if (result == 0) {
        std::cout << "[WASM] Smart Contract Executed Successfully: " << wasmFile << std::endl;
        return true;
    } else {
        std::cerr << "[WASM] Error executing contract: " << wasmFile << " (Exit Code: " << result << ")" << std::endl;
        return false;
    }
}
