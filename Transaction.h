#include<string>
#include"BitcoinAccount.h"
#include"EtherAccount.h"
using namespace std;
#ifndef B
#define B
class Transaction {
protected:
    string sender_public_key;   //to store sender's public key
    string receiver_public_key; //to store reciever's public key
    double amount;  //to store amount sent in this transaction
protected:
    void setRecieverKey(string s) { //for storing receiver's public key
        receiver_public_key = s;
    }
    void setSenderKey(string s) {   //for storing sender's public key
        sender_public_key = s;
    }
public:
    virtual void setSenderPublicKey(Account* ptr) { //for storing sender's public key
        setSenderKey(ptr->getPublicKey());
    }

    virtual void setRecieverPublicKey(Account* ptr) {   //for storing receiver's public key
        setRecieverKey(ptr->getPublicKey());
    }
    string getSenderPublicKey()const {  //for getting sender's key
        return sender_public_key;
    }
    string getRecieverPublicKey()const {    //for getting receiver's key
        return receiver_public_key;
    }
    void setAmount(double amount) { //for storing amount
        this->amount = amount;
    }

    virtual string ToString()/* Do not modify this function*/
    {
        return this->sender_public_key + "-" + this->receiver_public_key + "-" + to_string(amount);
    }
    void write_to_file(ofstream& fout) {
        size_t length = sender_public_key.length();
        fout.write(reinterpret_cast<char*>(&length), sizeof(size_t));
        fout.write(sender_public_key.c_str(), length);
        length = receiver_public_key.length();
        fout.write(reinterpret_cast<char*>(&length), sizeof(size_t));
        fout.write(receiver_public_key.c_str(), length);
        fout.write(reinterpret_cast<char*>(&amount), sizeof(amount));
    }
};

#endif // !B
