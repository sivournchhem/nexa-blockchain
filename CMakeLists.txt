cmake_minimum_required(VERSION 3.10)
project(NexaCore)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Define source files
set(SOURCES
    src/main.cpp
    src/network/network.cpp
    src/consensus/consensus.cpp
    src/mempool/mempool.cpp
    src/governance/governance.cpp
)

# Create executable
add_executable(nexad ${SOURCES})

# Include directories
target_include_directories(nexad PRIVATE ${CMAKE_SOURCE_DIR}/src)
