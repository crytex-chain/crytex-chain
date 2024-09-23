#include "blockchain.h"

Blockchain::Blockchain()
{
    chain.push_back(createGenesisBlock());
    difficulty = 4;
}

Block Blockchain::createGenesisBlock()
{
    return Block(0, "0", {}); // Index 0, no previous hash, no transactions
}

Block Blockchain::getLatestBlock() {
    return chain.back();
}

void Blockchain::addBlock(Block newBlock) {
    newBlock.previousHash = getLatestBlock().hash;
    newBlock.mineBlock(difficulty);
    chain.push_back(newBlock);
}

bool Blockchain::isChainValid() {
    for (int i = 1; i < chain.size(); i++) {
        Block currentBlock = chain[i];
        Block previousBlock = chain[i - 1];

        if (currentBlock.hash != currentBlock.calculateHash()) return false;
        if (currentBlock.previousHash != previousBlock.hash) return false;
    }
    return true;
}

void Blockchain::adjustDifficulty() {
    int adjustmentInterval = 3;
    if (chain.size() % adjustmentInterval == 0) {
        // Logic to adjust difficulty based on block times
    }
}

