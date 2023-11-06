#ifndef PERSONALACCOUNT_H
#define PERSONALACCOUNT_H

#include "account.h"


class personalAccount : public account
{
    public:
        personalAccount(int accountID, int ownerID, string ownerName, float balance = 1000); //creates a new personal account, starting balance is 1000 for easier testing (in real app would be 0)
        ~personalAccount();
        void Earn(float value, string target, Date date); //adds an income transfer to the history from external source (no other account transfer required) and changes the account balance
        void Spend(float value, string target, Date date); //adds an expenditure transfer to the history from external source (no other account transfer required) and changes the account balance


    protected:

    private:


};

#endif // PERSONALACCOUNT_H
