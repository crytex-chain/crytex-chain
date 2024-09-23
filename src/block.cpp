#include "block.h"

Block::Block(int idx, std::string prevHash, std::vector<Transaction> txs)
{
    index = idx;
    timestamp = currentTime(); // Function to get the current timestamp
    previousHash = prevHash;
    transactions = txs;
    nonce = 0;
    hash = calculateHash(); // Calculate the initial hash
}

std::string Block::currentTime()
{
    // time_t now = time(0);
    // return ctime(&now);

    return std::to_string(time(0));
}

std::string Block::calculateHash()
{
    if (!cachedHash.empty()) return cachedHash;
    std::string txs;
    for (Transaction tx : transactions)
    {
        txs += tx.sender + tx.receiver + std::to_string(tx.amount);
    }

    cachedHash = sha256(std::to_string(index) + timestamp + previousHash + txs + std::to_string(nonce));
    return cachedHash;
}

std::string Block::sha256(const std::string &data)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;

    // SHA256_Init(&sha256);
    if (!SHA256_Init(&sha256))
    {
        throw std::runtime_error("SHA256 initialization failed");
    }
    SHA256_Update(&sha256, data.c_str(), data.size());
    SHA256_Final(hash, &sha256);

    // Convert the binary hash to a hexadecimal string
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
        // hashStr += hash[i];
    }
    return ss.str();
}

void Block::mineBlock(int difficulty)
{
    if (nonce % 10000 == 0)
    {
        std::cout << "Mining block with nonce: " << nonce << std::endl;
    }

    while (hash.substr(0, difficulty) != std::string(difficulty, '0'))
    {
        nonce++;
        hash = calculateHash();
    }

    std::cout << "Block mined: " << hash << std::endl;
}
