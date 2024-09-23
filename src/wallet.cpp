#include "wallet.h"
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/sha.h>
#include <openssl/err.h>
#include <sstream>
#include <iostream>

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

std::string Wallet::generatePrivateKey()
{
    RSA* rsa = RSA_new();
    BIGNUM* bn = BN_new();
    BN_set_word(bn, RSA_F4); // RSA_F4 is a standard exponent

    // Generate the RSA key pair (2048 bits)
    if (!RSA_generate_key_ex(rsa, 2048, bn, NULL)) {
        std::cerr << "Error generating RSA key pair" << std::endl;
        return "";
    }

    // Convert private key to string (PEM format)
    BIO* bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);

    char* keyData;
    long keyLen = BIO_get_mem_data(bio, &keyData);
    std::string privateKeyStr(keyData, keyLen);

    // Free resources
    RSA_free(rsa);
    BIO_free(bio);
    BN_free(bn);

    return privateKeyStr;
}

std::string Wallet::derivePublicKey(std::string key)
{
    // Read private key from string
    BIO* bio = BIO_new_mem_buf(privateKey.data(), privateKey.size());
    RSA* rsa = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL);

    // Extract public key
    BIO* pubBio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(pubBio, rsa);

    char* pubKeyData;
    long pubKeyLen = BIO_get_mem_data(pubBio, &pubKeyData);
    std::string publicKeyStr(pubKeyData, pubKeyLen);

    // Free resources
    RSA_free(rsa);
    BIO_free(bio);
    BIO_free(pubBio);

    return publicKeyStr;
}

std::string signTransaction(std::string privateKey, std::string amount)
{
    BIO* bio = BIO_new_mem_buf(privateKey.data(), privateKey.size());
    RSA* rsa = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    // SHA256(reinterpret_cast<const unsigned char *>(data.c_str()), data.size(), hash);

    unsigned char signature[RSA_size(rsa)];
    unsigned int sigLen;

    if (RSA_sign(NID_sha256, hash, SHA256_DIGEST_LENGTH, signature, &sigLen, rsa) == 0) {
        std::cerr << "Error signing transaction" << std::endl;
        RSA_free(rsa);
        BIO_free(bio);
        return "";
    }

    std::stringstream ss;
    for (unsigned int i = 0; i < sigLen; i++) {
        ss << std::hex << static_cast<int>(signature[i]);
    }

    RSA_free(rsa);
    BIO_free(bio);

    return ss.str();
}
