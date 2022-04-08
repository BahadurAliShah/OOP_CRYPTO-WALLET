#include<string>
#include<string.h>
#include"Currency.h"
#include<fstream>
#include<typeinfo>
#include"BitCoin.h"
#include"Ether.h"

using namespace std;
#pragma once
class Account {
    string public_key;//to store public key
    string private_key_hash;//to store hash of private key
    Currency* coins;    //to store address of currency (polymorphism)
public:
    //constructors
    Account();
    Account(bool);
    Account(string, string);
    //Setters
    void setPublicKey(string);
    void setPrivateKeyHash(string);
    void setCoins(Currency*);
    //Getters
    string getPublicKey()const;
    string getPrivateKeyHash()const;
    Currency* getCoins()const;

    virtual string getHash(string);

    bool VerfiyAccount(string);
    bool SendCoins(string, double);
    void DeductAmount(double);
    void AddCoin(double);
    string ToString();
    void write_to_file(ofstream&);

    virtual ~Account();

};

void Account::setPublicKey(string s) {  //to store given string in public key of object
    public_key = s;
}
void Account::setPrivateKeyHash(string s) { //to store given string in private key of object
    private_key_hash = s;
}
void Account::setCoins(Currency* ptr) {
    if (coins != NULL)      //check to delete meomory stpred in coins
        delete this->coins;
    this->coins = ptr;      //to assign given meomry to coins
}

//Getters
string Account::getPublicKey()const //to return public key of object
{
    return this->public_key;
}
string Account::getPrivateKeyHash()const {  //to return stored Hash of private key of object
    return private_key_hash;
}
Currency* Account::getCoins()const {    //to return address of meomry pointed by coins
    return coins;
}
//constructors
Account::Account()  //default constructor
{
    public_key = private_key_hash = ""; //it will make public_key and private_key empty
    coins = NULL;
}

Account::Account(string public_key, string private_key)
{
    this->public_key = public_key;  //it will store public key as given
    this->private_key_hash = getHash(private_key);  //it will take Hash of private key then store it
    coins = new Currency;   //meomry is assigned to coins to make account active
}
string Account::getHash(string s) { //it will return the hash of passed string
    return s;
}
bool Account::VerfiyAccount(string private_key)
{
    /*Take Hash of the parameter private_key and compare it with hash member variable
    return true if matches
    */
    return !strcmp(private_key_hash.c_str(), getHash(private_key).c_str());
}
bool Account::SendCoins(string private_key, double amount)
{
    if (VerfiyAccount(private_key)) {   //if account verified make transaction else return false
        (*coins) -= amount;     //passed amount will substracted from total amount of account
        coins->DeductTransaction(); //it will deduct transaction fee
        return true;
    }
    else
    {
        return false;
    }
}
void Account::DeductAmount(double amount)
{
    //Deduct amount from coins
    (*coins) -= (amount);

}
void Account::AddCoin(double amount)    //Add amount to coins
{
    if (amount > 0) //only add when passed amount will positive
        (*coins) += (amount);
}
string Account::ToString()
{
    //DO NOT MODIFY THIS FUNCTION
    return  getPublicKey() + "-" + to_string(coins->getAmount());
}
void Account::write_to_file(ofstream& fout) {
    string type = typeid(*this).name(); //to store name of object type in string type
    size_t length = type.length();  //to store length of type
    fout.write(reinterpret_cast<char*>(&length), sizeof(size_t));   //to write length of type in file because while reading it tells how many characters have to read
    fout.write(type.c_str(), length);    /*Account type is stored first because during the time of reading it is impossible to find the type of account*/
    length = public_key.length();   //to store lenth of public key of object
    fout.write(reinterpret_cast<char*>(&length), sizeof(size_t));   //to write length of public key in file
    fout.write(public_key.c_str(), length); //writing public key in file
    length = private_key_hash.length(); //storing lenght of private key
    fout.write(reinterpret_cast<char*>(&length), sizeof(size_t));   //writing length of private key hash in file
    fout.write(private_key_hash.c_str(), length);   //writing hash of private key in file
    double amount = coins->getAmount(); //storing no of coins
    fout.write(reinterpret_cast<char*>(&amount), sizeof(amount));   //writing no of coins in file
}
Account::~Account() {
    if (coins)
        delete coins;  //to delete meomry assigned to coins
}
