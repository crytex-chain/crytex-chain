#include "p2p.h"
#include <thread>

void Node::startNode()
{
    while (true)
    {
        // Listen for incoming transactions or blocks from peers
        listenForMessages();
    }
}

void Node::listenForMessages()
{
    // Receive transaction/block from another node
    // Validate it, and if valid, add it to the blockchain
    // If it's a block, broadcast it to other nodes

    // For now, we'll just add a dummy block to the blockchain
    std::vector<Transaction> txs;
    Block newBlock(crytexChain.chain.size(), crytexChain.getLatestBlock().hash, txs);
    newBlock.mineBlock(crytexChain.difficulty);
    crytexChain.addBlock(newBlock);

    // Broadcast the new block to other nodes
    broadcastBlock(newBlock);

    // Sync the blockchain with other nodes
    syncBlockchain();

    // Sleep for a few seconds before listening for more messages
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Repeat the process

    // Note: In a real-world scenario, you would need to handle various types of messages,
}

void Node::broadcastBlock(Block newBlock) {
    // Send the mined block to other nodes in the network
    // For now, we'll just print the block details
    std::cout << "Broadcasting new block to other nodes..." << std::endl;
}

void Node::syncBlockchain() {
    // Compare local blockchain with peers and update accordingly
    // For now, we'll just print the blockchain size
    std::cout << "Syncing blockchain with other nodes..." << std::endl;
}
