#include "miner.h"
#include "p2p.h"

void Miner::startMining()
{
    while (true)
    {
        Block newBlock = createBlock();
        newBlock.mineBlock(crytexChain->difficulty);
        crytexChain->addBlock(newBlock);

        // Node::broadcastBlock(newBlock);
        Node node = Node();
        node.broadcastBlock(newBlock);
    }
}

Block Miner::createBlock()
{
    // Gather pending transactions, create a block, and return it
}
