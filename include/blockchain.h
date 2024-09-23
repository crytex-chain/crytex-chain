#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include "block.h"

class Blockchain {
public:
    std::vector<Block> chain;
    int difficulty; // Diffuculty for Proof of Work (PoW)

    Blockchain();

    Block createGenesisBlock();
    Block getLatestBlock();
    void addBlock(Block newBlock);
    bool isChainValid();
    void adjustDifficulty();
};

#endif // BLOCKCHAIN_H