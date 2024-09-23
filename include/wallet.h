#ifndef WALLET_H
#define WALLET_H

#include "transaction.h"

class Wallet {
public:
    std::string privateKey;
    std::string publicKey;

    Wallet();

    void generateKeys();
    Transaction createTransaction(std::string to, double amount);

private:
    std::string generatePrivateKey();
    std::string derivePublicKey(std::string key);
    std::string signTransaction(std::string privateKey, std::string amount);
};

#endif // WALLET_H
