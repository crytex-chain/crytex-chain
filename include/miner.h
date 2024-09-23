#ifndef MINER_H
#define MINER_H

#include "blockchain.h"

class Miner {
public:
    Blockchain* crytexChain;
    void startMining();
    Block createBlock();
};


#endif // MINER_H
