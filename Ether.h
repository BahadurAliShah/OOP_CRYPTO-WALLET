#include"Currency.h"
#ifndef D
#define D
class Ether :public Currency {
public:
    virtual void DeductTransaction() {  //to deduct transaction fee which is 5 Ethers
        setAmount(getAmount() - 5);
    }
};
#endif // !D