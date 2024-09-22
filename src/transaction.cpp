#include "transaction.h"

Transaction::Transaction(std::string from, std::string to, double amt, std::string sign) {
    sender = from;
    receiver = to;
    amount = amt;
    signature = sign;
}

// TODO: Simplified function to verify the transaction
bool Transaction::verifyTransaction() {
    // return verifySignature(sender, signature);
    return false;
}
