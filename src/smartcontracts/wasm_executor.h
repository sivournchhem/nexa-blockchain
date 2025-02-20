#ifndef WASM_EXECUTOR_H
#define WASM_EXECUTOR_H

#include <string>

class WASMExecutor {
public:
    static bool executeContract(const std::string& wasmFile);
};

#endif // WASM_EXECUTOR_H
