#ifndef A
#define A
class Currency{
    double amount;
    public:
    Currency()
    {
        amount=0;
    }
    Currency(double amount) {
        this->amount = amount;
    }
    virtual void DeductTransaction()
    {
        //Deducts transaction fee from amount
        //if amount is less than transaction fee it still deducts and leave the user in debt e.g negative amount
    }
    void operator+=(double c)
    {
        //add c to the amount
        amount += c;

    }
    void operator-=(double c)
    {
        //deducte c from amount
        amount -= c;
    }
    double getAmount() const
    {
        return this->amount;
    }
    void setAmount(double amount) {
        this->amount = amount;
    }

};
#endif
