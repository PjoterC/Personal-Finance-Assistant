#ifndef PERSONALASSISTANT_H
#define PERSONALASSISTANT_H
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"

#include <time.h>
#include "personalaccount.h"
#include "investmentaccount.h"
#include "user.h"
#include <memory>
#include "date.h"

#include "stock.h"
#include <fstream>
#include <filesystem>
class user;
class PersonalAssistant
{
    public:
        PersonalAssistant();
        ~PersonalAssistant();
        void Register_New_User_ID(int ID); //adds user's id to the list of user IDs

        bool Check_For_User_ID(int ID); //checks if user with a given ID exists on the list
        account* Check_For_Account_ID(int ID); //returns a pointer to account with given ID if exists, else returns nullptr


        void Print_All_Users_List(list<user>& users); //prints list of all user IDs (testing only, not for users)
        void Print_All_Accounts_List(); //prints list of all accounts
        void Print_User_Accounts_List(int userID); //prints list of all accounts of one user


        int Register_Personal_Account(int ownerID, string ownerName, int ID = 1, float balance = 1000); //creates a new Personal Account and adds it to the list of accounts
        int Register_Investment_Account(int ownerID, string ownerName, int ID = 1, float balance = 1000); //creates a new Investment Account and adds it to the list of accounts

        void Remove_Account(int accID); //removes account from the list
        void Remove_User(int userID);  //removes user's ID from the list

        void Set_Date(int day, int month, int year); //sets the todayDate


        //TRANSFER CREATION
        void Register_Transfer_Between(float value, string title, int recID, int sendID); //calls receiving and sending accounts to create appropriate transfers
        void Register_Transfer(int accNumber, float value, string target); // calls an account to create a transfer to or from an outer source (personal accounts only)


        string Get_Owners_Name(int ID); //returns the name of the owner of the account with a given ID


        //HISTORY CHECK
        void Check_Account_History_By_Name(int accNumber, string name); //Displays history of account's transfers with a user with a given name
        void Check_By_Name_For_All(int ownerID, string name); //Displays history of all of user's accounts transfers with a user with a given name






        float GetTotalUserBalance(int ownerID); //returns the sum of balance of all of user's accounts



        //INVESTMENT ACCOUNT AND STOCKS
        Stock* Find_Stock(string code); //returns pointer to stock with a given code
        void Add_Stock(float price, string name, string code); //adds a new stock to the list of available stocks
        void Display_Available_Stocks(); //displays list of all stocks that are available to buy or sell
        void Set_Stock_Price(float value, string code); //sets a price of a stock with a given code
        void Buy_Stock(int accNumber, string code, int amount);
        void Sell_Stock(int accNumber, string code, int amount);



        //TEXTFILE HANDLING
        void Write_Account(int accountID); //saves account data in a text file, name of which is the ID of the chosen account
        void Write_Account_IDs(); //saves IDs of all accounts in a text file "accountIDs" (used later for read)
        void Write_All_Accounts(); //calls Write_Account() for all accounts
        void Load_Account(int ID); //Loads data for an account with a given ID
        void Load_All_Accounts(); //calls Load_Account() for all accounts

    protected:

    private:
        list<int> userIDs;
        list<account> accounts;
        Date todayDate;
        list<Stock> availableStocks;

};

#endif // PERSONALASSISTANT_H
