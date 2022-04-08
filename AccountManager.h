#include<iostream>
#include<vector>
#include<cstdlib>
#include<time.h>
#include<string.h>
#include<fstream>
#include"EtherAccount.h"
#include"BitcoinAccount.h"
#include"Currency.h"
#include"TransactionHashed.h"
using namespace std;
enum ACC_TYPE { BITCOIN, ETHER };
class AccountManager {
    Account** arr;
    int NumAccounts;
    vector<Transaction> TransactionLog;
    bool SearchPublicKey(string Key);
protected:
    int getNumAccounts() { return NumAccounts; }
    Account** getArray() { return arr; }
public:
    AccountManager();
    AccountManager(const AccountManager& copy);
    bool AddAccount(Account& a);
    string GenerateRandomKey();
    string  CreateAccount(ACC_TYPE e);
    virtual bool MakeTransaction(string sender_public_key, string sender_private_key, string reciever_public_key, double amount);
    virtual string ToStringAccounts();
    virtual Account* operator[](int i);
    virtual string ToStringTransactionLog();
    void WriteToFile(string filename);
    void LoadFromFile(string filename);
    virtual void PUSHBACK(Transaction*);
    virtual void WriteTransactionLogToFile(ofstream&);

    virtual ~AccountManager();
};

//Constructors
AccountManager::AccountManager()
{
    this->NumAccounts = 0;
    arr = NULL;
    srand(time(0));
}
AccountManager::AccountManager(const AccountManager& copy) {    //for deep copy
    for (int i = 0; i < NumAccounts; i++)
        delete arr[i];
    delete[] arr;
    arr = new Account * [copy.NumAccounts];
    NumAccounts = copy.NumAccounts;
    for (int i = 0; i < copy.NumAccounts; i++) {
        string temp = typeid(*(copy.arr[i])).name();
        if (!strcmp(temp.c_str(), "class BitcoinAccount")) {
            arr[i] = new BitcoinAccount;
        }else
            arr[i] = new EtherAccount;
        *arr[i] = *(copy.arr[i]);
    }

    TransactionLog.clear();
    for (int i = 0; i < copy.TransactionLog.size(); i++) {
        TransactionLog.push_back(copy.TransactionLog.at(i));
    }
}
Account* AccountManager::operator[](int i)
{
    if(i>=NumAccounts||i<0) //return Null pointer when passed value will out of range
        return NULL;
    return arr[i];
}

//Normal Functions
string AccountManager::GenerateRandomKey()
{
    int i, length = 3;  //length of string which will be returned

    string random, defined = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";//string from which random string will extract
    random.resize(length);  //random string is resized to length
    i = 0;
    do {
        random[i] = defined[rand() % defined.length()]; //random indexes are extracted from defined string
        i++;
    } while (i < length);   //loop will iterate untill iterator becomes equal to length-1
    return random;
}
bool AccountManager::AddAccount(Account& a)
{
    /*Add the account a to the list of accounts arr
    *return true if successful
    * return false if account with public key already exists
    * increase NumAcoounts
    *         * */
    if (SearchPublicKey(a.getPublicKey())) {
        Account** temp = new Account *[NumAccounts + 1];
        for (int i = 0; i < NumAccounts; i++) {
            temp[i] = arr[i];
        }
        if (!strcmp((typeid(*a.getCoins()).name()), "class BitcoinAccount")) {
            temp[NumAccounts] = new BitcoinAccount;
            (temp[NumAccounts]->getCoins())->setAmount((a.getCoins())->getAmount());
        }
        else if (!strcmp((typeid(*a.getCoins()).name()), "class EtherAccount")) {
            temp[NumAccounts] = new EtherAccount;
            (temp[NumAccounts]->getCoins())->setAmount((a.getCoins())->getAmount());
        }
        else {
            temp[NumAccounts] = new Account;
            Currency* ptr=new Currency;
            double amount = (*a.getCoins()).getAmount();
            ptr->setAmount(amount);
            temp[NumAccounts]->setCoins(ptr);
        }
        temp[NumAccounts]->setPublicKey(a.getPublicKey());
        temp[NumAccounts]->setPrivateKeyHash(a.getPrivateKeyHash());
        NumAccounts++;
        delete arr;
        arr = temp;
        return true;
    }
    else
        return false;
}

