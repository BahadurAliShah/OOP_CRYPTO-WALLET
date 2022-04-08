#include"Transaction.h"
#pragma once
class TransactionHashed :public Transaction
{
public:
    virtual void setSenderPublicKey(Account* ptr) {
        setSenderKey(ptr->getHash(ptr->getPublicKey()));    /*to store hash of sender public key*/
    }

    virtual void setRecieverPublicKey(Account* ptr) {   /*to store Hash of receiver public key*/
        setRecieverKey(ptr->getHash(ptr->getPublicKey()));
    }
};