#ifndef BLOCK_H
#define BLOCK_H

#include <cstring>
#include <iomanip>
#include <iostream>
#include <openssl/sha.h>
#include <sstream>
#include <string>

#include "transaction.h"

class Block
{
public:
    int index;
    std::string timestamp;
    std::string previousHash;
    std::string hash;
    std::vector<Transaction> transactions;
    int nonce;

    Block(int idx, std::string prevHash, std::vector<Transaction> txs);

    std::string currentTime();
    std::string calculateHash();
    void mineBlock(int difficulty);

private:
    std::string sha256(const std::string &data);
};

#endif // BLOCK_H