bool AccountManager::SearchPublicKey(string Key) {
    /*if public key matches to public key of any account, it will return false else true*/
    if (NumAccounts) {
        for (int i = 0; i < NumAccounts; i++) {
            if (Key.length() == arr[i]->getPublicKey().length()) {
                for (int j = 0; j < Key.length(); j++) {
                    if (Key[j] != (arr[i]->getPublicKey())[j])
                        break;
                    if (j == Key.length() - 1) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    else
        return true;
}
string  AccountManager::CreateAccount(ACC_TYPE e)
{
    bool a = false;
    string public_key = GenerateRandomKey();
    while (!a) {
        if (!SearchPublicKey(public_key)) {
            public_key = GenerateRandomKey();
        }
        else
        {
            a = true;
        }
    }
    Account** temp = new Account * [NumAccounts + 1];
    for (int i = 0; i < NumAccounts; i++) {
        temp[i] = arr[i];
    }
    if(e)
        temp[NumAccounts] = new EtherAccount;
    else
        temp[NumAccounts] = new BitcoinAccount;
    string private_key = GenerateRandomKey();
    temp[NumAccounts]->setPublicKey(public_key);
    temp[NumAccounts]->setPrivateKeyHash(temp[NumAccounts]->getHash(private_key));
    NumAccounts++;
    delete arr;
    arr = temp;
    temp = NULL;
    cout << "Account Created with Public Key: " << public_key << "\tPrivate Key: " << private_key;
    return private_key;
}
bool AccountManager::MakeTransaction(string sender_public_key, string sender_private_key, string reciever_public_key, double amount)
{
    for (int i = 0; i < NumAccounts; i++) {
        if (!strcmp(sender_public_key.c_str(), (arr[i]->getPublicKey()).c_str())) { //finding account of passed sender public key if not found then it will return false
            if (arr[i]->SendCoins(sender_private_key, amount)) {    //private key of sender's account and amout is passed to send coins if it matches then record of
                //strored otherwise it will return false
                Transaction temp;
                temp.setSenderPublicKey(arr[i]);
                for (int j = 0; j < NumAccounts; j++) {
                    if (!strcmp(reciever_public_key.c_str(), arr[j]->getPublicKey().c_str())) { //finding receiver's account if found then coins will add to his account otherwise
                    //coins of sender will waste
                        temp.setRecieverPublicKey(arr[j]);  //storing receiver public key
                        if (!strcmp(typeid(*arr[i]).name(), typeid(*arr[j]).name())) {
                            arr[j]->AddCoin(amount);  //if both accounts are of same type then coins will add to receiver account without conversion
                        }
                        else if (!strcmp(typeid(*arr[i]).name(), "class BitcoinAccount")) {
                            arr[j]->AddCoin(amount*12);   /*if sender account is bitcoin account and reciver account is ether account then amount will
                                                            multiplied to 12 because 1 BitCoin == 12 Ethers*/
                        }
                        else {
                            arr[j]->AddCoin(amount/12);   /*if sender account is ether account and receiver account is BitCoin account then total amount
                                                            will divided by 12 because 1 Ether == 1/12 BitCoins*/
                        }
                    }
                }
                temp.setAmount(amount); /*storing amount sent to temp*/
                TransactionLog.push_back(temp); /*storing transaction to Transaction Log*/
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false;
}
string AccountManager::ToStringTransactionLog()
{
    string res = "";
    for (int i = 0; i < TransactionLog.size(); ++i)
    {
        res += TransactionLog[i].ToString() + "\n";
    }
    return res;
}
string AccountManager::ToStringAccounts()
{
    /** DO NOT MODIFY THIS FUNCTION**/
    string res = "";
    for (int i = 0; i < this->NumAccounts; ++i)
    {
        res += this->arr[i]->ToString() + "\n";
    }
    return res;
}
void AccountManager::LoadFromFile(string filename)
{
    ifstream fin(filename.c_str(), ios::in | ios::binary);
    if (fin.fail()) //if file not opened then warning msg will displayed on screen
        cout << "file is not opened\n";
    else {
        Account* temp_ptr;  //temporary pointer to read one object
        while ((fin.get()) != '\n') {   //loop will stop when \n will read
            string type, public_key, private_key;
            double amount;
            fin.seekg(-1, ios::cur);
            size_t length;
            fin.read(reinterpret_cast<char*>(&length), sizeof(size_t));
            char* temp = new char[length + 1];
            fin.read(temp, length);
            temp[length] = 0;
            type = temp;
            delete []temp;
            if (!strcmp(type.c_str(), "class BitcoinAccount")) {
                temp_ptr = new BitcoinAccount;
            }
            else if (!strcmp(type.c_str(), "class EtherAccount")) {
                temp_ptr = new EtherAccount;
            }
            else {
                temp_ptr = new Account;
                temp_ptr->setCoins(new Currency);
            }
            fin.read(reinterpret_cast<char*>(&length), sizeof(size_t));
            temp = new char[length + 1];
            fin.read(temp, length);
            temp[length] = 0;
            public_key = temp;
            delete[]temp;
            fin.read(reinterpret_cast<char*>(&length), sizeof(size_t));
            temp = new char[length + 1];
            fin.read(temp, length);
            temp[length] = 0;
            private_key = temp;
            delete[]temp;
            fin.read(reinterpret_cast<char*>(&amount), sizeof(amount));
            temp_ptr->setPublicKey(public_key);
            temp_ptr->setPrivateKeyHash(private_key);
            temp_ptr->getCoins()->setAmount(amount);
            AddAccount(*temp_ptr);
            temp_ptr = NULL;
        }
        Transaction temp_trans;
        temp_ptr = new Account;
        while ((fin.get()) != '\n') {
            string sender_key, receiver_key;
            double amount;
            size_t length;
            fin.seekg(-1, ios::cur);
            fin.read(reinterpret_cast<char*>(&length), sizeof(size_t));
            char* temp_char = new char[length + 1];
            fin.read(temp_char, length);
            temp_char[length] = 0;
            sender_key = temp_char;
            delete[]temp_char;

            fin.read(reinterpret_cast<char*>(&length), sizeof(size_t));
            temp_char = new char[length + 1];
            fin.read(temp_char, length);
            temp_char[length] = 0;
            receiver_key = temp_char;
            delete[]temp_char;

            fin.read(reinterpret_cast<char*>(&amount), sizeof(double));
            temp_ptr->setPublicKey(receiver_key);
            temp_trans.setRecieverPublicKey(temp_ptr);
            temp_ptr->setPublicKey(sender_key);
            temp_trans.setSenderPublicKey(temp_ptr);
            temp_trans.setAmount(amount);
            PUSHBACK(&temp_trans);
        }
        delete temp_ptr;
    }
}
void AccountManager::PUSHBACK(Transaction* temp_ptr) {
    TransactionLog.push_back(*temp_ptr);
}
void AccountManager::WriteToFile(string filename)
{
    ofstream fout;
    fout.open(filename.c_str(), ios::out);
    fout.close();
    fout.open(filename.c_str(), ios::app | ios::binary);
    for (int i = 0; i < NumAccounts; i++)
        arr[i]->write_to_file(fout);
    fout.put('\n');
    WriteTransactionLogToFile(fout);
    fout.put('\n');
    fout.close();
}
void AccountManager::WriteTransactionLogToFile(ofstream& fout) {
    for (int i = 0; i < TransactionLog.size(); i++) {
        TransactionLog[i].write_to_file(fout);
    }
}
AccountManager::~AccountManager() {
    for (int i = 0; i < NumAccounts; i++)
        delete arr[i];
    delete[] arr;
}
