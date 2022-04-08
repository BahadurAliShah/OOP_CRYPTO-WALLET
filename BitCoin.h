#include"Currency.h"
#ifndef E
#define E
class BitCoin :public Currency {
public:
    virtual void DeductTransaction() {  //to deduct transaction fee which is 2 BitCoins
        setAmount(getAmount() - 2);
    }
};
#endif // !E