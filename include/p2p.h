#ifndef P2P_H
#define P2P_H

#include <string>
#include "blockchain.h"

class Node {
public:
    std::string nodeID;
    Blockchain crytexChain;

    void startNode();
    void listenForMessages();
    void broadcastBlock(Block newBlock);
    void syncBlockchain();
};

#endif // P2P_H
