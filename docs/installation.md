# Nexa Core Installation Guide  

## Prerequisites  
- Ubuntu 20.04+  
- Git, CMake, g++, make  

## Installation Steps  
```sh
git clone https://github.com/founderNXA/nexa-core.git
cd nexa-core
mkdir build
cd build
cmake ..
make -j$(nproc)
