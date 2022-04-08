#pragma once
#include"Account.h"
#include"Ether.h"
class EtherAccount:public Account{
protected:
    virtual string getHash(string private_key); //to return hash of given key
public:
    EtherAccount();
    EtherAccount(const EtherAccount& copy);
    virtual ~EtherAccount();
};
string EtherAccount::getHash(string private_key) {
    /*  ASCIHash  */
    int length = private_key.length();  //to store length of given string i.e private key
    string hashed_key;  //string hashed_key is declared to store hash of given string
    hashed_key.resize(length * 3);
    for (int i = 0, k = 0; private_key[i]; i++) {
        int temp = private_key[i];
        int arr[3] = { 0,0,0 };
        for (int j = 0; temp; j++) {
            arr[j] = temp % 10;
            temp /= 10;
        }
        for (int j = 2; j >= 0; j--) {
            if (arr[j] || j == 0) {
                hashed_key[k] = '0' + arr[j];
                k++;
            }
        }
    }
    return hashed_key;
}

EtherAccount::EtherAccount() {
        Currency* ptr = new Ether;  //to set coins to BitCoin type  
        ptr->setAmount(120);    //it will set amount to 12 when BitCoin object will created
        setCoins(ptr);
    }
EtherAccount::EtherAccount(const EtherAccount& copy) {  //for deep copy
        setPublicKey(copy.getPublicKey());
        setPrivateKeyHash(copy.getPrivateKeyHash());
        Currency* ptr = new Ether;
        (*ptr) = *(copy.getCoins());
        setCoins(ptr);
    }
EtherAccount::~EtherAccount() {
        setCoins(NULL); //delete meomry pointed by coins and set it to Null pointer
}