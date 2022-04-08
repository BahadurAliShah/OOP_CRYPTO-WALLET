#pragma once
#include"Account.h"
#include"BitCoin.h"
class BitcoinAccount:public Account{
protected:
    virtual string getHash(string private_key); //to return the Hash of passed string
public:
    BitcoinAccount();
    BitcoinAccount(const BitcoinAccount& copy);
    ~BitcoinAccount();
};

string BitcoinAccount::getHash(string private_key) {
    /*  RepeatTilSize  */
    int length = private_key.length();  //store length of passed string
    string hashed_key;  //hashed key is declared to store hash of given string i.e private key
    hashed_key.resize((length) * (length + 1)); //hashed_key is resized to length of Hash of passed string i.e private_key
    for (int i = 0; i < length; i++) {
        hashed_key[i * (length + 1)] = private_key[i];
        char temp = private_key[i]; 
        for (int j = 1; j <= length; j++) {
            if (temp == 127)    //when Ascii will reach to 127 it will again start from zero 
                temp = 0;
            else
                temp++;
            hashed_key[i * (length + 1) + j] = temp;
        }
    }
    return hashed_key;
}
BitcoinAccount::BitcoinAccount() {
        Currency* ptr = new BitCoin;      //to set coins to BitCoin type  
        ptr->setAmount(12); //it will set amount to 12 when BitCoin object will created
        setCoins(ptr);
    }

BitcoinAccount::BitcoinAccount(const BitcoinAccount& copy) {    //for Deep Copy
        setPublicKey(copy.getPublicKey());
        setPrivateKeyHash(copy.getPrivateKeyHash());
        Currency* ptr = new BitCoin;    
        (*ptr) = *(copy.getCoins());
        setCoins(ptr);
    }
BitcoinAccount::~BitcoinAccount() {
        setCoins(NULL); //delete meomry pointed by coins and set it to Null pointer
    }