#ifndef ACCOUNT_H
#define ACCOUNT_H
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"


#include <list>
#include<iostream>
#include<string>
#include "transfer.h"
#include "time.h"
#include <memory>
#include "stock.h"
#include <utility>
#include <sstream>

using namespace std;
class account
{
    public:
        account();
        virtual ~account();




        void Display_History(); //displays accounts history of all transfers

        void Display_By_Date(int sMonth, int sYear, int eMonth, int eYear); //displays history of transfers in a given time period

        void Display_By_Person(string name); //displays history of transfers with a person with a given name

        float Display_Income(int sMonth, int sYear, int eMonth, int eYear); //displays income in given time period

        float Display_Expenses(int sMonth, int sYear, int eMonth, int eYear); //displays expenses in given time period

        void Add_To_History(const Transfer& added); //adds a transfer to history

        bool Create_Transfer_Out(float value, string title, int recID, string recName, Date date); /*if given value is correct (>0 and >balance), creates a transfer, adds it to the history
        and returns true
        */

        void Create_Transfer_In(float value, string title, int sendID, string sendName, Date date); //activated when receiving transfer from another account or outer source, adds transfer to history


        int datecmp(const Transfer& transfer1, const Transfer& transfer2); //used to compare dates of 2 transfers





        bool Check_If_Investment(); //verifies if account is an investment account

        void Clear_History(); //deletes history of the account, used when removing account

        int GetID();
        int GetOwnerID();
        string GetOwnerName();
        float GetBalance();




        string Save_History(); //returns a string containing transfer history to be used by the assistant while saving
        void Load_Transfer(float value, string title, int recID, int sendID, string recName, string sendName, int day, int month, int year);




    protected:
        int accountID;
        int ownerID;
        string ownerName;
        float balance;
        list<Transfer> history; //transfer history sorted from most recent to oldest
        bool isInvestment;

        list<pair<Stock, int>> ownedStocks;


    private:

};

#endif // ACCOUNT_H
