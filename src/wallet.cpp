#include "wallet.h"

Wallet::Wallet()
{
    generateKeys(); // Generate the key pair when wallet is created
}

void Wallet::generateKeys()
{
    // Generate public-private key pair (RSA or Elliptic Curve)
    privateKey = generatePrivateKey();
    publicKey = derivePublicKey(privateKey);
}

// Function to create a signed transaction
Transaction Wallet::createTransaction(std::string to, double amount)
{
    std::string signature = signTransaction(privateKey, std::to_string(amount));
    return Transaction(publicKey, to, amount, signature);
}
