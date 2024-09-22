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
};

#endif // WALLET_H
