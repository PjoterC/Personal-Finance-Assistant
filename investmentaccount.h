#ifndef INVESTMENTACCOUNT_H
#define INVESTMENTACCOUNT_H

#include "account.h"
#include <utility>
#include "stock.h"
class investmentAccount : public account
{
    public:
        investmentAccount(int accountID, int ownerID, string ownerName, float balance = 1000); //creates a new investment account, starting balance is 1000 for easier testing (in real app would be 0)
        ~investmentAccount();




        void Buy_Stock(int amount, string stockName, string stockCode, float totalPrice, Date date); //registers a transfer of buying a stock and adds it to transfer history, adds stock to the ownedStocks list

        pair<int, string> Sell_Stock(int amount, string stockCode); //registers a transfer of selling a stock and adds it to transfer history, removes stock from the ownedStocks list
        void Display_Owned_Stocks(); //displays information about stocks owned by this account
        pair<Stock, int>* Check_If_Stock_Owned(string stockCode); //checks if account owns a stock with given code

        string Save_Stocks(); //saves the stocks to a text file named (accountID)s
        void Load_StockPair(float price, string name, string code, int amount); //loads owned stocks and their amount from a text file

    protected:

    private:



};

#endif // INVESTMENTACCOUNT_H
