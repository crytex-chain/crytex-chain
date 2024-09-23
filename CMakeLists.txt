cmake_minimum_required(VERSION 3.10)
project(Crytex)

# C++ version
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/blockchain.cpp
    src/block.cpp
    src/transaction.cpp
    src/wallet.cpp
    src/miner.cpp
    src/p2p.cpp
)

# Link libraries (OpenSSL for cryptography)
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

# Executable and linking
add_executable(crytex ${SOURCES})
target_link_libraries(crytex ${OPENSSL_LIBRARIES})
