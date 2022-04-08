#include"AccountManager.h"
class HashedAccountManager:public AccountManager {
	vector <TransactionHashed> TransactionLog;
public:
    HashedAccountManager() {
        
    }

    virtual bool MakeTransaction(string sender_public_key, string sender_private_key, string reciever_public_key, double amount)
    {
        for (int i = 0; i < (getNumAccounts()); i++) {
            if (!strcmp(sender_public_key.c_str(), ((getArray())[i]->getPublicKey()).c_str())) {//finding account of passed sender public key if not found then it will return false
                if ((getArray())[i]->SendCoins(sender_private_key, amount)) {//private key of sender's account and amout is passed to send coins if it matches then record of
                //strored otherwise it will return false
                    TransactionHashed temp;
                    temp.setSenderPublicKey((getArray())[i]);
                    for (int j = 0; j < (getNumAccounts()); j++) {
                        if (!strcmp(reciever_public_key.c_str(), (getArray())[j]->getPublicKey().c_str())) {//finding receiver's account if found then coins will add to his account otherwise
                            //coins of sender will waste
                            temp.setRecieverPublicKey((getArray())[j]);//storing receiver public key
                            if (!strcmp(typeid(*(getArray())[i]).name(), typeid(*(getArray())[j]).name())) {
                                (getArray())[j]->AddCoin(amount); //if both accounts are of same type then coins will add to receiver account without conversion
                            }
                            else if (!strcmp(typeid(*(getArray())[i]).name(), "class BitcoinAccount")) {
                                (getArray())[j]->AddCoin(amount * 12);    /*if sender account is bitcoin account and reciver account is ether account then amount will
                                                                            multiplied to 12 because 1 BitCoin == 12 Ethers*/
                            }
                            else {
                                (getArray())[j]->AddCoin(amount / 12);    /*if sender account is ether account and receiver account is BitCoin account then total amount
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

    virtual string ToStringTransactionLog()
    {
        string res = "";
        for (int i = 0; i < TransactionLog.size(); ++i)
        {
            res += TransactionLog[i].ToString() + "\n";
        }
        return res;
    }  
    virtual void WriteTransactionLogToFile(ofstream& fout) {
        for (int i = 0; i < TransactionLog.size(); i++) {
            TransactionLog[i].write_to_file(fout);
        }
    }

    virtual void PUSHBACK(Transaction* temp_ptr) {
        TransactionLog.push_back(*(reinterpret_cast<TransactionHashed *>(temp_ptr)));
    }
};
